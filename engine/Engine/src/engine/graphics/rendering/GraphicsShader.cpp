#include "ghepch.h"
#include "GraphicsShader.h"

#include "core/reflection/TypeBuilder.h"

#include <DirectXMath.h>

namespace Ghurund::Engine {
    using namespace ::DirectX;

    const Ghurund::Core::Type& GraphicsShader::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<GraphicsShader>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    BaseValueInput* makeInput(ValueConstant& valueInput) {
        switch (valueInput.Type) {
        case ConstantType::INT:
            return ghnew ValueInput<int32_t>(valueInput);
        case ConstantType::INT2:
            return ghnew ValueInput<XMINT2>(valueInput);
        case ConstantType::UINT:
            return ghnew ValueInput<uint32_t>(valueInput);
        case ConstantType::BOOL:
            return ghnew ValueInput<bool>(valueInput);
        case ConstantType::FLOAT:
            return ghnew ValueInput<float>(valueInput);
        case ConstantType::FLOAT2:
            return ghnew ValueInput<XMFLOAT2>(valueInput);
        case ConstantType::FLOAT3:
            return ghnew ValueInput<XMFLOAT3>(valueInput);
        case ConstantType::FLOAT4:
            return ghnew ValueInput<XMFLOAT4>(valueInput);
        case ConstantType::MATRIX:
            return ghnew ValueInput<XMFLOAT4X4>(valueInput);
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

    void GraphicsShader::applyInputs() {
        uint32_t logId = 0;
        for (auto input : valueInputs) {
            logId++;
            if (input->IsEmpty) {
                if (input->DefaultValue) {
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
                auto text = std::format(_T("No value for input '{}'.\n"), input->Name);
                Logger::logOnce(LogType::WARNING, text.c_str(), logId);
                continue;
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
