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

    void Material::setParameters(ParameterManager& parameterManager) {
        size_t i = 0;
        for (auto& [input, parameter] : valueParameters) {
            i++;
            auto p = parameter.get();
            if (p->IsEmpty) {
                auto global = (BaseValueParameter*)parameterManager.Parameters.get(p->Name);
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
            p->apply(*input);
        }
        for (auto& [input, parameter] : textureParameters) {
            i++;
            auto p = parameter.get();
            if (p->IsEmpty) {
                auto global = (TextureParameter*)parameterManager.Parameters.get(p->Name);
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