#include "ghcpch.h"
#include "ResourcePath.h"

#include "core/Exceptions.h"
#include "core/logging/Logger.h"
#include "core/SharedPointer.h"

#include <format>

namespace Ghurund::Core {
	ResourcePath ResourcePath::parse(const WString& str) {
		if (str.startsWith(LIB_PROTOCOL)) {
			WString pathSimplified = str;
			pathSimplified.replace('\\', '/');
			size_t indexOfPath = pathSimplified.find(L"/", LIB_PROTOCOL.Length);
			WString libName = pathSimplified.substring(LIB_PROTOCOL.Length, indexOfPath - LIB_PROTOCOL.Length);
			WString path = pathSimplified.substring(indexOfPath + 1);
			return ResourcePath(libName, path);
		} else {
			return ResourcePath(FilePath(str));
		}
	}

	SharedPointer<Buffer> ResourcePath::resolveResource(const DirectoryPath& workingDir, LibraryList& libraries) const {
		if (type == Type::LIBRARY) {
			auto buffer = libraries.get(libName)->get(path);
			if (buffer == nullptr || buffer->Size == 0) {
				auto message = std::format(_T("the library '{}' doesn't contain '{}'\n"), libName, path);
				Logger::log(LogType::ERR0R, message.c_str());
				AString exMessage = convertText<tchar, char>(String(message.c_str()));
				throw InvalidParamException(exMessage.Data);
			}
			return buffer;
		} else {
			FilePath absolutePath = FilePath(path);
			if (!absolutePath.IsAbsolute)
				absolutePath = workingDir / FilePath(path);
			File file(absolutePath);
			if (!file.Exists) {
				auto message = std::format(_T("the file '{}' doesn't exist\n"), absolutePath);
				Logger::log(LogType::ERR0R, message.c_str());
				AString exMessage = convertText<tchar, char>(String(message.c_str()));
				throw InvalidParamException(exMessage.Data);
			}
			auto buffer = SharedPointer(ghnew Buffer());
			file.read(*buffer.get());
			return buffer;
		}
	}

	bool ResourcePath::exists(const DirectoryPath& workingDir, LibraryList& libraries) const {
		if (type == Type::LIBRARY) {
			return libraries.get(libName)->contains(path);
		} else {
			FilePath absolutePath = FilePath(path);
			if (!absolutePath.IsAbsolute)
				absolutePath = workingDir / FilePath(path);
			File file(absolutePath);
			return file.Exists;
		}
	}

	String ResourcePath::toString() const {
		if (type == Type::LIBRARY) {
			return String(std::format(_T("{}{}/{}"), LIB_PROTOCOL, libName, path).c_str());
		} else {
			return convertText<wchar_t, tchar>(path);
		}
	}
}
