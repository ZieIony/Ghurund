#include "Resource.h"

namespace Ghurund {
    LoadOption operator |(LoadOption lhs, LoadOption rhs) {
        return (LoadOption)((std::underlying_type<LoadOption>::type)lhs|(std::underlying_type<LoadOption>::type)rhs);
    }

    bool operator &(LoadOption lhs, LoadOption rhs) {
        return (std::underlying_type<LoadOption>::type)lhs&(std::underlying_type<LoadOption>::type)rhs;
    }

    SaveOption operator |(SaveOption lhs, SaveOption rhs) {
        return (SaveOption)((std::underlying_type<SaveOption>::type)lhs|(std::underlying_type<SaveOption>::type)rhs);
    }

    bool operator &(SaveOption lhs, SaveOption rhs) {
        return (std::underlying_type<SaveOption>::type)lhs&(std::underlying_type<SaveOption>::type)rhs;
    }

    Status filterStatus(Status result, LoadOption option) {
        if(result==Status::ALREADY_LOADED)
            return Status::OK;
        return result;
    }

    Status filterStatus(Status result, SaveOption option) {
        if(result==Status::FILE_EXISTS&&option&SaveOption::SKIP_IF_EXISTS)
            return Status::OK;
        return result;
    }

    Status Resource::writeHeader(MemoryOutputStream & stream) const {
        unsigned int hash = hashCode(Type.Name);
        stream.write(hash);
        stream.write(getVersion());
        return Status::OK;
    }

    Status Resource::readHeader(MemoryInputStream & stream) {
        if(stream.Size<stream.BytesRead+sizeof(unsigned int)*2)
            return Status::UNEXPECTED_EOF;
        unsigned int hash = hashCode(Type.Name);
        if(stream.read<unsigned int>()!=hash)
            return Status::WRONG_RESOURCE_TYPE;
        if(stream.read<unsigned int>()!=getVersion())
            return Status::WRONG_RESOURCE_VERSION;
        return Status::OK;
    }

    Status Resource::load(ResourceManager &resourceManager, ResourceContext &context, unsigned long *bytesRead, LoadOption options) {
        File file(fileName);
        if(!file.Exists) {
            Logger::log(_T("'%s' doesn't exist\n"), fileName);
            return Status::FILE_DOESNT_EXIST;
        }

        Status result = file.read();
        if(result != Status::OK)
            return result;
        MemoryInputStream stream(file.Data, file.Size);
        result = load(resourceManager, context, stream, options);
        if(bytesRead!=nullptr)
            *bytesRead = stream.BytesRead;
        return result;
    }

    Status Resource::load(ResourceManager &resourceManager, ResourceContext &context, const String & fileName, unsigned long *bytesRead, LoadOption options) {
        if(fileName.Length==0) {
            Logger::log(_T("File name is empty\n"));
            return Status::INV_PARAM;
        }

        this->fileName = fileName;

        return load(resourceManager, context, bytesRead, options);
    }

    Status Resource::load(ResourceManager &resourceManager, ResourceContext &context, File & file, unsigned long *bytesRead, LoadOption options) {
        this->fileName = file.Name;
        if(!file.Exists)
            return Status::FILE_DOESNT_EXIST;
        Status result;
        if(file.Size==0) {
            result = file.read();
            if(result!=Status::OK)
                return result;
        }
        MemoryInputStream stream(file.Data, file.Size);
        result = load(resourceManager, context, stream, options);
        if(bytesRead!=nullptr)
            *bytesRead = stream.BytesRead;
        return result;
    }

    Status Resource::load(ResourceManager &resourceManager, ResourceContext &context, MemoryInputStream &stream, LoadOption options) {
        Status result = loadInternal(resourceManager, context, stream, options);
        valid = result == Status::OK;
        return result;
    }

    Status Resource::save(ResourceManager &resourceManager, SaveOption options) const {
        if(fileName.Length==0) {
            Logger::log(_T("File name is empty\n"));
            return Status::INV_PARAM;
        }

        File file(this->fileName);
        Status result = saveInternal(resourceManager, file, options);
        if(result!=Status::OK)
            return result;
        return file.write();
    }

    Status Resource::save(ResourceManager &resourceManager, const String &fileName, SaveOption options) {
        if(fileName.Length==0) {
            Logger::log(_T("File name is empty\n"));
            return Status::INV_PARAM;
        }

        this->fileName = fileName;

        File file(this->fileName);
        Status result = saveInternal(resourceManager, file, options);
        if(result!=Status::OK)
            return result;
        return file.write();
    }

    Status Resource::save(ResourceManager &resourceManager, File & file, SaveOption options) {
        this->fileName = file.Name;

        return saveInternal(resourceManager, file, options);
    }

    Status Resource::saveInternal(ResourceManager &resourceManager, File & file, SaveOption options) const {
        if(file.Exists&&options&SaveOption::SKIP_IF_EXISTS)
            return Status::FILE_EXISTS;
        if(file.Exists&&!(options&SaveOption::OVERWRITE))
            return Status::FILE_EXISTS;

        MemoryOutputStream stream;
        Status result = save(resourceManager, stream, options);
        if(result!=Status::OK)
            return result;
        file.setData(stream.Data, stream.BytesWritten);
        return Status::OK;
    }

    Status Resource::save(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options) const {
        return saveInternal(resourceManager, stream, options);
    }
}