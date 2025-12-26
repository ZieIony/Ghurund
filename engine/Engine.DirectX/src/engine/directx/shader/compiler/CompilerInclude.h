#pragma once

#include "core/collection/List.h"
#include "core/io/DirectoryPath.h"
#include "core/resource/ResourceManager.h"
#include "core/string/String.h"

#pragma warning(push, 0)
#include <d3dcommon.h>
#pragma warning(pop)

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class CompilerInclude:public ID3DInclude {
        ResourceManager& resourceManager;
        DirectoryPath shaderDir;
        List<DirectoryPath> systemDirs;

    public:
        CompilerInclude(
            ResourceManager& resourceManager,
            const DirectoryPath& shaderDir,
            List<DirectoryPath> systemDirs
        ):resourceManager(resourceManager), shaderDir(shaderDir), systemDirs(systemDirs) {
        }

        virtual HRESULT __stdcall Open(THIS_ D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes) override;

        virtual HRESULT __stdcall Close(THIS_ LPCVOID pData) override {
            char* buf = (char*)pData;
            delete[] buf;
            return S_OK;
        }
    };
}