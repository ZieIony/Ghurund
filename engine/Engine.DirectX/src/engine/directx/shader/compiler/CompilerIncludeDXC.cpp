#include "ghedxpch.h"
#include "CompilerIncludeDXC.h"

#include <wrl/client.h>

namespace Ghurund::Engine::DirectX {
    using namespace Microsoft::WRL;

    HRESULT __stdcall CompilerIncludeDXC::LoadSource(LPCWSTR pFilename, IDxcBlob** ppIncludeSource) {
		FilePath filePath = FilePath(pFilename);
		SharedPointer<Buffer> buffer;

		bool found = false;
		try {
			auto absolutePath = ResourceManager::getAbsoluteOrLibPath(filePath, shaderDir);
			buffer = resourceManager.resolveResource(absolutePath);
			found = true;
		} catch (std::invalid_argument e) {
			for (auto& systemDir : systemDirs) {
				try {
					auto absolutePath = ResourceManager::getAbsoluteOrLibPath(filePath, systemDir);
					buffer = resourceManager.resolveResource(absolutePath);
					found = true;
					break;
				} catch (std::invalid_argument e) {
				}
			}
		}

		if (!found) {
			auto text = std::format(_T("Include \"{}\" could not be found in include dirs.\n"), filePath);
			Logger::log(LogType::ERR0R, text.c_str());
			return E_FAIL;
		}

		ComPtr<IDxcUtils> utils;
		DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(utils.GetAddressOf()));
		ComPtr<IDxcBlobEncoding> pEncoding;
        if (includedFiles.contains(filePath)) {
            static const char nullStr[] = " ";
            utils->CreateBlobFromPinned(nullStr, ARRAYSIZE(nullStr), DXC_CP_ACP, pEncoding.GetAddressOf());
            *ppIncludeSource = pEncoding.Detach();
            return S_OK;
        }

		// Clang looks for <> includes in include directories and reports
		// errors even though the include handler loads these files just fine
		std::string source = (char*)buffer->Data;
		std::regex regex(" *\\#include +\\<(.*)\\> *");
		source = std::regex_replace(source, regex, "#include \"$1\"");

		HRESULT hr = utils->CreateBlob(source.c_str(), buffer->Size, DXC_CP_ACP, pEncoding.GetAddressOf());
        if (SUCCEEDED(hr)) {
            includedFiles.put(filePath);
            *ppIncludeSource = pEncoding.Detach();
        }

		return hr;
    }
}
