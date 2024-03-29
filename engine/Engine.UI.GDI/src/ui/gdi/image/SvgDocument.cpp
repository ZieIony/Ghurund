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

        static auto PROPERTY_SIZE = ReadOnlyProperty<SvgDocument, FloatSize>("Size", &getSize);

        static const auto CONSTRUCTOR = Constructor<SvgDocument>();

        static const Ghurund::Core::Type TYPE = TypeBuilder<SvgDocument>(Ghurund::UI::NAMESPACE_NAME, "SvgDocument")
            .withProperty(PROPERTY_SIZE)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    const Array<ResourceFormat>& SvgDocument::GET_FORMATS() {
        static const Ghurund::Core::Array<Ghurund::Core::ResourceFormat> formats = { Ghurund::Core::ResourceFormat(L"svg", true, false) };
        return formats;
    }

    Status SvgDocument::loadInternal(
        const Ghurund::Core::DirectoryPath& workingDir,
        Ghurund::Core::MemoryInputStream& stream,
        Ghurund::Core::LoadOption options
    ) {
        return Status::NOT_IMPLEMENTED;
    }

    Status SvgDocument::saveInternal(
        const Ghurund::Core::DirectoryPath& workingDir,
        Ghurund::Core::MemoryOutputStream& stream,
        Ghurund::Core::SaveOption options
    ) const {
        return Status::NOT_SUPPORTED;
    }

    void SvgDocument::finalize() {}

    Ghurund::Core::FloatSize SvgDocument::getSize() {
        return { 0,0 };
    }
}