package ru.chudakov.generator

import java.util.*
import kotlin.math.exp
import kotlin.math.ln
import kotlin.math.sqrt

class Generator {
    private val maxRand: Int = Int.MAX_VALUE
    private val random = Random()
    private lateinit var normalTable: Table
    private lateinit var expTable: Table

    private class Table(
            val x1: Double,
            val a: Double,
            val stairWidth: Array<Double>,
            val stairHeight: Array<Double>
    )

    init {
        setupExpTables()
        setupNormalTables()
    }

    private fun basicRandGenerator(): Int {
        val number = random.nextInt()
        return (if (number < 0) {
            -number
        } else {
            number
        })
    }

    /**
     * a - minimal value
     * b - maximal value
     */
    fun uniform(a: Double, b: Double): Double {
        return a + basicRandGenerator() * (b - a) / maxRand
    }

    fun uniform(a: Double, b: Double, count: Int): Array<Double> {
        val normalize = (b - a) / maxRand

        return Array(count) { a + basicRandGenerator() * normalize };
    }

    private fun setupExpTables() {
        val x1 = 7.69711747013104972;
        val a = 3.9496598225815571993e-3; /// area under rectangle
        val stairWidth: Array<Double> = Array(257) { 0.0 }
        val stairHeight: Array<Double> = Array(256) { 0.0 }

        // coordinates of the implicit rectangle in base layer
        stairHeight[0] = exp(-x1)
        stairWidth[0] = a / stairHeight[0]
        // implicit value for the top layer
        stairWidth[256] = 0.0

        for (i in 1..255) {
            // such x_i that f(x_i) = y_{i-1}
            stairWidth[i] = -ln(stairHeight[i - 1])
            stairHeight[i] = stairHeight[i - 1] + a / stairWidth[i]
        }

        expTable = Table(x1, a, stairWidth, stairHeight)
    }

    private fun setupNormalTables() {
        val x1 = 3.6541528853610088;
        val a = 4.92867323399e-3; /// area under rectangle
        val stairWidth: Array<Double> = Array(257) { 0.0 }
        val stairHeight: Array<Double> = Array(256) { 0.0 }

        // coordinates of the implicit rectangle in base layer
        stairHeight[0] = exp(-.5 * x1 * x1)
        stairWidth[0] = a / stairHeight[0]
        // implicit value for the top layer
        stairWidth[256] = 0.0

        for (i in 1..255) {
            // such x_i that f(x_i) = y_{i-1}
            stairWidth[i] = sqrt(-2 * ln(stairHeight[i - 1]))
            stairHeight[i] = stairHeight[i - 1] + a / stairWidth[i]
        }

        normalTable = Table(x1, a, stairWidth, stairHeight)
    }

    private fun expZiggurat(): Double {
        var iter = 0
        do {
            val stairId = basicRandGenerator() and 255
            val x = uniform(0.0, expTable.stairWidth[stairId]) // get horizontal coordinate
            if (x < expTable.stairWidth[stairId + 1]) {
                /// if we are under the upper stair - accept
                return x
            }
            if (stairId == 0) {
                // if we catch the tail
                return expTable.x1 + expZiggurat()
            }
            if (uniform(expTable.stairHeight[stairId - 1], expTable.stairHeight[stairId]) < exp(-x)) {
                // if we are under the curve - accept
                return x
            }
            // rejection - go back
        } while (++iter <= 1e9) // one billion should be enough to be sure there is a bug

        return Double.NaN // fail due to some error
    }

    private fun exponential(rate: Double): Double {
        return expZiggurat() / rate
    }

    /**
     * min - minimal value
     * mean - mathematical expectation
     */
    fun exponential(min: Double, mean: Double): Double {
        return if (mean <= min) {
            Double.NaN
        } else {
            min + expZiggurat() * (mean - min)
        }
    }

    fun exponential(min: Double, mean: Double, count: Int): Array<Double> {
        return if (mean <= min) {
            emptyArray()
        } else {
            Array(count) { exponential(min, mean) }
        }
    }

    private fun normalZiggurat(): Double {
        var iter = 0

        do {
            val b = basicRandGenerator();
            val stairId = b and 255
            var x = uniform(0.0, normalTable.stairWidth[stairId]) // get horizontal coordinate

            if (x < normalTable.stairWidth[stairId + 1]) {
                return x;
            }

            // handle the base layer
            if (stairId == 0) {
                var z = -1.0
                var y: Double
                // we don't have to generate another exponential variable as we already have one
                if (z > 0) {
                    x = exponential(normalTable.x1)
                    z -= 0.5 * x * x
                }
                // if previous generation wasn't successful
                if (z <= 0) {
                    do {
                        x = exponential(normalTable.x1)
                        y = exponential(1.0)
                        z = y - 0.5 * x * x // we storage this value as after acceptance it becomes exponentially distributed
                    } while (z <= 0)
                }
                x += normalTable.x1

                return x
            }

            // handle the wedges of other stairs
            if (uniform(normalTable.stairHeight[stairId - 1], normalTable.stairHeight[stairId]) < exp(-.5 * x * x)) {
                return x
            }
        } while (++iter <= 1e9)

        return Double.NaN
    }

    /**
     * min - minimal value
     * mean - mathematical expectation
     */
    fun normal(min: Double, mean: Double): Double {
        return if (mean <= min) {
            Double.NaN
        } else {
            min + normalZiggurat() * (mean - min)
        }
    }

    fun normal(min: Double, mean: Double, count: Int): Array<Double> {
        return if (mean <= min) {
            emptyArray()
        } else {
            Array(count) { normal(min, mean) }
        }
    }
}