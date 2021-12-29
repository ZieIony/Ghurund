#include "ghcdxpch.h"
#include "CompilerInclude.h"

#include "core/io/File.h"
#include "core/logging/Logger.h"

namespace Ghurund::Core::DirectX {
    HRESULT __stdcall CompilerInclude::Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes) {
        WString fullPath;

        switch (IncludeType) {
        case D3D_INCLUDE_LOCAL: // #include "FILE"
        {
            if (!shaderDir)
                return E_FAIL;
            fullPath = shaderDir;
            const wchar_t* str = convertText<char, wchar_t>(pFileName);
            fullPath.add(str);
            delete[] str;
            break;
        }
        case D3D_INCLUDE_SYSTEM: // #include <FILE>
        {
            if (!systemDir)
                return E_FAIL;
            fullPath = systemDir;
            const wchar_t* str = convertText<char, wchar_t>(pFileName);
            fullPath.add(str);
            delete[] str;
            break;
        }
        default:
            return E_FAIL;
        }

        void* data = nullptr;
        size_t size;

        if (readFile(fullPath.Data, data, size) != Status::OK) {
            Logger::log(LogType::ERR0R, _T("failed to load include: {}\n"), fullPath);
            return E_FAIL;
        }

        *ppData = data;
        *pBytes = (UINT)size;

        return S_OK;
    }
}
