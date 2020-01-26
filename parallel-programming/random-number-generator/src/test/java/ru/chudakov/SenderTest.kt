package ru.chudakov

import org.junit.jupiter.api.RepeatedTest
import org.junit.jupiter.api.Test
import ru.chudakov.generator.Generator

internal class SenderTest {

    @Test
    @RepeatedTest(30)
    fun generateMsgTest() {
        val generator = Generator()

        println(generator.uniform(1.0, 4.0).toInt())
    }
}