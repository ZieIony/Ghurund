#include "ghcpch.h"
#include "Resource.h"

#include "core/io/File.h"
#include "core/io/MemoryStream.h"
#include "core/logging/Formatter.h"
#include "core/logging/Logger.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {
    LoadOption operator |(LoadOption lhs, LoadOption rhs) {
        return (LoadOption)((std::underlying_type<LoadOption>::type)lhs | (std::underlying_type<LoadOption>::type)rhs);
    }

    bool operator &(LoadOption lhs, LoadOption rhs) {
        return (std::underlying_type<LoadOption>::type)lhs & (std::underlying_type<LoadOption>::type)rhs;
    }

    SaveOption operator |(SaveOption lhs, SaveOption rhs) {
        return (SaveOption)((std::underlying_type<SaveOption>::type)lhs | (std::underlying_type<SaveOption>::type)rhs);
    }

    bool operator &(SaveOption lhs, SaveOption rhs) {
        return (std::underlying_type<SaveOption>::type)lhs & (std::underlying_type<SaveOption>::type)rhs;
    }

    Status filterStatus(Status result, LoadOption option) {
        if (result == Status::ALREADY_LOADED)
            return Status::OK;
        return result;
    }

    Status filterStatus(Status result, SaveOption option) {
        if (result == Status::FILE_EXISTS && option & SaveOption::SKIP_IF_EXISTS)
            return Status::OK;
        return result;
    }

    Status Resource::writeHeader(MemoryOutputStream& stream) const {
        unsigned int hash = hashCode(Type.Name.Data);
        stream.writeUInt(hash);
        stream.writeUInt(getVersion());
        return Status::OK;
    }

    Status Resource::readHeader(MemoryInputStream& stream) {
        if (stream.Size < stream.BytesRead + sizeof(unsigned int) * 2)
            return Status::UNEXPECTED_EOF;
        unsigned int hash = hashCode(Type.Name.Data);
        if (stream.readUInt() != hash)
            return Status::WRONG_RESOURCE_TYPE;
        if (stream.readUInt() != getVersion())
            return Status::WRONG_RESOURCE_VERSION;
        return Status::OK;
    }

    const Ghurund::Core::Type& Resource::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Resource>(NAMESPACE_NAME, GH_STRINGIFY(Resource))
            .withModifiers(TypeModifier::ABSTRACT)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    const Array<ResourceFormat>& Resource::GET_FORMATS() {
        static const Array<ResourceFormat> formats = {};
        return formats;
    }

    Resource::~Resource() {
        delete path;
    }

    Status Resource::load(size_t* bytesRead, LoadOption options) {
        if (!path)
            return Logger::log(LogType::ERR0R, Status::INV_PARAM, _T("File path is empty\n"));

        File file(*path);
        if (!file.Exists) {
            auto text = std::format(_T("'{}' doesn't exist\n"), *path);
            return Logger::log(LogType::ERR0R, Status::FILE_DOESNT_EXIST, text.c_str());
        }

        Status result = file.read();
        if (result != Status::OK)
            return result;

        MemoryInputStream stream(file.Data, file.Size);
        result = load(path->Directory, stream, options);
        if (bytesRead != nullptr)
            *bytesRead = stream.BytesRead;
        return result;
    }

    Status Resource::load(const FilePath& path, size_t* bytesRead, LoadOption options) {
        FilePath* p = ghnew FilePath(path.AbsolutePath);
        delete this->path;
        this->path = p;

        return load(bytesRead, options);
    }

    Status Resource::load(File& file, size_t* bytesRead, LoadOption options) {
        if (!file.Exists)
            return Status::FILE_DOESNT_EXIST;
        Status result;
        if (file.Size == 0) {
            result = file.read();
            if (result != Status::OK)
                return result;
        }

        FilePath* p = ghnew FilePath(file.Path);
        delete this->path;
        this->path = p;

        MemoryInputStream stream(file.Data, file.Size);
        result = load(path->Directory, stream, options);
        if (bytesRead != nullptr)
            *bytesRead = stream.BytesRead;
        return result;
    }

    Status Resource::load(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
        Status result = loadInternal(workingDir, stream, options);
        valid = result == Status::OK;
        return result;
    }

    Status Resource::save(SaveOption options) const {
        if (!path)
            return Logger::log(LogType::ERR0R, Status::INV_PARAM, _T("File path is empty\n"));

        File file(*path);
        Status result = saveInternal(file, options);
        if (result != Status::OK)
            return result;
        return file.write();
    }

    Status Resource::save(const FilePath& path, SaveOption options) {
        FilePath* p = ghnew FilePath(path);
        delete this->path;
        this->path = p;

        File file(*this->path);
        Status result = saveInternal(file, options);
        if (result != Status::OK)
            return result;
        return file.write();
    }

    Status Resource::save(File& file, SaveOption options) {
        FilePath* p = ghnew FilePath(file.Path);
        delete this->path;
        this->path = p;

        return saveInternal(file, options);
    }

    Status Resource::saveInternal(File& file, SaveOption options) const {
        if (file.Exists && options & SaveOption::SKIP_IF_EXISTS)
            return Status::FILE_EXISTS;
        if (file.Exists && !(options & SaveOption::OVERWRITE))
            return Status::FILE_EXISTS;

        MemoryOutputStream stream;
        Status result = save(file.Path.Directory, stream, options);
        if (result != Status::OK)
            return result;
        file.setData(stream.Data, stream.BytesWritten);
        return Status::OK;
    }

    Status Resource::save(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
        return saveInternal(workingDir, stream, options);
    }
    
    void Resource::setPath(const FilePath* path) {
        delete this->path;
        if (path) {
            this->path = ghnew FilePath(*path);
        } else {
            this->path = nullptr;
        }
    }
}