package ru.chudakov

import ru.chudakov.proto.MessageProto

data class Message(
        val type: MessageType,
        val size: Long,
        val data: Array<Int>
) {
    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (javaClass != other?.javaClass) return false

        other as Message

        if (type != other.type) return false
        if (size != other.size) return false
        if (!data.contentEquals(other.data)) return false

        return true
    }

    override fun hashCode(): Int {
        var result = type.hashCode()
        result = 31 * result + size.hashCode()
        result = 31 * result + data.contentHashCode()
        return result
    }
}

fun getProtoEType(type: MessageType): MessageProto.EType {
    return when (type) {
        MessageType.FIBONACCI -> MessageProto.EType.FIBONACCI
        MessageType.POW -> MessageProto.EType.POW
        MessageType.BUBBLE_SORT -> MessageProto.EType.BUBBLE_SORT_UINT64
        MessageType.STOP -> MessageProto.EType.STOP
    }
}