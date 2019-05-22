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
        if(!path)
            return Logger::log(LogType::ERR0R, Status::INV_PARAM, _T("File path is empty\n"));

        File file(*path);
        if(!file.Exists)
            return Logger::log(LogType::ERR0R, Status::FILE_DOESNT_EXIST, _T("'%s' doesn't exist\n"), path->get().getData());

        Status result = file.read();
        if(result != Status::OK)
            return result;

        Logger::log(LogType::INFO, _T("Loading '%s'\n"), (const tchar*)path->get());
        MemoryInputStream stream(file.Data, file.Size);
        result = load(resourceManager, context, path->Directory, stream, options);
        if(bytesRead!=nullptr)
            *bytesRead = stream.BytesRead;
        return result;
    }

    Status Resource::load(ResourceManager &resourceManager, ResourceContext &context, const FilePath &path, unsigned long *bytesRead, LoadOption options) {
        FilePath *p = ghnew FilePath(path.AbsolutePath);
        delete this->path;
        this->path = p;

        return load(resourceManager, context, bytesRead, options);
    }

    Status Resource::load(ResourceManager &resourceManager, ResourceContext &context, File & file, unsigned long *bytesRead, LoadOption options) {
        if(!file.Exists)
            return Status::FILE_DOESNT_EXIST;
        Status result;
        if(file.Size==0) {
            result = file.read();
            if(result!=Status::OK)
                return result;
        }

        FilePath *p = ghnew FilePath(file.Path);
        delete this->path;
        this->path = p;

        Logger::log(LogType::INFO, _T("Loading '%s'\n"), (const tchar*)path->get());
        MemoryInputStream stream(file.Data, file.Size);
        result = load(resourceManager, context, path->Directory, stream, options);
        if(bytesRead!=nullptr)
            *bytesRead = stream.BytesRead;
        return result;
    }

    Status Resource::load(ResourceManager &resourceManager, ResourceContext &context, const DirectoryPath &workingDir, MemoryInputStream &stream, LoadOption options) {
        Status result = loadInternal(resourceManager, context, workingDir, stream, options);
        valid = result == Status::OK;
        return result;
    }

    Status Resource::save(ResourceManager &resourceManager, ResourceContext &context, SaveOption options) const {
        if(!path)
            return Logger::log(LogType::ERR0R, Status::INV_PARAM, _T("File path is empty\n"));

        File file(*path);
        Status result = saveInternal(resourceManager, context, file, options);
        if(result!=Status::OK)
            return result;
        return file.write();
    }

    Status Resource::save(ResourceManager &resourceManager, ResourceContext &context, const FilePath &path, SaveOption options) {
        FilePath *p = ghnew FilePath(path);
        delete this->path;
        this->path = p;

        File file(*this->path);
        Status result = saveInternal(resourceManager, context, file, options);
        if(result!=Status::OK)
            return result;
        return file.write();
    }

    Status Resource::save(ResourceManager &resourceManager, ResourceContext &context, File & file, SaveOption options) {
        FilePath *p = ghnew FilePath(file.Path);
        delete this->path;
        this->path = p;

        return saveInternal(resourceManager, context, file, options);
    }

    Status Resource::saveInternal(ResourceManager &resourceManager, ResourceContext &context, File & file, SaveOption options) const {
        if(file.Exists&&options&SaveOption::SKIP_IF_EXISTS)
            return Status::FILE_EXISTS;
        if(file.Exists&&!(options&SaveOption::OVERWRITE))
            return Status::FILE_EXISTS;

        MemoryOutputStream stream;
        Status result = save(resourceManager, context, file.Path.Directory, stream, options);
        if(result!=Status::OK)
            return result;
        file.setData(stream.Data, stream.BytesWritten);
        return Status::OK;
    }

    Status Resource::save(ResourceManager &resourceManager, ResourceContext &context, const DirectoryPath &workingDir, MemoryOutputStream &stream, SaveOption options) const {
        return saveInternal(resourceManager, context, workingDir, stream, options);
    }
}