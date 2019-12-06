package ru.chudakov

import com.google.gson.Gson
import ru.chudakov.generator.Distribution
import ru.chudakov.generator.Generator

class Sender(
        private val generator: Generator,
        private val distribution: Distribution,
        private val param1: Int,
        private val param2: Int
) {
    private val stopMsg = Message(MessageType.STOP, 0, emptyArray())
    private val gson = Gson()

    fun run() {
        val messageCount = generateNumber()

        for (i in 0..messageCount) {
            Thread.sleep(generateNumber().toLong() and 127)

            println(gson.toJson(generateMsg()))
        }

        println(gson.toJson(stopMsg))
    }

    private fun generateNumber(): Int {
        return when (distribution) {
            Distribution.EXPONENTIAL -> generator.exponential(param1.toDouble(), param2.toDouble()).toInt()
            Distribution.UNIFORM -> generator.uniform(param1.toDouble(), param2.toDouble()).toInt()
            Distribution.NORMAL -> generator.normal(param1.toDouble(), param2.toDouble()).toInt()
        }
    }

    private fun generateNumbers(count: Int): Array<Int> {
        return when (distribution) {
            Distribution.EXPONENTIAL -> generator.exponential(param1.toDouble(), param2.toDouble(), count).map { it.toInt() and 255 }.toTypedArray()
            Distribution.UNIFORM -> generator.uniform(param1.toDouble(), param2.toDouble(), count).map { it.toInt() and 255 }.toTypedArray()
            Distribution.NORMAL -> generator.normal(param1.toDouble(), param2.toDouble(), count).map { it.toInt() and 255 }.toTypedArray()
        }
    }

    private fun generateMsg(): Message {
        var number = generateNumber() and 3
        while (number == 0) {
            number = generateNumber() and 3
        }

        return when (number) {
            1 -> {
                Message(MessageType.FIBONACCI, 1, generateNumbers(1))
            }
            2 -> {
                Message(MessageType.POW, 2, generateNumbers(2))
            }
            3 -> {
                val size = generateNumber()

                Message(MessageType.BUBBLE_SORT, size.toLong(), generateNumbers(size))
            }
            else -> {
                error("Error, something went wrong")
            }
        }
    }
}