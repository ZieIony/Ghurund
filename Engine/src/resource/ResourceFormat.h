#pragma once

#include "Ghurund.h"
#include "File.h"
#include "core/Object.h"
#include "core/MemoryStream.h"

using namespace std;

namespace Ghurund {
    class ResourceFormat {
    private:
        unsigned int value;
        const char *extension;
        bool save, load;

    public:
        static const ResourceFormat &AUTO,
            &ENTITY,
            &HLSL, &SHADER,
            &JPG,
            &MATERIAL;

        static const ResourceFormat values[];

        static const ResourceFormat &fromValue(unsigned int value) {
            if(value==HLSL.value) {
                return HLSL;
            } else if(value==SHADER.value) {
                return SHADER;
            } else {
                return AUTO;
            }
        }

        ResourceFormat(unsigned int value, const char *extension, bool save, bool load) {
            this->value = value;
            this->extension = extension;
            this->save = save;
            this->load = load;
        }

        unsigned int getValue() const {
            return value;
        }

        operator unsigned int() const { return value; }

        const char *getExtension() const {
            return extension;
        }

        bool canSave() const {
            return save;
        }

        bool canLoad() const {
            return load;
        }
    };
}