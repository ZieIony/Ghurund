#pragma once

#include "Ghurund.h"
#include "File.h"
#include "core/Object.h"
#include "core/MemoryStream.h"
#include "collection/Array.h"

using namespace std;

namespace Ghurund {
    class ResourceFormat {
    private:
        unsigned int value;
        const tchar *extension = nullptr;
        bool save, load;

        static const ResourceFormat* values[9];

    public:
        static const ResourceFormat &AUTO,
            &ENTITY,
            &HLSL, &SHADER,
            &JPG, &JPEG,
            &MATERIAL,
            &MODEL,
            &MESH, &OBJ;

        ResourceFormat() {
            extension = nullptr;
        }

        ResourceFormat(unsigned int value, const tchar *extension, bool save, bool load) {
            this->value = value;
            this->extension = extension;
            this->save = save;
            this->load = load;
        }

        ResourceFormat(const ResourceFormat &format) {
            this->value = format.value;
            this->extension = format.extension;
            this->save = format.save;
            this->load = format.load;
        }

        static const ResourceFormat &fromValue(unsigned int value) {
            if(value==HLSL.value) {
                return HLSL;
            } else if(value==SHADER.value) {
                return SHADER;
            } else {
                return AUTO;
            }
        }

        static const ResourceFormat** getValues() {
            return values;
        }

        static const size_t getValueCount() {
            return sizeof(values)/sizeof(values[0]);
        }

        unsigned int getValue() const {
            return value;
        }

        operator unsigned int() const { return value; }

        const tchar *getExtension() const {
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