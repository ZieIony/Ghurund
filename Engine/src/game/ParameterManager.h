#pragma once

#include "Ghurund.h"
#include "collection/TypeMap.h"
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

        inline void lock() {
            section.enter();
        }

        inline void unlock() {
            section.leave();
        }

    public:
        ParameterManager() {
            unsigned int emptyUint;
            XMFLOAT4 emptyColor;
            float emptyFloat;

            add(Parameter::WINDOW_WIDTH, &emptyUint, sizeof(emptyUint));
            add(Parameter::WINDOW_HEIGHT, &emptyUint, sizeof(emptyUint));

            add(Parameter::PARTY_COLOR, &emptyColor, sizeof(emptyColor));

            add(Parameter::RANDOM, &emptyFloat, sizeof(emptyFloat));
        }

        ~ParameterManager() {
            for(size_t i = 0; i<parameters.Size; i++)
                delete parameters.getValue(i);
        }

        Parameter *add(const ASCIIString &name, const void *value, size_t size) {
            Parameter *parameter = ghnew Parameter(name, value, size);
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

        /*void flip() {
            section.enter();
            section.leave();
        }*/
    };
}