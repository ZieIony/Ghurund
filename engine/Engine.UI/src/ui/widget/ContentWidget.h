#pragma once

#include "Widget.h"
#include "core/Observable.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class ContentWidget:public Widget {
    private:
        ControlContainer* container = nullptr;

    protected:
        virtual void onChildChanged() override {
            if (Child) {
                container = (Ghurund::UI::ControlContainer*)ControlContainer::find("content");
                if (container)
                    container->Child = content.Value.get();
            } else {
                container = nullptr;
            }
        }

    public:
        Observable<SharedPointer<Control>> content;

        virtual void load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        using Control::find;

        virtual Ghurund::UI::Control* find(const Ghurund::Core::AString& name, bool deep = true) const override;

        virtual Ghurund::UI::Control* find(const Ghurund::Core::Type& type, bool deep = true) const override;

        static const Ghurund::Core::Type& GET_TYPE();

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}
