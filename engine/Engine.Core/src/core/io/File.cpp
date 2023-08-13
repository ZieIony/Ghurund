#include "ghcpch.h"
#include "File.h"

#include "core/logging/Logger.h"
#include <core/Exceptions.h>

namespace Ghurund::Core {
	const size_t File::getSize() const {
		HANDLE handle = CreateFileW(path.toString().Data, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		DWORD derr = GetLastError();
		if (handle == INVALID_HANDLE_VALUE) {
			auto message = std::format(_T("couldn't open file '{}'\n"), path.toString().Data);
			Logger::log(LogType::WARNING, message.c_str());
			AString exMessage = convertText<tchar, char>(String(message.c_str()));
			throw IOException(exMessage.Data);
		}
		// ignore files larger than DWORD size
		unsigned long fileSize = GetFileSize(handle, nullptr);
		CloseHandle(handle);
		return fileSize;
	}

	void File::read(Buffer& buffer) const {
		HANDLE handle = CreateFileW(path.toString().Data, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		DWORD derr = GetLastError();
		if (handle == INVALID_HANDLE_VALUE) {
			auto message = std::format(_T("couldn't open file '{}'\n"), path.toString().Data);
			AString exMessage = convertText<tchar, char>(String(message.c_str()));
			throw IOException(exMessage.Data);
		}
		unsigned long bytes;
		size_t size = GetFileSize(handle, nullptr);
		buffer.resize(size);
		void* data = buffer.Data;
		ReadFile(handle, data, (DWORD)size, &bytes, nullptr);
		CloseHandle(handle);
		if (bytes != size) {
			auto message = std::format(_T("read {} bytes from {} bytes long file '{}'\n"), bytes, size, path.toString().Data);
			Logger::log(LogType::WARNING, message.c_str());
			AString exMessage = convertText<tchar, char>(String(message.c_str()));
			throw IOException(exMessage.Data);
		}
	}

	void File::read(void*& data, size_t& size) const {
		HANDLE handle = CreateFileW(path.toString().Data, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		DWORD derr = GetLastError();
		if (handle == INVALID_HANDLE_VALUE) {
			auto message = std::format(_T("couldn't open file '{}'\n"), path.toString().Data);
			Logger::log(LogType::WARNING, message.c_str());
			AString exMessage = convertText<tchar, char>(String(message.c_str()));
			throw IOException(exMessage.Data);
		}
		if (data != nullptr)
			delete[] data;
		unsigned long bytes;
		size = GetFileSize(handle, nullptr);
		data = ghnew BYTE[size];
		ReadFile(handle, data, (DWORD)size, &bytes, nullptr);
		CloseHandle(handle);
		if (bytes != size) {
			auto message = std::format(_T("read {} bytes from {} bytes long file '{}'\n"), bytes, size, path.toString().Data);
			Logger::log(LogType::WARNING, message.c_str());
			AString exMessage = convertText<tchar, char>(String(message.c_str()));
			throw IOException(exMessage.Data);
		}
	}

	void File::write(const void* data, size_t size) const {
		HANDLE handle = CreateFileW(path.toString().Data, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (handle == INVALID_HANDLE_VALUE) {
			auto message = std::format(_T("couldn't open file '{}'\n"), path.toString().Data);
			Logger::log(LogType::WARNING, message.c_str());
			AString exMessage = convertText<tchar, char>(String(message.c_str()));
			throw IOException(exMessage.Data);
		}
		unsigned long bytes;
		WriteFile(handle, data, (DWORD)size, &bytes, nullptr);
		if (bytes != size) {
			auto message = std::format(_T("wrote {} bytes out of {} bytes to file '{}'\n"), bytes, size, path.toString().Data);
			Logger::log(LogType::WARNING, message.c_str());
			AString exMessage = convertText<tchar, char>(String(message.c_str()));
			throw IOException(exMessage.Data);
		}
		CloseHandle(handle);
	}

	void File::write(const Buffer& buffer) const {
		HANDLE handle = CreateFileW(path.toString().Data, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		if (handle == INVALID_HANDLE_VALUE) {
			auto message = std::format(_T("couldn't open file '{}'\n"), path.toString().Data);
			Logger::log(LogType::WARNING, message.c_str());
			AString exMessage = convertText<tchar, char>(String(message.c_str()));
			throw IOException(exMessage.Data);
		}
		unsigned long bytes;
		WriteFile(handle, buffer.Data, (DWORD)buffer.Size, &bytes, nullptr);
		if (bytes != buffer.Size) {
			auto message = std::format(_T("wrote {} bytes out of {} bytes to file '{}'\n"), bytes, buffer.Size, path.toString().Data);
			Logger::log(LogType::WARNING, message.c_str());
			AString exMessage = convertText<tchar, char>(String(message.c_str()));
			throw IOException(exMessage.Data);
		}
		CloseHandle(handle);
	}

	bool File::exists() const {
        DWORD attributes = GetFileAttributesW(path.toString().Data);

        return (attributes != INVALID_FILE_ATTRIBUTES &&
            !(attributes & FILE_ATTRIBUTE_DIRECTORY));
    }
}
