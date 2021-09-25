#pragma once

#include "core/string/String.h"

#pragma warning(push, 0)
#include <d3dcompiler.h>
#pragma warning(pop)

namespace Ghurund {
    using namespace Ghurund::Core;

    class CompilerInclude:public ID3DInclude {
        wchar_t *shaderDir, *systemDir;

    public:
        CompilerInclude(const wchar_t *shaderDir, const wchar_t *systemDir) {
            this->shaderDir = copyStr(shaderDir);
            this->systemDir = copyStr(systemDir);
        }

        ~CompilerInclude() {
            delete[] shaderDir;
            delete[] systemDir;
        }

        virtual HRESULT __stdcall Open(THIS_ D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes) override;

        virtual HRESULT __stdcall Close(THIS_ LPCVOID pData) override {
            char* buf = (char*)pData;
            delete[] buf;
            return S_OK;
        }
    };
}