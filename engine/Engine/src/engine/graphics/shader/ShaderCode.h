#pragma once

#include <core/resource/Resource.h>

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class ShaderCode:public Resource {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ShaderCode::GET_TYPE();
#pragma endregion

    public:
        AString sourceCode;


#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return ShaderCode::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_HLSL = ResourceFormat(L"hlsl", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_HLSL };

        static const inline uint32_t VERSION = 0;
#pragma endregion
    };
}