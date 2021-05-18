#pragma once

#include "core/string/WString.h"

namespace Ghurund {
    class ResourceFormat {
    private:
        WString extension;
        bool save, load;

    public:
        ResourceFormat(const WString& extension, bool save, bool load) {
            this->extension = extension;
            this->save = save;
            this->load = load;
        }

        ResourceFormat(const ResourceFormat& format) {
            this->extension = format.extension;
            this->save = format.save;
            this->load = format.load;
        }

        const WString& getExtension() const {
            return extension;
        }

        __declspec(property(get = getExtension)) const WString& Extension;

        bool canSave() const {
            return save;
        }

        bool canLoad() const {
            return load;
        }

        bool operator==(const ResourceFormat& format) const {
            return extension == format.extension && save == format.save && load == format.load;
        }
    };
}
