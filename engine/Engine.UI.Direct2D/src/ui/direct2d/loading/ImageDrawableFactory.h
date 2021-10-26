#pragma once

#include "core/io/FilePath.h"
#include "ui/direct2d/drawable/BitmapDrawable.h"
#include "ui/direct2d/drawable/SvgDrawable.h"
#include "ui/direct2d/image/Bitmap.h"
#include "ui/direct2d/image/SvgDocument.h"
#include "ui/drawable/ImageDrawable.h"
#include "ui/loading/ImageDrawableFactory.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI::Direct2D {
    class ImageDrawableFactory:public Ghurund::UI::ImageDrawableFactory {
    private:
        ResourceManager& resourceManager;

    public:
        ImageDrawableFactory(ResourceManager& resourceManager):resourceManager(resourceManager) {}

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