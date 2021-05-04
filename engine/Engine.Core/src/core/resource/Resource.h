#pragma once

#include "Loader.h"
#include "ResourceFormat.h"
#include "Status.h"
#include "core/Pointer.h"
#include "core/io/DirectoryPath.h"
#include "core/io/FilePath.h"

#include <stdint.h>

namespace Ghurund {
    Status filterStatus(Status result, LoadOption option);
    Status filterStatus(Status result, SaveOption option);

    struct DataSize {
        uint64_t graphical, system;
    };

    class ResourceManager;
    class ResourceContext;
    class MemoryInputStream;
    class MemoryOutputStream;
    class File;

    class Resource: public Pointer {
    private:
        bool valid = false;
        FilePath* path = nullptr;

        Status saveInternal(File& file, SaveOption options) const;

    protected:
        DataSize dataSize;

        virtual Status loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
            return Status::NOT_IMPLEMENTED;
        };

        virtual Status saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
            return Status::NOT_IMPLEMENTED;
        };

        virtual unsigned int getVersion() const {
            return 0;
        }

        Status writeHeader(MemoryOutputStream& stream) const;
        Status readHeader(MemoryInputStream& stream);

        static const Ghurund::Type& GET_TYPE();

    public:
        ~Resource();

        Status load(size_t* bytesRead = nullptr, LoadOption options = LoadOption::DEFAULT);
        Status load(const FilePath& path, size_t* bytesRead = nullptr, LoadOption options = LoadOption::DEFAULT);
        Status load(File& file, size_t* bytesRead = nullptr, LoadOption options = LoadOption::DEFAULT);
        Status load(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options = LoadOption::DEFAULT);

        Status save(SaveOption options = SaveOption::DEFAULT) const;
        Status save(const FilePath& path, SaveOption options = SaveOption::DEFAULT);

        // this method doesn't write the file contents to disk, remember to call File::write()
        Status save(File& file, SaveOption options = SaveOption::DEFAULT);
        Status save(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options = SaveOption::DEFAULT) const;

        virtual void reload() {
            valid = true;
            invalidate();
            addReference();
            load();
            release();
        }

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

        const FilePath* getPath() const {
            return path;
        }

        void setPath(const FilePath* path);

        __declspec(property(get = getPath, put = setPath)) FilePath* Path;
        /*
        const DataSize& getSize() const {
            return dataSize;
        }

        __declspec(property(get = getSize)) const DataSize& Size;*/

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}