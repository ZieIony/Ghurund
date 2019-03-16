#pragma once

#include "Ghurund.h"
#include "FileUtils.h"
#include "File.h"
#include "core/MemoryStream.h"
#include "ResourceFormat.h"
#include "collection/Array.h"
#include "core/Pointer.h"
#include "ResourceContext.h"


using namespace std;

namespace Ghurund {
    enum class LoadOption {
        DEFAULT = 0, DONT_WATCH = 1
    };

    LoadOption operator |(LoadOption lhs, LoadOption rhs);

    bool operator &(LoadOption lhs, LoadOption rhs);

    enum class SaveOption {
        DEFAULT = 0, OVERWRITE = 1, SKIP_IF_EXISTS = 2
    };

    SaveOption operator |(SaveOption lhs, SaveOption rhs);

    bool operator &(SaveOption lhs, SaveOption rhs);


    Status filterStatus(Status result, LoadOption option);
    Status filterStatus(Status result, SaveOption option);


    class ResourceManager;

    class Resource: public Pointer {
    private:
        bool valid = false;
        FilePath *path = nullptr;

        Status saveInternal(ResourceManager &resourceManager, File &file, SaveOption options) const;

    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, ResourceContext &context, const DirectoryPath &workingDir, MemoryInputStream &stream, LoadOption options) = 0;
        virtual Status saveInternal(ResourceManager &resourceManager, const DirectoryPath &workingDir, MemoryOutputStream &stream, SaveOption options) const = 0;

        virtual unsigned int getVersion() const {
            return 0;
        }

        Status writeHeader(MemoryOutputStream &stream) const;
        Status readHeader(MemoryInputStream &stream);

    public:

        Resource() = default;

        ~Resource() {
            delete path;
        }

        Status load(ResourceManager &resourceManager, ResourceContext &context, unsigned long *bytesRead = nullptr, LoadOption options = LoadOption::DEFAULT);
        Status load(ResourceManager &resourceManager, ResourceContext &context, const FilePath &path, unsigned long *bytesRead = nullptr, LoadOption options = LoadOption::DEFAULT);
        Status load(ResourceManager &resourceManager, ResourceContext &context, File &file, unsigned long *bytesRead = nullptr, LoadOption options = LoadOption::DEFAULT);
        Status load(ResourceManager &resourceManager, ResourceContext &context, const DirectoryPath &workingDir, MemoryInputStream &stream, LoadOption options = LoadOption::DEFAULT);

        Status save(ResourceManager &resourceManager, SaveOption options = SaveOption::DEFAULT) const;
        Status save(ResourceManager &resourceManager, const FilePath &path, SaveOption options = SaveOption::DEFAULT);

        // this method doesn't write the file contents to disk, remember to call File::write()
        Status save(ResourceManager &resourceManager, File &file, SaveOption options = SaveOption::DEFAULT);
        Status save(ResourceManager &resourceManager, const DirectoryPath &workingDir, MemoryOutputStream &stream, SaveOption options = SaveOption::DEFAULT) const;

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

        const FilePath *getPath() const {
            return path;
        }

        void setPath(const FilePath *path) {
            delete this->path;
            this->path = ghnew FilePath(*path);
        }

        __declspec(property(get = getPath, put = setPath)) FilePath *Path;
    };
}