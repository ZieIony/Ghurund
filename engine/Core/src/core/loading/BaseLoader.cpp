#include "ghcpch.h"
#include "BaseLoader.h"

#include "core/DataParsing.h"
#include "core/math/Int.h"
#include "core/reflection/TypeBuilder.h"

#include <format>

namespace Ghurund::Core {
	const Ghurund::Core::Type& BaseLoader::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<BaseLoader>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void BaseLoader::readHeader(MemoryInputStream& stream, const Ghurund::Core::Type& type, uint32_t version) {
		if (stream.Size < stream.Position + sizeof(unsigned int) * 2) {
			Logger::log(LogType::ERR0R, _T("EOF\n"));
			throw InvalidDataException("EOF");
		}
		unsigned int hash = hashCode(type.Name.Data);
		uint32_t h = stream.readUInt32();
		if (h != hash) {
			auto message = std::format(_T("Invalid resource type code (expected: {}, read: {})\n"), hash, h);
			Logger::log(LogType::ERR0R, message.c_str());
			AString exMessage = convertText<tchar, char>(String(message.c_str()));
			throw InvalidDataException(exMessage.Data);
		}
		uint32_t v = stream.readUInt32();
		if (v != version) {
			auto message = std::format(_T("Invalid version number (expected: {}, read: {})\n"), version, v);
			Logger::log(LogType::ERR0R, message.c_str());
			AString exMessage = convertText<tchar, char>(String(message.c_str()));
			throw InvalidDataException(exMessage.Data);
		}
	}

	void BaseLoader::checkXmlRoot(const XMLElement& xml, const WString& name) {
		if (xml.name != name) {
			auto message = std::format("Invalid resource type name (expected: {}, read: {})\n", name, xml.name);
			String exMessage = convertText<char, tchar>(AString(message.c_str()));
			Logger::log(LogType::ERR0R, exMessage.Data);
			throw InvalidDataException(message.c_str());
		}
		auto versionAttrIterator = xml.attributes.find(L"version");
		if (versionAttrIterator == xml.attributes.end())
			throw InvalidFormatException();
		uint32_t version = parse<uint32_t>(convertText<wchar_t, char>(versionAttrIterator->value));
		uint32_t supportedVersion = getResourceVersion();
		if (version != supportedVersion) {
			auto message = std::format(_T("Invalid version number (expected: {}, read: {})\n"), supportedVersion, version);
			Logger::log(LogType::ERR0R, message.c_str());
			AString exMessage = convertText<tchar, char>(String(message.c_str()));
			throw InvalidDataException(exMessage.Data);
		}
	}
}
