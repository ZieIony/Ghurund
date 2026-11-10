#pragma once

#include "core/collection/Set.h"
#include "core/resource/ResourceManager.h"

#pragma warning(push, 0)
#include <dxcapi.h>
#pragma warning(pop)

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	class CompilerIncludeDXC: public IDxcIncludeHandler {
	private:
		ULONG refValue = 0;

		Set<FilePath> includedFiles;
		ResourceManager& resourceManager;
		DirectoryPath shaderDir;
		List<DirectoryPath> systemDirs;

	public:
		CompilerIncludeDXC(
			ResourceManager& resourceManager,
			const DirectoryPath& shaderDir,
			List<DirectoryPath> systemDirs
		):resourceManager(resourceManager), shaderDir(shaderDir), systemDirs(systemDirs) {
		}

		virtual HRESULT __stdcall LoadSource(_In_ LPCWSTR pFilename, _COM_Outptr_result_maybenull_ IDxcBlob** ppIncludeSource) override;

		IFACEMETHOD(QueryInterface)(IID const& iid, OUT void** ppObject) {
			*ppObject = NULL;
			if (iid != __uuidof(IDxcIncludeHandler))
				return E_NOINTERFACE;

			*ppObject = (IDxcIncludeHandler*)this;

			AddRef();
			return S_OK;
		}

		IFACEMETHOD_(ULONG, AddRef)() {
			return InterlockedIncrement(&refValue);
		}

		IFACEMETHOD_(ULONG, Release)() {
			ULONG newCount = InterlockedDecrement(&refValue);
			if (newCount == 0)
				delete this;

			return newCount;
		}
	};
}
