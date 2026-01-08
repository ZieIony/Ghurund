#include "ghepch.h"

#include "Material.h"

#include "core/reflection/TypeBuilder.h"
#include "engine/parameter/ValueParameter.h"

#include <format>

namespace Ghurund::Engine {
    const Ghurund::Core::Type& Material::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = Ghurund::Core::TypeBuilder<Material>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void Material::initParameters() {
        for (auto& bi : shader->BufferInputs) {
            size_t size = 0;
            for (auto& vi : bi.ValueInputs) {
                size += vi.Size;
                auto p = IntrusivePointer(vi.makeParameter());
                valueParameters.add({ &vi, p });
                parameters.put(p.get());
            }
            constantBuffers.add(IntrusivePointer(memoryManager.makeConstantBuffer(size)));
        }
        for (auto& vi : shader->ValueInputs) {
            auto p = IntrusivePointer(vi.makeParameter());
            valueParameters.add({ &vi, p });
            parameters.put(p.get());
        }
        for (auto& ti : shader->TextureInputs) {
            auto p = IntrusivePointer(ti.makeParameter());
            textureParameters.add({ &ti, p });
            parameters.put(p.get());
        }
    }

	Material::Material(const Material& other):Resource(other), memoryManager(other.memoryManager), shader(other.shader) {
		if (shader) {
			shader->addReference();
			for (size_t i = 0; i < other.valueParameters.Size; i++) {
				auto p = IntrusivePointer((BaseValueParameter*)other.valueParameters[i].second->clone());
				valueParameters.add({ other.valueParameters[i].first, p });
				parameters.put(p.get());
			}
			for (size_t i = 0; i < shader->BufferInputs.Size; i++)
				constantBuffers.add(IntrusivePointer(memoryManager.makeConstantBuffer(other.constantBuffers[i]->Size)));
			for (size_t i = 0; i < other.textureParameters.Size; i++) {
				auto p = IntrusivePointer((TextureParameter*)other.textureParameters[i].second->clone());
				textureParameters.add({ other.textureParameters[i].first, p });
				parameters.put(p.get());
			}
		}
	}

    void Material::setParameters(ParameterCollection& defaults) {
        size_t i = 0;
        for (auto& [input, parameter] : valueParameters) {
            i++;
            auto p = parameter.get();
            if (p->IsEmpty) {
                auto global = (BaseValueParameter*)defaults.get(p->Name);
                if (!global) {
                    auto text = std::format(_T("Parameter for variable '{}' is missing.\n"), p->Name);
                    Logger::logOnce(LogType::WARNING, text.c_str(), i);
                    continue;
                }
                p = global;
                if (p->IsEmpty) {
                    auto text = std::format(_T("Parameter for variable '{}' is empty.\n"), p->Name);
                    Logger::logOnce(LogType::WARNING, text.c_str(), i);
                    continue;
                }
            }
            // TODO: shader root constants
            input->value = p->RawValue;
        }
		for (size_t b = 0; b < shader->BufferInputs.Size; b++) {
            auto& bi = shader->BufferInputs[b];
            auto& cb = constantBuffers[b];
            bi.constantBuffer = cb.get();
            for (auto& vi : bi.ValueInputs) {
                if (!vi.value) {
                    auto text = std::format(_T("Input '{}' is empty.\n"), vi.Name);
                    Logger::logOnce(LogType::WARNING, text.c_str(), i);
                    continue;
                }
                cb->setValue(vi.value, vi.Size, vi.Offset);
            }
        }
        for (auto& [input, parameter] : textureParameters) {
            i++;
            auto p = parameter.get();
            if (p->IsEmpty) {
                auto global = (TextureParameter*)defaults.get(p->Name);
                if (!global) {
                    auto text = std::format(_T("Parameter for variable '{}' is missing.\n"), p->Name);
                    Logger::logOnce(LogType::WARNING, text.c_str(), i);
                    continue;
                }
                p = global;
                if (p->IsEmpty) {
                    auto text = std::format(_T("Parameter for variable '{}' is empty.\n"), p->Name);
                    Logger::logOnce(LogType::WARNING, text.c_str(), i);
                    continue;
                }
            }
            input->Value = parameter->Value;
        }
    }
}