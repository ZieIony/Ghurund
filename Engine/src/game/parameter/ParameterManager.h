#pragma once

#include "Ghurund.h"
#include "Parameter.h"
#include "collection/String.h"
#include "core/CriticalSection.h"
#include "core/Object.h"
#include "graphics/Graphics.h"

namespace Ghurund {

    class ParameterManager: public Object {
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
        ParameterManager();

        ~ParameterManager();

        Parameter *add(const ASCIIString &name, const ParameterType &type);

        Parameter *get(const ASCIIString &name) const;

        size_t getParameterCount() const {
            return parameters.Size;
        }

        Parameter *get(size_t index) const {
            return parameters.getValue(index);
        }

        const static Ghurund::Type& TYPE;

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

    };
}