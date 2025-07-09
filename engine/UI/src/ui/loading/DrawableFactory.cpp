#include "ghuipch.h"
#include "DrawableFactory.h"

#include "core/logging/Logger.h"
#include "ui/drawable/BitmapDrawable.h"
#include "ui/image/Bitmap.h"
#include "ui/image/VectorImage.h"
#include "ui/drawable/Drawable.h"

namespace Ghurund::UI {
    Drawable* DrawableFactory::makeDrawable(const ResourcePath& path) {
        try {
            IntrusivePointer<Bitmap> bitmap(resourceManager->load<Bitmap>(path, DirectoryPath()));
            return ghnew BitmapDrawable(bitmap.get());
        } catch (...) {
            /*try {
                IntrusivePointer<SvgDocument> svg(resourceManager.load<SvgDocument>(path, DirectoryPath()));
                return ghnew SvgDrawable(svg.get());
            } catch (...) {*/
                auto text = std::format(_T("Failed to load '{}'.\n"), path);
                Logger::log(LogType::ERR0R, text.c_str());
            //}
        }
        return nullptr;
    }
}