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

        static const Array<const ResourceFormat*> values;

    public:
        static const ResourceFormat &AUTO,
            &ENTITY,
            &HLSL, &SHADER,
            &JPG, &JPEG,
            &MATERIAL;

        static const ResourceFormat &fromValue(unsigned int value) {
            if(value==HLSL.value) {
                return HLSL;
            } else if(value==SHADER.value) {
                return SHADER;
            } else {
                return AUTO;
            }
        }

        ResourceFormat(unsigned int value, const tchar *extension, bool save, bool load) {
            this->value = value;
            this->extension = copyStr(extension);
            this->save = save;
            this->load = load;
        }

        ResourceFormat(const ResourceFormat &format) {
            this->value = format.value;
            this->extension = copyStr(format.extension);
            this->save = format.save;
            this->load = format.load;
        }

        ~ResourceFormat() {
            delete[] extension;
        }

        static const Array<const ResourceFormat*> &getValues() {
            return values;
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