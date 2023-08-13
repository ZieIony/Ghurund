#pragma once

#include "Loader.h"
#include "ResourceFormat.h"
#include "Status.h"
#include "core/Pointer.h"
#include "core/io/DirectoryPath.h"
#include "core/resource/ResourcePath.h"

#include <stdint.h>

namespace Ghurund::Core {
    struct DataSize {
        uint64_t graphical, system;
    };

    class ResourceManager;
    class MemoryInputStream;
    class MemoryOutputStream;
    class File;

    class Resource: public Pointer {
    private:
        bool valid = false;
        ResourcePath* path = nullptr;

    protected:
        DataSize dataSize = {};

        ~Resource();

        virtual void loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
            throw NotImplementedException();
        };

        virtual void saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
            throw NotImplementedException();
        };

        virtual unsigned int getVersion() const {
            return 0;
        }

        void writeHeader(MemoryOutputStream& stream) const;
        void readHeader(MemoryInputStream& stream);

        static const Array<ResourceFormat>& GET_FORMATS();

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        void load(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options = LoadOption::DEFAULT);

        void save(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options = SaveOption::DEFAULT) const;

        virtual void reload() {
            valid = true;
            invalidate();
            addReference();
            //load();
            throw NotImplementedException();
            //release();
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

        const ResourcePath* getPath() const {
            return path;
        }

        void setPath(const ResourcePath* path);

        __declspec(property(get = getPath, put = setPath)) ResourcePath* Path;
        /*
        const DataSize& getSize() const {
            return dataSize;
        }

        __declspec(property(get = getSize)) const DataSize& Size;*/

        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Array<ResourceFormat>& FORMATS = GET_FORMATS();

        virtual const Array<ResourceFormat>& getFormats() const {
            return FORMATS;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat>& Formats;
    };
}