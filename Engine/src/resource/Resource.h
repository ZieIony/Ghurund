#pragma once

#include "Ghurund.h"
#include "File.h"
#include "core/Object.h"
#include "core/MemoryStream.h"
#include "Context.h"

using namespace std;

namespace Ghurund {
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

        virtual const char *getType()const {
            return typeid(*this).name();
        }
        // TODO: why size is of type unsigned long instead of size_t?
        virtual Status loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size, unsigned int flags = 0) = 0;
        virtual Status saveInternal(ResourceManager &resourceManager, void **data, unsigned long *size, unsigned int flags = 0)const = 0;

    public:

        Resource() = default;

        /**
        * ?aduje plik z dysku
        * @param fileName ?cie?ka do pliku z danymi
        * @param loader obiekt zawieraj?cy wszystkie informacje niezb?dne do odczytania zasobu
        * @param flags ustawienia odczytywania
        * @return kod b??du wykonania
        */
        Status load(ResourceManager &resourceManager, const String *fileName, unsigned int flags = 0) {
            if(this->fileName.Length==0&&fileName==nullptr) {
                Logger::log(_T("Both resource's file name and the file name passed as parameter are null\n"));
                return Status::INV_PARAM;
            } else if(fileName!=nullptr) {
                this->fileName = *fileName;
            }

            File file(this->fileName);
            if(!file.Exists)
                return Status::FILE_DOESNT_EXIST;

            Status result = file.read();
            if(result!=Status::OK)
                return result;
            result = load(resourceManager, file.Data, file.Size, flags);
            valid = result == Status::OK;
            return result;
        }

        Status load(ResourceManager &resourceManager, File &file, unsigned int flags = 0) {
            this->fileName = file.Name;
            if(!file.Exists)
                return Status::FILE_DOESNT_EXIST;
            Status result;
            if(file.Size==0) {
                result = file.read();
                if(result!=Status::OK)
                    return result;
            }
            result = load(resourceManager, file.Data, file.Size, flags);
            valid = result == Status::OK;
            return result;
        }

        Status load(ResourceManager &resourceManager, const void *data, unsigned long size, unsigned int flags = 0) {
            Status result;
            if(isVersioned()) {
                MemoryInputStream stream = MemoryInputStream(data);
                if(stream.readUInt()!=getVersion()||getVersion()==NO_VERSION)
                    return Status::WRONG_RESOURCE_VERSION;
                if(strcmp(stream.readASCII(), getType())!=0)
                    return Status::WRONG_RESOURCE_TYPE;
                result = loadInternal(resourceManager, ((BYTE*)data)+stream.getBytesRead(), size-stream.getBytesRead(), flags);
            } else {
                result = loadInternal(resourceManager, data, size, flags);
            }
            valid = result == Status::OK;
            return result;
        }

        Status save(ResourceManager &resourceManager, const String *fileName = nullptr, unsigned int flags = 0) {
            if(this->fileName.Length==0&&fileName==nullptr) {
                Logger::log(_T("Both resource's file name and the file name passed as parameter are null\n"));
                return Status::INV_PARAM;
            } else if(fileName!=nullptr) {
                this->fileName = *fileName;
            }

            File file(this->fileName);
            void *data = nullptr;
            unsigned long size;
            Status result = save(resourceManager, &data, &size, flags);
            if(result!=Status::OK)
                return result;
            file.setData(data, size);
            return file.write();
        }

        // this method doesn't write the file contents to disk, remember to call File::write()
        Status save(ResourceManager &resourceManager, File &file, unsigned int flags = 0)const {
            void *data = nullptr;
            unsigned long size;
            Status result = save(resourceManager, &data, &size, flags);
            if(result!=Status::OK)
                return result;
            file.setData(data, size);
            return Status::OK;
        }

        Status save(ResourceManager &resourceManager, void **data, unsigned long *size, unsigned int flags = 0)const {
            Status result;
            if(isVersioned()) {
                if(getVersion()==NO_VERSION)
                    return Status::WRONG_RESOURCE_VERSION;
                void *dataInternal = nullptr;
                unsigned long sizeInternal;
                result = saveInternal(resourceManager, &dataInternal, &sizeInternal, flags);
                MemoryOutputStream stream;
                stream.writeUInt(getVersion());
                stream.writeASCII(getType());
                *data = ghnew BYTE[stream.getBytesWritten()];
                memcpy(*data, stream.getData(), stream.getBytesWritten());
                memcpy(((BYTE*)*data)+stream.getBytesWritten(), dataInternal, sizeInternal);
                *size = stream.getBytesWritten()+sizeInternal;
            } else {
                result = saveInternal(resourceManager, data, size, flags);
            }
            return result;
        }


        /**
        * sprawdza, czy zasób jest prawid³owy (gotowy do u¿ycia)
        * @return czy zasób prawid³owy
        */
        virtual bool isValid() {
            return valid;
        }

        /**
        * zwalnia dane ulotne zasobu, zas?b staje si? nieprawid?owy
        */
        virtual void invalidate() {
            valid = false;
        }

        /**
        * ustawia stan zasobu na prawid?owy
        */
        inline void reset() {
            valid = true;
        }

        const String &getFileName() const {
            return fileName;
        }

        void setFileName(const String &fileName) {
            this->fileName = fileName;
        }

        __declspec(property(get = getFileName, put = setFileName)) String &FileName;
    };
}