#include "ghuipch.h"
#include "Layout.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& Layout::GET_TYPE() {

        static const auto CONSTRUCTOR = Constructor<Layout>();

        static const Ghurund::Core::Type TYPE = TypeBuilder<Layout>(Ghurund::UI::NAMESPACE_NAME, "Layout")
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    const Array<ResourceFormat>& Layout::GET_FORMATS() {
        static const Ghurund::Core::Array<Ghurund::Core::ResourceFormat> formats = {
                Ghurund::Core::ResourceFormat(L"xml", true, false)
        };
        return formats;
    }

}