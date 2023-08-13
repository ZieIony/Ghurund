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
    Drawable* DrawableFactory::makeDrawable(const ResourcePath& path) {
        try {
            SharedPointer<Bitmap> bitmap(resourceManager.load<Bitmap>(path, DirectoryPath()));
            return ghnew BitmapDrawable(bitmap.get());
        } catch (...) {
            try {
                SharedPointer<SvgDocument> svg(resourceManager.load<SvgDocument>(path, DirectoryPath()));
                return ghnew SvgDrawable(svg.get());
            } catch (...) {
                auto text = std::format(_T("Failed to load '{}'.\n"), path);
                Logger::log(LogType::ERR0R, text.c_str());
            }
        }
        return nullptr;
    }
}