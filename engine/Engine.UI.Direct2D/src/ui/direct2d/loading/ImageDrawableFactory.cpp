#include "ghuidxpch.h"
#include "ImageDrawableFactory.h"

#include "core/io/FilePath.h"
#include "ui/direct2d/drawable/BitmapDrawable.h"
#include "ui/direct2d/drawable/SvgDrawable.h"
#include "ui/direct2d/image/Bitmap.h"
#include "ui/direct2d/image/SvgDocument.h"
#include "ui/drawable/Drawable.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/theme/Theme.h"

#include <ranges>

namespace Ghurund::UI::Direct2D {
    Drawable* DrawableFactory::makeDrawable(const FilePath& path) {
        auto formatSupported = [&path](const ResourceFormat& format) {
            return format.Extension == path.Extension && format.CanLoad;
        };
        try {
            if (std::ranges::count_if(Bitmap::FORMATS, formatSupported) == 1) {
                SharedPointer<Bitmap> bitmap(resourceManager.load<Bitmap>(path));
                return ghnew BitmapDrawable(bitmap.get());
            } else if (std::ranges::count_if(SvgDocument::FORMATS, formatSupported) == 1) {
                SharedPointer<SvgDocument> svg(resourceManager.load<SvgDocument>(path));
                return ghnew SvgDrawable(svg.get());
            } else {
                auto text = std::format(_T("File format of '{}' is not supported.\n"), path);
                Logger::log(LogType::ERR0R, text.c_str());
            }
        } catch (...) {
            auto text = std::format(_T("Failed to load '{}'.\n"), path);
            Logger::log(LogType::ERR0R, text.c_str());
        }
        return nullptr;
    }
}