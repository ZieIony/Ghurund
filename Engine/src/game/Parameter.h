#pragma once

#include "Ghurund.h"
#include "collection/String.h"

namespace Ghurund {
    class Parameter {
    private:
        ASCIIString name;
        BYTE *value;
        size_t size;
        unsigned int index;

        friend class ParameterManager;
        ParameterManager *manager;

    public:
        static const char *WINDOW_WIDTH;
        static const char *WINDOW_HEIGHT;
        static const char *PARTY_COLOR;
        static const char *RANDOM;
        
        Parameter(const ASCIIString &name, const void *value, size_t size) {
            this->name = name;
            this->value = ghnew BYTE[size];
            memcpy(this->value, value, size);
            this->size = size;
        }

        ~Parameter() {
            delete[] value;
        }

        inline const ASCIIString &getName() const {
            return name;
        }

        inline const void *getValue() const {
            return value;
        }

        void setValue(const void *value);
    };
}