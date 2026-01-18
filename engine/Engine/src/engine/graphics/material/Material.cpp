#include "ghepch.h"

#include "Material.h"

#include "core/reflection/TypeBuilder.h"
#include "engine/parameter/ParameterCollection.h"
#include "engine/parameter/ValueParameter.h"
#include "engine/parameter/TextureParameter.h"

#include <format>

namespace Ghurund::Engine {
    const Ghurund::Core::Type& Material::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = Ghurund::Core::TypeBuilder<Material>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    BaseValueInput* makeInput(ValueConstant& valueInput) {
        switch (valueInput.Type) {
        case InputType::INT:
            return ghnew ValueInput<IntParameter>(valueInput);
        case InputType::INT2:
            return ghnew ValueInput<Int2Parameter>(valueInput);
        case InputType::FLOAT:
            return ghnew ValueInput<FloatParameter>(valueInput);
        case InputType::FLOAT2:
            return ghnew ValueInput<Float2Parameter>(valueInput);
        case InputType::FLOAT3:
            return ghnew ValueInput<Float3Parameter>(valueInput);
        case InputType::FLOAT4:
            return ghnew ValueInput<Float4Parameter>(valueInput);
        case InputType::MATRIX:
            return ghnew ValueInput<MatrixParameter>(valueInput);
        }
        throw InvalidParamException();
    }

    void Material::initInputs() {
        for (auto& bi : shader->BufferConstants) {
            size_t size = 0;
            for (auto& vi : bi.ValueConstants) {
                size += vi.Size;
                auto input = makeInput(vi);
                valueInputs.add(input);
                inputs.add(input);
            }
            constantBuffers.add(IntrusivePointer(memoryManager.makeConstantBuffer(size)));
        }
        for (auto& vi : shader->ValueConstants) {
            auto input = makeInput(vi);
            valueInputs.add(input);
            inputs.add(input);
        }
        for (auto& ti : shader->TextureConstants) {
            auto input = ghnew TextureInput(ti);
            textureInputs.add(input);
            inputs.add(input);
        }
    }

	Material::Material(const Material& other):Resource(other), memoryManager(other.memoryManager), shader(other.shader) {
		if (shader) {
			shader->addReference();
			for (size_t i = 0; i < other.valueInputs.Size; i++) {
				auto input = (BaseValueInput*)other.valueInputs[i]->clone();
				valueInputs.add(input);
                inputs.add(input);
			}
			for (size_t i = 0; i < shader->BufferConstants.Size; i++)
				constantBuffers.add(IntrusivePointer(memoryManager.makeConstantBuffer(other.constantBuffers[i]->Size)));
			for (size_t i = 0; i < other.textureInputs.Size; i++) {
				auto input = other.textureInputs[i]->clone();
				textureInputs.add(input);
                inputs.add(input);
			}
		}
	}

    void Material::applyInputs(ParameterCollection& globals) {
		size_t i = 0;
		for (auto input : valueInputs) {
			i++;
			if (input->IsEmpty) {
				auto global = (BaseValueParameter*)globals.get(input->Name);
				if (global && !global->IsEmpty) {
					input->applyValue(global->RawValue);
				} else if (input->DefaultValue) {
					input->applyValue(input->DefaultValue);
				} else {
					auto text = std::format(_T("No value for input '{}'.\n"), input->Name);
					Logger::logOnce(LogType::WARNING, text.c_str(), i);
                    continue;
                }
            } else {
			    // TODO: shader root constants
                input->applyValue();
            }
		}
		for (size_t b = 0; b < shader->BufferConstants.Size; b++) {
            auto& bi = shader->BufferConstants[b];
            auto& cb = constantBuffers[b];
            bi.constantBuffer = cb.get();
            for (auto& vi : bi.ValueConstants) {
                if (!vi.Value) {
                    auto text = std::format(_T("No value for input '{}'.\n"), vi.Name);
                    Logger::logOnce(LogType::WARNING, text.c_str(), i);
                    continue;
                }
                cb->setValue(vi.Value, vi.Size, vi.Offset);
			}
		}
		for (auto input : textureInputs) {
			i++;
			if (input->IsEmpty) {
				auto global = (TextureParameter*)globals.get(input->Name);
				if (global && !global->IsEmpty) {
                    input->applyValue(global->Value);
				} else {
					auto text = std::format(_T("No value for input '{}'.\n"), input->Name);
					Logger::logOnce(LogType::WARNING, text.c_str(), i);
                    continue;
				}
            } else {
                input->applyValue();
            }
		}
    }
}