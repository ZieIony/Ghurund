#include "ghcpch.h"
#include "Common.h"
#include "StandardTypes.h"

namespace Ghurund::Core {

    template<>
    const Type& getType<void>() {
        static Type TYPE = Type("void", 0);
        return TYPE;
    }

    template<>
    const Type& getType<uint32_t>() {
        static Type TYPE = Type("uint32_t", sizeof(uint32_t));
        return TYPE;
    }

    template<>
    const Type& getType<float>() {
        static Type TYPE = Type("float", sizeof(float));
        return TYPE;
    }

    template<>
    const Type& getType<bool>() {
        static Type TYPE = Type("bool", sizeof(bool));
        return TYPE;
    }

    template<>
    const Type& getType<char>() {
        static Type TYPE = Type("char", sizeof(char));
        return TYPE;
    }

    template<>
    const Type& getType<AString>() {
        static Type TYPE = Type(NAMESPACE_NAME, "AString", sizeof(AString));
        return TYPE;
    }

    template<>
    const Type& getType<WString>() {
        static Type TYPE = Type(NAMESPACE_NAME, "WString", sizeof(WString));
        return TYPE;
    }

    template<>
    const Type& getType<IntSize>() {
        static Type TYPE = Type(NAMESPACE_NAME, "IntSize", sizeof(IntSize));
        return TYPE;
    }

    template<>
    const Type& getType<FloatSize>() {
        static Type TYPE = Type(NAMESPACE_NAME, "FloatSize", sizeof(FloatSize));
        return TYPE;
    }

    template<>
    const Type& getType<IntPoint>() {
        static Type TYPE = Type(NAMESPACE_NAME, "IntPoint", sizeof(IntPoint));
        return TYPE;
    }

    template<>
    const Type& getType<FloatPoint>() {
        static Type TYPE = Type(NAMESPACE_NAME, "FloatPoint", sizeof(FloatPoint));
        return TYPE;
    }

    template<>
    const Type& getType<Matrix3x2>() {
        static Type TYPE = Type(NAMESPACE_NAME, "Matrix3x2", sizeof(Matrix3x2));
        return TYPE;
    }

    template<>
    const Type& getType<Buffer>() {
        static Type TYPE = Type(NAMESPACE_NAME, "Buffer", sizeof(Buffer));
        return TYPE;
    }
}