#pragma once

#include "BufferConstant.h"
#include "CubeMapConstant.h"
#include "TextureConstant.h"
#include "ValueConstant.h"

#include "core/object/Noncopyable.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class ConstantsCollection:public Noncopyable {
    protected:
        List<ValueConstant> valueConstants;
        List<BufferConstant> bufferConstants;
        List<TextureConstant> textureConstants;
        List<CubeMapConstant> cubeMapConstants;
        List<TextureConstant> uavConstants;

    public:
        ConstantsCollection() {}

        inline const List<ValueConstant>& getValueConstants() const {
            return valueConstants;
        }

        __declspec(property(get = getValueConstants)) const List<ValueConstant>& ValueConstants;

        inline const List<BufferConstant>& getBufferConstants() const {
            return bufferConstants;
        }

        __declspec(property(get = getBufferConstants)) const List<BufferConstant>& BufferConstants;

        inline const List<TextureConstant>& getTextureConstants() const {
            return textureConstants;
        }

        __declspec(property(get = getTextureConstants)) const List<TextureConstant>& TextureConstants;

        inline const List<CubeMapConstant>& getCubeMapConstants() const {
            return cubeMapConstants;
        }

        __declspec(property(get = getCubeMapConstants)) const List<CubeMapConstant>& CubeMapConstants;

        inline const List<TextureConstant>& getUAVConstants() const {
            return textureConstants;
        }

        __declspec(property(get = getUAVConstants)) const List<TextureConstant>& UAVConstants;
    };
}
