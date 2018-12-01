#pragma once

#include "Ghurund.h"
#include "collection/String.h"
#include "Parameter.h"
#include "core/CriticalSection.h"
#include "graphics/Graphics.h"

namespace Ghurund {

    class ParameterManager {
    private:
        Map<ASCIIString, Parameter*> parameters;
        CriticalSection section;

        friend class Parameter;

        void lock() {
            section.enter();
        }

        void unlock() {
            section.leave();
        }

    public:
        ParameterManager() {
            add(Parameter::PARTY_COLOR, ParameterType::FLOAT);

            add(Parameter::RANDOM, ParameterType::FLOAT);

            add(Parameter::WORLD, ParameterType::MATRIX);
            add(Parameter::WORLD_IT, ParameterType::MATRIX);
            add(Parameter::VIEW_PROJECTION, ParameterType::MATRIX);
        }

        ~ParameterManager() {
			for(size_t i = 0; i<parameters.Size; i++)
                delete parameters.getValue(i);
		}

        Parameter *add(const ASCIIString &name, const ParameterType &type) {
            if(parameters.contains(name))
                return parameters.get(name);
            Parameter *parameter = ghnew Parameter(name, type);
            parameter->manager = this;
            parameter->index = parameters.Size;
            parameters.set(name, parameter);
            return parameter;
        }

        Parameter *get(const ASCIIString &name) const {
            return parameters.get(name);
        }

        size_t getParameterCount() const {
            return parameters.Size;
        }

        Parameter *get(size_t index) const {
            return parameters.getValue(index);
        }

    };
}