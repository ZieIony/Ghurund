#include "DragDropManager.h"
#include "SystemWindow.h"

namespace Ghurund {
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
