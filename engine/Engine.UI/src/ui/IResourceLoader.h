#pragma once

#include "core/io/FilePath.h"
#include "ui/drawable/ImageDrawable.h"

namespace Ghurund::UI {
    __interface IResourceLoader {

        Pointer* loadResource(const FilePath& path);

        ImageDrawable* loadDrawable(const FilePath& path);
    };
}