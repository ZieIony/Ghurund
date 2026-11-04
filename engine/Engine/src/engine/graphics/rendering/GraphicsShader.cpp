#include "ghepch.h"
#include "GraphicsShader.h"

#include "core/reflection/TypeBuilder.h"
#include "engine/parameter/ParameterCollection.h"
#include "engine/parameter/ValueParameter.h"
#include "engine/parameter/TextureParameter.h"

namespace Ghurund::Engine {
    const Ghurund::Core::Type& GraphicsShader::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<GraphicsShader>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    BaseValueInput* makeInput(ValueConstant& valueInput) {
        switch (valueInput.Type) {
        case ConstantType::INT:
            return ghnew ValueInput<IntParameter>(valueInput);
        case ConstantType::INT2:
            return ghnew ValueInput<Int2Parameter>(valueInput);
        case ConstantType::UINT:
            return ghnew ValueInput<UIntParameter>(valueInput);
        case ConstantType::BOOL:
            return ghnew ValueInput<BoolParameter>(valueInput);
        case ConstantType::FLOAT:
            return ghnew ValueInput<FloatParameter>(valueInput);
        case ConstantType::FLOAT2:
            return ghnew ValueInput<Float2Parameter>(valueInput);
        case ConstantType::FLOAT3:
            return ghnew ValueInput<Float3Parameter>(valueInput);
        case ConstantType::FLOAT4:
            return ghnew ValueInput<Float4Parameter>(valueInput);
        case ConstantType::MATRIX:
            return ghnew ValueInput<MatrixParameter>(valueInput);
        }
        throw std::invalid_argument("invalid valueInput type");
    }

    void GraphicsShader::init(NotNull<IGPUMemoryManager> memoryManager) {
        if (State == ResourceState::INITIALIZED)
            return;

        for (auto& bi : constants->BufferConstants) {
            for (auto& vi : bi.valueConstants) {
                auto input = makeInput(vi);
                valueInputs.add(input);
                inputs.add(input);
            }
            bi.constantBuffer = memoryManager->makeConstantBuffer(bi.size);
        }
        for (auto& vi : constants->ValueConstants) {
            auto input = makeInput(vi);
            valueInputs.add(input);
            inputs.add(input);
        }
        for (auto& ti : constants->TextureConstants) {
            auto input = ghnew TextureInput(ti);
            textureInputs.add(input);
            inputs.add(input);
        }
        for (auto& cmi : constants->CubeMapConstants) {
            auto input = ghnew CubeMapInput(cmi);
            cubeMapInputs.add(input);
            inputs.add(input);
        }
    }

    void GraphicsShader::applyInputs(ParameterCollection& globals) {
        uint32_t logId = 0;
        for (auto input : valueInputs) {
            logId++;
            if (input->IsEmpty) {
                auto global = (BaseValueParameter*)globals.get(input->Name);
                if (global && !global->IsEmpty) {
                    input->applyValue(global->RawValue);
                } else if (input->DefaultValue) {
                    input->applyValue(input->DefaultValue);
                } else {
                    auto text = std::format(_T("No value for input '{}'.\n"), input->Name);
                    Logger::logOnce(LogType::WARNING, text.c_str(), logId);
                    continue;
                }
            } else {
                // TODO: shader root constants
                input->applyValue();
            }
        }
        for (size_t b = 0; b < constants->BufferConstants.Size; b++) {
            auto& bc = constants->BufferConstants[b];
            auto& cb = bc.constantBuffer;
            for (auto& vi : bc.valueConstants) {
                if (!vi.Value) {
                    auto text = std::format(_T("No value for input '{}'.\n"), vi.Name);
                    Logger::logOnce(LogType::WARNING, text.c_str(), logId);
                    continue;
                }
                cb->setValue(vi.Value, vi.Size, vi.Offset);
            }
        }
        for (auto input : textureInputs) {
            logId++;
            if (input->IsEmpty) {
                auto global = (TextureParameter*)globals.get(input->Name);
                if (global && !global->IsEmpty) {
                    input->applyValue(global->Value);
                } else {
                    auto text = std::format(_T("No value for input '{}'.\n"), input->Name);
                    Logger::logOnce(LogType::WARNING, text.c_str(), logId);
                    continue;
                }
            } else {
                input->applyValue();
            }
        }
        for (auto input : cubeMapInputs) {
            logId++;
            if (input->IsEmpty) {
                auto text = std::format(_T("No value for input '{}'.\n"), input->Name);
                Logger::logOnce(LogType::WARNING, text.c_str(), logId);
                continue;
            } else {
                input->applyValue();
            }
        }
    }
}
