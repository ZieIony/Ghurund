#pragma once

#include "ShaderSettings.h"

#include "core/collection/List.h"
#include "core/string/String.h"

#include <cstdint>

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    struct ShaderProgramSourceCode {
        AString sourceCode;
        List<SamplerInfo> samplers;

        ShaderProgramSourceCode(const AString& sourceCode):sourceCode(sourceCode) {}

        virtual ~ShaderProgramSourceCode() {}

        virtual uint64_t getDataSize() const {
			return sizeof(*this) + sourceCode.Length + samplers.Capacity * sizeof(SamplerInfo);
        }
    };
}
