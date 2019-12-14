package ru.chudakov

import ru.chudakov.generator.Distribution
import ru.chudakov.generator.Generator

open class Main {
    companion object {
        @JvmStatic
        fun main(args: Array<String>) {
            if (args.size < 3) {
                error("Arguments must be: -mode -param1 - param2")
            }

            val distribution = when(args[0]) {
                "-uniform" -> Distribution.UNIFORM
                "-exponential" -> Distribution.EXPONENTIAL
                "-normal" -> Distribution.NORMAL
                else -> error("Mode must be: uniform | exponential | normal")
            }

            val param1: Int = args[1].toInt()
            val param2: Int = args[2].toInt()

            if (param1 < 1 || param2 < 1) {
                error("Params must be more 0")
            }

            val generator = Generator()
            val sender = Sender(generator, distribution, param1, param2);

            sender.run()
        }
    }
}