#include "ghuigdipch.h"
#include "SvgDocument.h"

#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/TypeBuilder.h"

#include <Shlwapi.h>
#include <wrl.h>

namespace Ghurund::UI::GDI {
    const Ghurund::Core::Type& SvgDocument::GET_TYPE() {
        using namespace Ghurund::Core;

        static auto PROPERTY_SIZE = Property<SvgDocument, FloatSize>("Size", &getSize);

        static const Ghurund::Core::Type TYPE = TypeBuilder<SvgDocument>(Ghurund::UI::NAMESPACE_NAME, "SvgDocument")
            .withProperty(PROPERTY_SIZE)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    const Array<ResourceFormat>& SvgDocument::GET_FORMATS() {
        static const Ghurund::Core::Array<Ghurund::Core::ResourceFormat> formats = { Ghurund::Core::ResourceFormat(L"svg", true, false) };
        return formats;
    }

    void SvgDocument::loadInternal(
        const Ghurund::Core::DirectoryPath& workingDir,
        Ghurund::Core::MemoryInputStream& stream,
        Ghurund::Core::LoadOption options
    ) {
        throw NotImplementedException();
    }

    void SvgDocument::saveInternal(
        const Ghurund::Core::DirectoryPath& workingDir,
        Ghurund::Core::MemoryOutputStream& stream,
        Ghurund::Core::SaveOption options
    ) const {
        throw NotSupportedException();
    }

    void SvgDocument::finalize() {}

    Ghurund::Core::FloatSize SvgDocument::getSize() {
        return { 0,0 };
    }
}