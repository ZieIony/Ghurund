#pragma once

#include "ShaderSettings.h"

#include "core/resource/Resource.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    struct ShaderProgramSourceCode {
        AString sourceCode;

        ShaderProgramSourceCode(const AString& sourceCode):sourceCode(sourceCode) {}

        virtual ~ShaderProgramSourceCode() {}

        virtual uint64_t getDataSize() {
            return sizeof(this) + sourceCode.Length;
        }
    };

    class ShaderSource:public RefCountedObject {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ShaderSource::GET_TYPE();
#pragma endregion

    public:
        List<ShaderProgramSourceCode*> programs;
        List<SamplerInfo> samplers;
        ShaderSettings settings;

        ~ShaderSource() {
            programs.deleteItems();
        }

        inline uint64_t getDataSize() {
            uint64_t size = sizeof(this);
            size += samplers.Capacity * sizeof(SamplerInfo);
            for (auto program : programs)
                size += program->getDataSize();
            return size;
        }
    };
}
