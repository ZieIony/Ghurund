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
        static const char *WIDTH;
        static const char *HEIGHT;

        static const char *PARTY_COLOR;
        static const char *RANDOM;
        
        static const char *DIRECTION;
        static const char *POSITION;
        static const char *ROTATION;
        static const char *SCALE;
        static const char *TARGET;
        static const char *UP;
        static const char *RIGHT;
        static const char *FOV;
        static const char *ZNEAR;
        static const char *ZFAR;
      
        static const char *WORLD;
        static const char *VIEW;
        static const char *PROJECTION;

        Parameter(const String &providerName, const ASCIIString &name, size_t size) {
            const char *mbName = toMultiByte(providerName.getData());
            this->name = mbName;
            delete[] mbName;
            this->name.add(name.getData());
            this->value = ghnew BYTE[size];
            this->size = size;
        }

        Parameter(const ASCIIString &name, size_t size) {
            this->name = name;
            this->value = ghnew BYTE[size];
            this->size = size;
        }

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