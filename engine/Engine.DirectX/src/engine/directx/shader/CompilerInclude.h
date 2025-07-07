#pragma once

#include "core/string/String.h"

#pragma warning(push, 0)
#include <d3dcommon.h>
#pragma warning(pop)

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class CompilerInclude:public ID3DInclude {
        DirectoryPath shaderDir, systemDir;

    public:
        CompilerInclude(const DirectoryPath& shaderDir, const DirectoryPath& systemDir):shaderDir(shaderDir), systemDir(systemDir) {
        }

        virtual HRESULT __stdcall Open(THIS_ D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes) override;

        virtual HRESULT __stdcall Close(THIS_ LPCVOID pData) override {
            char* buf = (char*)pData;
            delete[] buf;
            return S_OK;
        }
    };
}