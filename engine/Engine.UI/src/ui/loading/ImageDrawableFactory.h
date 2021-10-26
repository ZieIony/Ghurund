#pragma once

#include "ui/drawable/ImageDrawable.h"

namespace Ghurund::UI {
    __interface ImageDrawableFactory {
        ImageDrawable* makeDrawable(const FilePath& path);
    };
}