#include "ResourceContext.h"
#include "graphics/CommandList.h"

#include <wincodec.h>

namespace Ghurund {
    ResourceContext::~ResourceContext() {
        if (wicFactory)
            wicFactory->Release();
        if (commandList)
            commandList->release();
    }

    Status ResourceContext::init() {
        commandList = ghnew Ghurund::CommandList();
        Status result = commandList->init(graphics, graphics.DirectQueue);
        if (result != Status::OK)
            return result;
        commandList->Name = L"resource context's CommandList";
        HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&wicFactory));
        if (FAILED(hr))
            return Status::CALL_FAIL;
        return Status::OK;
    }
}
