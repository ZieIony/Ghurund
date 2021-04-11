#include "ghpch.h"
#include "Image.h"

#include "resource/ResourceContext.h"
#include "core/io/File.h"
#include "core/io/MemoryStream.h"

#include <Shlwapi.h>

namespace Ghurund {
    const Ghurund::Type& Image::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<Image>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Image))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}