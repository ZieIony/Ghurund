#pragma once

namespace Ghurund {
    class ResourceFormat {
    private:
        const wchar_t* extension = nullptr;
        bool save, load;

    public:
        ResourceFormat(const wchar_t* extension, bool save, bool load) {
            this->extension = extension;
            this->save = save;
            this->load = load;
        }

        ResourceFormat(const ResourceFormat& format) {
            this->extension = format.extension;
            this->save = format.save;
            this->load = format.load;
        }

        const wchar_t* getExtension() const {
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
