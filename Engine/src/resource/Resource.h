#pragma once

#include "Ghurund.h"
#include "File.h"
#include "core/MemoryStream.h"
#include "ResourceFormat.h"
#include "collection/Array.h"
#include "core/Pointer.h"
#include "ResourceContext.h"


using namespace std;

namespace Ghurund {
    enum class LoadOption {
        DEFAULT = 0
    };

    LoadOption operator |(LoadOption lhs, LoadOption rhs);

    bool operator &(LoadOption lhs, LoadOption rhs);

    enum class SaveOption {
        DEFAULT = 0, OVERWRITE = 1, SKIP_IF_EXISTS = 2
    };

    SaveOption operator |(SaveOption lhs, SaveOption rhs);

    bool operator &(SaveOption lhs, SaveOption rhs);

    class ResourceManager;

    class Resource: public Pointer {
    private:
        static const unsigned int NO_VERSION = -1;
        bool valid = false;
        String fileName;

    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, ResourceContext &context, MemoryInputStream &stream, LoadOption options) = 0;
        virtual Status saveInternal(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options) const = 0;

        virtual unsigned int getVersion() const {
            return NO_VERSION;
        }

        Status writeHeader(MemoryOutputStream &stream) const;
        Status readHeader(MemoryInputStream &stream);

    public:

        Resource() = default;

        Status load(ResourceManager &resourceManager, ResourceContext &context, unsigned long *bytesRead = nullptr, LoadOption options = LoadOption::DEFAULT);
        Status load(ResourceManager &resourceManager, ResourceContext &context, const String &fileName, unsigned long *bytesRead = nullptr, LoadOption options = LoadOption::DEFAULT);
        Status load(ResourceManager &resourceManager, ResourceContext &context, File &file, unsigned long *bytesRead = nullptr, LoadOption options = LoadOption::DEFAULT);
        Status load(ResourceManager &resourceManager, ResourceContext &context, MemoryInputStream &stream, LoadOption options = LoadOption::DEFAULT);

        Status save(ResourceManager &resourceManager, SaveOption options = SaveOption::DEFAULT) const;
        Status save(ResourceManager &resourceManager, const String &fileName, SaveOption options = SaveOption::DEFAULT);

        // this method doesn't write the file contents to disk, remember to call File::write()
        Status save(ResourceManager &resourceManager, File &file, SaveOption options = SaveOption::DEFAULT) const;
        Status save(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options = SaveOption::DEFAULT) const;

        virtual void invalidate() {
            valid = false;
        }

        void setValid(bool valid) {
            this->valid = valid;
        }

        virtual bool isValid() const {
            return valid;
        }

        __declspec(property(get = isValid, put = setValid)) bool Valid;

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