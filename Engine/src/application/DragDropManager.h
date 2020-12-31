#pragma once

#include "core/IUnknownImpl.h"
#include "core/collection/List.h"
#include "core/io/FilePath.h"

#include <oleidl.h>
#include <shellapi.h>

namespace Ghurund {
    class SystemWindow;

    class DECLSPEC_UUID("796c4f9e-698f-42d4-ae90-3a9c4cb79b99") DragDropManager: public ComBase<QiList<IDropTarget>> {
    private:
        SystemWindow& window;

        Array<FilePath*>* getFiles(IDataObject * pDataObj) {
            FORMATETC fmte = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
            STGMEDIUM stgm;

            if (FAILED(pDataObj->GetData(&fmte, &stgm)))
                return nullptr;

            HDROP hdrop = (HDROP)stgm.hGlobal;
            UINT file_count = DragQueryFile(hdrop, 0xFFFFFFFF, NULL, 0);
            auto paths = ghnew Array<FilePath*>(file_count);

            for (UINT i = 0; i < file_count; i++) {
                TCHAR szFile[MAX_PATH];
                UINT cch = DragQueryFile(hdrop, i, szFile, MAX_PATH);
                if (cch > 0 && cch < MAX_PATH)
                    paths->set(i, ghnew FilePath(szFile));
            }

            ReleaseStgMedium(&stgm);

            return paths;
        }

    public:
        DragDropManager(SystemWindow& window):window(window) {}

        HRESULT DragEnter(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect);

        HRESULT DragLeave();

        HRESULT DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect);

        HRESULT Drop(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect);
    };
}