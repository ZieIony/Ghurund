#pragma once

#include "d3dcompiler.h"
#include "collection/String.h"
#include "core/Logger.h"
#include "resource/File.h"

namespace Ghurund {
    class CompilerInclude:public ID3DInclude {
        tchar *shaderDir, *systemDir;

    public:
        CompilerInclude(const tchar *shaderDir, const tchar *systemDir) {
            this->shaderDir = copyStr(shaderDir);
            this->systemDir = copyStr(systemDir);
        }

        ~CompilerInclude() {
            delete[] shaderDir;
            delete[] systemDir;
        }

        virtual HRESULT __stdcall Open(THIS_ D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes) override {
            String fullPath;

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
                Logger::log(_T("failed to load include: %s\n"), fullPath); // TODO: test this %s
                return E_FAIL;
            }

            *ppData = data;
            *pBytes = size;

            return S_OK;
        }

        virtual HRESULT __stdcall Close(THIS_ LPCVOID pData) override {
            char* buf = (char*)pData;
            delete[] buf;
            return S_OK;
        }
    };
}