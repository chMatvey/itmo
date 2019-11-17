package ru.chudakov.generator

import org.junit.jupiter.api.Assertions.*
import org.junit.jupiter.api.RepeatedTest
import org.junit.jupiter.api.Test

internal class GeneratorTest {

    private val generator = Generator()
    private val min = 1.0
    private val max = 255.0
    private val mean = 122.0

    @Test
    @RepeatedTest(1000)
    fun uniform() {
        val number = generator.uniform(min, max)

        assertTrue(number in min..max)
    }

    @Test
    fun testUniform() {
        val count = 1000;

        assertTrue(generator.uniform(min, max, count).size == count)
    }

    @Test
    @RepeatedTest(1000)
    fun exponential() {
        val number = generator.exponential(min, mean)

        assertTrue(number in min..mean * mean)
    }

    @Test
    fun testExponential() {
        val count = 1000;

        assertTrue(generator.exponential(min, mean, count).size == count)
    }

    @Test
    @RepeatedTest(1000)
    fun normal() {
        val number = generator.normal(min, mean)

        assertTrue(number in min..mean * mean)
    }

    @Test
    fun testNormal() {
        val count = 1000;

        assertTrue(generator.normal(min, mean, count).size == count)
    }
}