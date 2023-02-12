#pragma once

#include "ui/control/ControlContainer.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class Widget:public ControlContainer {
    private:
        AString layoutPath;

    protected:
        static const Ghurund::Core::Type& GET_TYPE();

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        virtual void onThemeChanged() override;

        virtual void bind() {}

    public:
        virtual void load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}
