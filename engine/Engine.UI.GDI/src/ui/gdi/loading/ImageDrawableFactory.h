#pragma once

#include "core/io/FilePath.h"
#include "ui/gdi/drawable/BitmapDrawable.h"
#include "ui/gdi/drawable/SvgDrawable.h"
#include "ui/gdi/image/Bitmap.h"
#include "ui/gdi/image/SvgDocument.h"
#include "ui/drawable/ImageDrawable.h"
#include "ui/loading/ImageDrawableFactory.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI::GDI {
    class DrawableFactory:public Ghurund::UI::DrawableFactory {
    private:
        ResourceManager& resourceManager;

    public:
        DrawableFactory(ResourceManager& resourceManager):resourceManager(resourceManager) {}

        virtual ImageDrawable* makeDrawable(const FilePath& path) override {
            auto formatSupported = [&path](const ResourceFormat& format) {
                return format.Extension == path.Extension && format.CanLoad;
            };
            try {
                if (std::ranges::count_if(Bitmap::FORMATS, formatSupported) == 1) {
                    SharedPointer<Image> bitmap = resourceManager.load<Image>(path);
                    return ghnew BitmapDrawable(dynamic_cast<Bitmap*>(&bitmap));
                } else if (std::ranges::count_if(SvgDocument::FORMATS, formatSupported) == 1) {
                    SharedPointer<Image> svg = resourceManager.load<Image>(path);
                    return ghnew SvgDrawable(dynamic_cast<SvgDocument*>(&svg));
                } else {
                    Logger::log(LogType::ERR0R, _T("File format of '{}' is not supported.\n"), path);
                }
            } catch (...) {
                Logger::log(LogType::ERR0R, _T("Failed to load '{}'.\n"), path);
            }
            return nullptr;
        }
    };
}