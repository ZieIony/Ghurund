#include "ghuidxpch.h"
#include "ImageDrawableFactory.h"

#include "core/logging/Logger.h"
#include "ui/directx/drawable/BitmapDrawable.h"
#include "ui/directx/image/Bitmap.h"
#include "ui/drawable/Drawable.h"

namespace Ghurund::UI::DirectX {
	Drawable* DrawableFactory::makeDrawable(const ResourcePath& path) {
		try {
			IntrusivePointer<Bitmap> bitmap(resourceManager.load<Bitmap>(path, DirectoryPath()));
			return ghnew BitmapDrawable(bitmap.get());
		} catch (...) {
			auto text = std::format(_T("Failed to load '{}'.\n"), path);
			Logger::log(LogType::ERR0R, text.c_str());
		}
		return nullptr;
	}
}