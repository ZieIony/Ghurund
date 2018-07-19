#pragma once

#include "Ghurund.h"
#include "File.h"
#include "core/Object.h"
#include "core/MemoryStream.h"
#include "ResourceFormat.h"
#include "collection/Array.h"

using namespace std;

namespace Ghurund {
    enum class LoadOption {
    };

    LoadOption operator |(LoadOption lhs, LoadOption rhs);

    bool operator &(LoadOption lhs, LoadOption rhs);

    enum class SaveOption {
        // TODO: use SaveOption in Resource::save()
        OVERWRITE
    };

    class ResourceManager;

    class Resource {
    private:
        static const unsigned int NO_VERSION = -1;
        bool valid = false;
        String fileName;

    protected:
        virtual bool isVersioned()const {
            return false;
        }

        virtual unsigned int getVersion()const {
            return NO_VERSION;
        }

        // TODO: why size is of type unsigned long instead of size_t?
        virtual Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size) = 0;
        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size)const = 0;

        virtual void clean() = 0;

    public:

        Resource() = default;

        virtual ~Resource() = default;  // TODO: maybe this destructor should call clean()?

        Status load(ResourceManager &resourceManager);
        Status load(ResourceManager &resourceManager, const String &fileName);
        Status load(ResourceManager &resourceManager, File &file);
        Status load(ResourceManager &resourceManager, const void *data, unsigned long size);

        Status save(ResourceManager &resourceManager) const;
        Status save(ResourceManager &resourceManager, const String &fileName);

        // this method doesn't write the file contents to disk, remember to call File::write()
        Status save(ResourceManager &resourceManager, File &file)const;
        Status save(ResourceManager &resourceManager, void **data, unsigned long *size)const;


        virtual bool isValid() {
            return valid;
        }

        __declspec(property(get = isValid)) bool Valid;
        
        const String &getFileName() const {
            return fileName;
        }

        void setFileName(const String &fileName) {
            this->fileName = fileName;
        }

        __declspec(property(get = getFileName, put = setFileName)) String &FileName;

        virtual const Array<ResourceFormat> &getFormats() const = 0;

        virtual const ResourceFormat &getDefaultFormat() const = 0;
    };
}