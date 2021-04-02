#pragma once

#include "core/SharedPointer.h"
#include "ui/IResourceLoader.h"
#include "ui/drawable/BitmapImageDrawable.h"
#include "ui/drawable/SvgImageDrawable.h"
#include "resource/ResourceManager.h"

#include <d2d1_3.h>

namespace Ghurund::UI {
    class ResourceLoader:public IResourceLoader {
    private:
        ResourceContext& resourceContext;

    public:
        ResourceLoader(ResourceContext& resourceContext):resourceContext(resourceContext) {}

        virtual Pointer* loadResource(const FilePath& path) override {
            if (path.FileName.endsWith(L".png") || path.FileName.endsWith(L".jpg")) {
                return (Resource*)resourceContext.ResourceManager.load<BitmapImage>(resourceContext, path);
            } else if (path.FileName.endsWith(L"svg")) {
                return (Resource*)resourceContext.ResourceManager.load<SvgImage>(resourceContext, path);
            }
            return nullptr;
        }

        virtual ImageDrawable* loadDrawable(const FilePath& path) override {
            SharedPointer<Resource> resource = (Resource*)loadResource(path);
            if (!resource)
                return nullptr;
            if (path.FileName.endsWith(L".png") || path.FileName.endsWith(L".jpg")) {
                return ghnew BitmapImageDrawable((BitmapImage*)(Resource*)resource);
            } else if (path.FileName.endsWith(L"svg")) {
                return ghnew SvgImageDrawable((SvgImage*)(Resource*)resource);
            }
            return nullptr;
        }
    };
}