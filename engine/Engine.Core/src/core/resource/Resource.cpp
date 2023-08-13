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

	void Resource::writeHeader(MemoryOutputStream& stream) const {
		unsigned int hash = hashCode(Type.Name.Data);
		stream.writeUInt(hash);
		stream.writeUInt(getVersion());
	}

	void Resource::readHeader(MemoryInputStream& stream) {
		if (stream.Size < stream.BytesRead + sizeof(unsigned int) * 2) {
			Logger::log(LogType::ERR0R, _T("EOF\n"));
			throw InvalidDataException("EOF");
		}
		unsigned int hash = hashCode(Type.Name.Data);
		uint32_t h = stream.readUInt();
		if (h != hash) {
			auto message = std::format(_T("Invalid resource type code (expected: {}, read: {})\n"), hash, h);
			Logger::log(LogType::ERR0R, message.c_str());
			AString exMessage = convertText<tchar, char>(String(message.c_str()));
			throw InvalidDataException(exMessage.Data);
		}
		uint32_t v = stream.readUInt();
		if (v != getVersion()) {
			auto message = std::format(_T("Invalid version number (expected: {}, read: {})\n"), getVersion(), v);
			Logger::log(LogType::ERR0R, message.c_str());
			AString exMessage = convertText<tchar, char>(String(message.c_str()));
			throw InvalidDataException(exMessage.Data);
		}
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

	void Resource::load(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
		try {
			loadInternal(workingDir, stream, options);
			valid = true;
		} catch (std::exception e) {
			valid = false;
			throw e;
		}
	}

	void Resource::save(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
		saveInternal(workingDir, stream, options);
    }
    
    void Resource::setPath(const ResourcePath* path) {
        delete this->path;
        if (path) {
            this->path = ghnew ResourcePath(*path);
        } else {
            this->path = nullptr;
        }
	}
}