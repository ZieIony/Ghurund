#include "Resource.h"

namespace Ghurund {
    LoadOption operator |(LoadOption lhs, LoadOption rhs) {
        return (LoadOption)((std::underlying_type<LoadOption>::type)lhs|(std::underlying_type<LoadOption>::type)rhs);
    }

    bool operator &(LoadOption lhs, LoadOption rhs) {
        return (std::underlying_type<LoadOption>::type)lhs&(std::underlying_type<LoadOption>::type)rhs;
    }

    Status Resource::load(ResourceManager & resourceManager, unsigned long *bytesRead) {
        File file(fileName);
		if (!file.Exists) {
			Logger::log(_T("'%s' doesn't exist\n"), fileName);
			return Status::FILE_DOESNT_EXIST;
		}

        Status result = file.read();
		if (result != Status::OK)
            return result;
        return load(resourceManager, file.Data, file.Size, bytesRead);
    }
    
    Status Resource::load(ResourceManager & resourceManager, const String & fileName, unsigned long *bytesRead) {
        if(this->fileName.Length==0&&fileName.Length==0) {
            Logger::log(_T("Both resource's file name and the file name passed as parameter are empty\n"));
            return Status::INV_PARAM;
        } else if(fileName!=nullptr) {
            this->fileName = fileName;
        }

        return load(resourceManager, bytesRead);
    }
    
    Status Resource::load(ResourceManager & resourceManager, File & file, unsigned long *bytesRead) {
        this->fileName = file.Name;
        if(!file.Exists)
            return Status::FILE_DOESNT_EXIST;
        Status result;
        if(file.Size==0) {
            result = file.read();
            if(result!=Status::OK)
                return result;
        }
        result = load(resourceManager, file.Data, file.Size, bytesRead);
        valid = result == Status::OK;
        return result;
    }
    
    Status Resource::load(ResourceManager & resourceManager, const void * data, unsigned long size, unsigned long *bytesRead) {
        Status result;
        if(isVersioned()) {
            MemoryInputStream stream = MemoryInputStream(data);
            if(stream.readUInt()!=getVersion()||getVersion()==NO_VERSION)
                return Status::WRONG_RESOURCE_VERSION;
            if(strcmp(stream.readASCII(), typeid(*this).name())!=0)
                return Status::WRONG_RESOURCE_TYPE;
            clean();
            unsigned long headerBytesRead = stream.getBytesRead();
            result = loadInternal(resourceManager, ((BYTE*)data)+stream.getBytesRead(), size-stream.getBytesRead(), bytesRead);
            if(bytesRead!=nullptr)
                *bytesRead += headerBytesRead;
        } else {
            clean();
            result = loadInternal(resourceManager, data, size, bytesRead);
        }
        valid = result == Status::OK;
        return result;
    }
    
    Status Resource::save(ResourceManager &resourceManager) const {
        File file(this->fileName);
        void *data = nullptr;
        unsigned long size;
        Status result = save(resourceManager, &data, &size);
        if(result!=Status::OK)
            return result;
        file.setData(data, size);
        delete[] data;
        return file.write();
    }
    
    Status Resource::save(ResourceManager &resourceManager, const String &fileName) {
        if(this->fileName.Length==0&&fileName.Length==0) {
            Logger::log(_T("Both resource's file name and the file name passed as parameter are null\n"));
            return Status::INV_PARAM;
        } else if(fileName!=nullptr) {
            this->fileName = fileName;
        }

        return save(resourceManager);
    }

    Status Resource::save(ResourceManager &resourceManager, File & file) const {
        void *data = nullptr;
        unsigned long size;
        Status result = save(resourceManager, &data, &size);
        if(result!=Status::OK)
            return result;
        file.setData(data, size);
        return Status::OK;
    }
    
    Status Resource::save(ResourceManager &resourceManager, void **data, unsigned long *size) const {
        Status result;
        if(isVersioned()) {
            if(getVersion()==NO_VERSION)
                return Status::WRONG_RESOURCE_VERSION;
            void *dataInternal = nullptr;
            unsigned long sizeInternal;
            result = saveInternal(resourceManager, &dataInternal, &sizeInternal);
            if(result!=Status::OK)
                return result;
            MemoryOutputStream stream;
            stream.writeUInt(getVersion());
            stream.writeASCII(typeid(*this).name());
            stream.writeBytes(dataInternal, sizeInternal);
            delete[] dataInternal;
            *data = ghnew BYTE[stream.getBytesWritten()];
            memcpy(*data, stream.getData(), stream.getBytesWritten());
            *size = stream.getBytesWritten()+sizeInternal;
        } else {
            result = saveInternal(resourceManager, data, size);
        }
        return result;
    }
}