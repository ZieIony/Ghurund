#include "ghpch.h"
#include "DragDropManager.h"

#include "SystemWindow.h"

#include <oleidl.h>
#include <shellapi.h>

namespace Ghurund {
    Array<FilePath*>* DragDropManager::getFiles(IDataObject* pDataObj) {
        FORMATETC fmte = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
        STGMEDIUM stgm;

        if (FAILED(pDataObj->GetData(&fmte, &stgm)))
            return nullptr;

        HDROP hdrop = (HDROP)stgm.hGlobal;
        UINT file_count = DragQueryFile(hdrop, 0xFFFFFFFF, NULL, 0);
        auto paths = ghnew Array<FilePath*>(file_count);

        for (UINT i = 0; i < file_count; i++) {
            wchar_t szFile[MAX_PATH];
            UINT cch = DragQueryFileW(hdrop, i, szFile, MAX_PATH);
            if (cch > 0 && cch < MAX_PATH)
                paths->set(i, ghnew FilePath(szFile));
        }

        ReleaseStgMedium(&stgm);

        return paths;
    }

    HRESULT DragDropManager::DragEnter(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) {
        Array<FilePath*>* files = getFiles(pDataObj);

        window.OnDragEntered(files);

        files->deleteItems();
        delete files;

        return S_OK;
    }
    
    HRESULT DragDropManager::DragLeave() {
        window.OnDragLeft();
        return S_OK;
    }
    
    HRESULT DragDropManager::DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) {
        window.OnDraggedOver();
        return S_OK;
    }
    
    HRESULT DragDropManager::Drop(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect) {
        Array<FilePath*>* files = getFiles(pDataObj);

        window.OnDropped(files);

        files->deleteItems();
        delete files;

        return S_OK;
    }
}
