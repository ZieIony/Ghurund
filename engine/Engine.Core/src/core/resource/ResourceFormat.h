#pragma once

#include "core/string/String.h"

namespace Ghurund::Core {
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

        inline const WString& getExtension() const {
            return extension;
        }

        __declspec(property(get = getExtension)) const WString& Extension;

        inline bool canSave() const {
            return save;
        }

        __declspec(property(get = canSave)) bool CanSave;

        inline bool canLoad() const {
            return load;
        }

        __declspec(property(get = canLoad)) bool CanLoad;

        inline bool operator==(const ResourceFormat& format) const {
            return extension == format.extension && save == format.save && load == format.load;
        }
    };
}
