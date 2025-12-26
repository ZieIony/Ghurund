#include "ghedxpch.h"
#include "CompilerInclude.h"

#include "core/logging/Logger.h"

#include <format>

namespace Ghurund::Engine::DirectX {
	HRESULT __stdcall CompilerInclude::Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes) {
		WString fullPath;
		AString aFileName = pFileName;
		WString fileName = convertText<char, wchar_t>(aFileName);
		FilePath filePath = FilePath(fileName);

		switch (IncludeType) {
		case D3D_INCLUDE_LOCAL: // #include "FILE"
		{
			try {
				auto buffer = resourceManager.resolveResource(filePath, shaderDir);
				*ppData = ghnew byte[buffer->Size];
				memcpy((void*)*ppData, buffer->Data, buffer->Size);
				*pBytes = (UINT)buffer->Size;
				return S_OK;
			} catch (InvalidParamException e) {
			}
			auto text = std::format(_T("Include {} could not be found in {}.\n"), filePath, shaderDir);
			Logger::log(LogType::ERR0R, text.c_str());
			return E_FAIL;
		}
		case D3D_INCLUDE_SYSTEM: // #include <FILE>
		{
			bool found = false;
			for (auto& systemDir : systemDirs) {
				try {
					auto buffer = resourceManager.resolveResource(filePath, systemDir);
					*ppData = ghnew byte[buffer->Size];
					memcpy((void*)*ppData, buffer->Data, buffer->Size);
					*pBytes = (UINT)buffer->Size;
					return S_OK;
				} catch (InvalidParamException e) {
				}
			}
			auto text = std::format(_T("Include {} could not be found in system include dirs.\n"), filePath);
			Logger::log(LogType::ERR0R, text.c_str());
			return E_FAIL;
		}
		default:
			auto text = std::format(_T("Unknown include type: {}.\n"), (uint32_t)IncludeType);
			Logger::log(LogType::ERR0R, text.c_str());
			return E_FAIL;
		}
	}
}
