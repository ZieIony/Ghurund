#pragma once

#include "core/IUnknownImpl.h"
#include "core/collection/List.h"
#include "core/io/FilePath.h"

namespace Ghurund {
    class SystemWindow;

    class DECLSPEC_UUID("796c4f9e-698f-42d4-ae90-3a9c4cb79b99") DragDropManager: public ComBase<QiList<IDropTarget>> {
    private:
        SystemWindow& window;

        Array<FilePath*>* getFiles(IDataObject * pDataObj);

    public:
        DragDropManager(SystemWindow& window):window(window) {
            AddRef();
        }

        HRESULT DragEnter(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect);

        HRESULT DragLeave();

        HRESULT DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect);

        HRESULT Drop(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect);
    };
}