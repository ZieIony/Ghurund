#include "ghepch.h"
#include "Parameter.h"

#include "ParameterCollection.h"
#include "core/reflection/TypeBuilder.h"
#include "core/logging/Formatter.h"

namespace Ghurund::Engine {
    const Ghurund::Core::Type& Parameter::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Parameter>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void Parameter::initDefault(ParameterCollection& defaultParameterCollection) {
        auto defaultParameter = defaultParameterCollection.get(name);
        if (defaultParameter) {
            if (defaultParameter->Type == Type) {
                DefaultValue = defaultParameter;
            } else {
                auto message = std::format(
                    _T("parameter manager contains a parameter named '{}' but its type doesn't match (local: {}, default: {})\n"),
                    name, Type.Name, defaultParameter->Type.Name
                );
                Logger::log(LogType::WARNING, message.c_str());
            }
        } else {
            DefaultValue = nullptr;
        }
    }
}
