#include "ghedxpch.h"
#include "CompilerInclude.h"

#include "core/io/File.h"
#include "core/logging/Logger.h"

#include <format>

namespace Ghurund::Engine::DirectX {
	HRESULT __stdcall CompilerInclude::Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes) {
		WString fullPath;
		AString aFileName = pFileName;
		WString fileName = convertText<char, wchar_t>(aFileName);

		// TODO: support library includes
		switch (IncludeType) {
		case D3D_INCLUDE_LOCAL: // #include "FILE"
		{
			fullPath = shaderDir / fileName;
			if (!File(FilePath(fullPath)).Exists) {
				auto text = std::format(_T("'{}' doesn't exist.\n"), fullPath);
				Logger::log(LogType::ERR0R, text.c_str());
				return E_FAIL;
			}
			break;
		}
		case D3D_INCLUDE_SYSTEM: // #include <FILE>
		{
			bool found = false;
			for (auto& systemDir : systemDirs) {
				fullPath = systemDir / fileName;
				if (File(FilePath(fullPath)).Exists) {
					found = true;
					break;
				}
			}
			if (!found) {
				auto text = std::format(_T("'{}' doesn't exist.\n"), fullPath);
				Logger::log(LogType::ERR0R, text.c_str());
				return E_FAIL;
			}
			break;
		}
		default:
			auto text = std::format(_T("Unknown include type: {}.\n"), (uint32_t)IncludeType);
			Logger::log(LogType::ERR0R, text.c_str());
			return E_FAIL;
		}

		File file = File(FilePath(fullPath));
		Buffer buffer;
		try {
			file.read(buffer);
		} catch (...) {
			auto text = std::format(_T("Failed to load include file: '{}'.\n"), fullPath);
			Logger::log(LogType::ERR0R, text.c_str());
			return E_FAIL;
		}

		*ppData = ghnew byte[buffer.Size];
		memcpy((void*)*ppData, buffer.Data, buffer.Size);
		*pBytes = (UINT)buffer.Size;

		return S_OK;
	}
}
