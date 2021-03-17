#pragma once

#include "SearchFieldLayout.h"
#include "ui/widget/ContainerWidget.h"

namespace Ghurund::Editor {
    using namespace Ghurund::UI;

    inline static const char* NAMESPACE_NAME = GH_STRINGIFY(Ghurund::Editor);

    class SearchField:public Widget<SearchFieldLayout> {
    protected:
        static const Ghurund::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = NoArgsConstructor<SearchField>();
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(SearchField))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    public:
        inline const WString& getHint() {
            return Layout->Hint->Text;
        }

        inline void setHint(const WString& hint) {
            Layout->Hint->Text = hint;
        }

        __declspec(property(get = getHint)) const WString& Hint;

        inline const WString& getQuery() {
            return Layout->QueryField->Text;
        }

        inline void setQuery(const WString& query) {
            Layout->QueryField->Text = query;
        }

        __declspec(property(get = getQuery)) const WString& Query;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}