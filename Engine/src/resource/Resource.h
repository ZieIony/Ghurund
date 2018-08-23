#pragma once

#include "Ghurund.h"
#include "File.h"
#include "core/Object.h"
#include "core/MemoryStream.h"
#include "ResourceFormat.h"
#include "collection/Array.h"
#include "core/Pointer.h"

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
        virtual Status loadInternal(ResourceManager &resourceManager, MemoryInputStream &stream, LoadOption options) = 0;
        virtual Status saveInternal(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options) const = 0;

        virtual unsigned int getVersion() const {
            return NO_VERSION;
        }

        Status writeHeader(MemoryOutputStream &stream) const;
        Status readHeader(MemoryInputStream &stream);

    public:

        Resource() = default;

        Status load(ResourceManager &resourceManager, unsigned long *bytesRead = nullptr, LoadOption options = LoadOption::DEFAULT);
        Status load(ResourceManager &resourceManager, const String &fileName, unsigned long *bytesRead = nullptr, LoadOption options = LoadOption::DEFAULT);
        Status load(ResourceManager &resourceManager, File &file, unsigned long *bytesRead = nullptr, LoadOption options = LoadOption::DEFAULT);
        Status load(ResourceManager &resourceManager, MemoryInputStream &stream, LoadOption options = LoadOption::DEFAULT);

        Status save(ResourceManager &resourceManager, SaveOption options = SaveOption::DEFAULT) const;
        Status save(ResourceManager &resourceManager, const String &fileName, SaveOption options = SaveOption::DEFAULT);

        // this method doesn't write the file contents to disk, remember to call File::write()
        Status save(ResourceManager &resourceManager, File &file, SaveOption options = SaveOption::DEFAULT) const;
        Status save(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options = SaveOption::DEFAULT) const;


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