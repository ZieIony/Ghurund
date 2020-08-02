#pragma once

#include "core/string/String.h"
#include "application/log/Logger.h"
#include "core/io/File.h"

#pragma warning(push, 0)
#include <d3dcompiler.h>
#pragma warning(pop)

namespace Ghurund {
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

        virtual HRESULT __stdcall Open(THIS_ D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes) override {
            UnicodeString fullPath;

            switch(IncludeType) {
                case D3D_INCLUDE_LOCAL: // #include "FILE"
                    if(!shaderDir)
                        return E_FAIL;
                    fullPath = shaderDir;
                    fullPath.add(pFileName);
                    break;
                case D3D_INCLUDE_SYSTEM: // #include <FILE>
                    if(!systemDir)
                        return E_FAIL;
                    fullPath = systemDir;
                    fullPath.add(pFileName);
                    break;
                default:
                    assert(0);
            }

            void *data = nullptr;
            size_t size;

            if(readFile(fullPath, data, size)!=Status::OK) {
                Logger::log(LogType::ERR0R, _T("failed to load include: %s\n"), fullPath); // TODO: test this %s
                return E_FAIL;
            }

            *ppData = data;
            *pBytes = (UINT)size;

            return S_OK;
        }

        virtual HRESULT __stdcall Close(THIS_ LPCVOID pData) override {
            char* buf = (char*)pData;
            delete[] buf;
            return S_OK;
        }
    };
}