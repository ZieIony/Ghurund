#include "ghcpch.h"
#include "Loader.h"

#include "core/reflection/TypeBuilder.h"
#include <format>

namespace Ghurund::Core {
	const Ghurund::Core::Type& Loader::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<Loader>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void Loader::readHeader(NotNull<MemoryInputStream> stream, const Ghurund::Core::Type& type, uint32_t version) {
		if (stream->Size < stream->BytesRead + sizeof(unsigned int) * 2) {
			Logger::log(LogType::ERR0R, _T("EOF\n"));
			throw InvalidDataException("EOF");
		}
		unsigned int hash = hashCode(type.Name.Data);
		uint32_t h = stream->readUInt32();
		if (h != hash) {
			auto message = std::format(_T("Invalid resource type code (expected: {}, read: {})\n"), hash, h);
			Logger::log(LogType::ERR0R, message.c_str());
			AString exMessage = convertText<tchar, char>(String(message.c_str()));
			throw InvalidDataException(exMessage.Data);
		}
		uint32_t v = stream->readUInt32();
		if (v != version) {
			auto message = std::format(_T("Invalid version number (expected: {}, read: {})\n"), version, v);
			Logger::log(LogType::ERR0R, message.c_str());
			AString exMessage = convertText<tchar, char>(String(message.c_str()));
			throw InvalidDataException(exMessage.Data);
		}
	}
}