package ru.chudakov

import ru.chudakov.generator.Distribution
import ru.chudakov.generator.Generator
import ru.chudakov.proto.MessageProto
import ru.chudakov.proto.MessageProto.TMessage.newBuilder
import java.net.InetAddress
import java.net.InetSocketAddress
import java.nio.ByteBuffer
import java.nio.channels.ServerSocketChannel


class Sender(
        private val generator: Generator,
        private val distribution: Distribution,
        private val param1: Int,
        private val param2: Int
) {
    fun run() {
        val serverSocketChannel = ServerSocketChannel.open()
        serverSocketChannel.bind(InetSocketAddress(InetAddress.getByName("127.0.0.1"), 27015))

        val messageCount = generateNumber()

        for (i in 0..messageCount) {
            println("Waiting for client :P")
            val client = serverSocketChannel.accept()

            Thread.sleep(generateNumber().toLong() / 10)

            val responseMsg = generateMsg();
            val byteBuffer = ByteBuffer.allocate(1024 * 1024)

            byteBuffer.put(responseMsg.toByteArray())
            byteBuffer.flip()
            client.write(byteBuffer)
            client.close()
        }

        val client = serverSocketChannel.accept()
        val byteBuffer = ByteBuffer.allocate(1024 * 1024)

        byteBuffer.put(getSTopMsg().toByteArray())
        byteBuffer.flip()
        client.write(byteBuffer)
        client.close()
    }

    private fun generateNumber(): Int {
        return when (distribution) {
            Distribution.EXPONENTIAL -> generator.exponential(param1.toDouble(), param2.toDouble()).toInt()
            Distribution.UNIFORM -> generator.uniform(param1.toDouble(), param2.toDouble()).toInt()
            Distribution.NORMAL -> generator.normal(param1.toDouble(), param2.toDouble()).toInt()
        }
    }

    private fun generateMsg(): MessageProto.TMessage {
        val builder = newBuilder()
        var number = generateNumber() and 3
        while (number == 0) {
            number = generateNumber() and 3
        }
        var size = 0L
        when (number) {
            1 -> {
                builder.type = MessageProto.EType.FIBONACCI
                size = 1
            }
            2 -> {
                builder.type = MessageProto.EType.POW
                size = 2
            }
            3 -> {
                builder.type = MessageProto.EType.BUBBLE_SORT_UINT64
                size = generateNumber().toLong()
            }
            else -> error("Error, something went wrong")
        }
        builder.size = size
        for (i in 0 until size) {
            builder.addData(generateNumber())
        }

        return builder.build();
    }

    private fun getSTopMsg(): MessageProto.TMessage {
        val builder = newBuilder()
        builder.type = MessageProto.EType.STOP;
        builder.size = 0

        return builder.build()
    }
}