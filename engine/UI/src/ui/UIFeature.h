#pragma once

#include "core/feature/Feature.h"
#include "ui/constraint/ConstraintFactory.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/loading/IDrawableFactory.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class UIFeature:public Feature {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<UIFeature>()
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        inline static const Ghurund::Core::Type& TYPE = UIFeature::GET_TYPE();
#pragma endregion

    public:
        virtual Ghurund::UI::IDrawableFactory* getDrawableFactory() = 0;

        __declspec(property(get = getDrawableFactory)) Ghurund::UI::IDrawableFactory* DrawableFactory;

        virtual Ghurund::UI::TextFormatFactory* getTextFormatFactory() = 0;

        __declspec(property(get = getTextFormatFactory)) Ghurund::UI::TextFormatFactory* TextFormatFactory;

        virtual Ghurund::UI::ConstraintFactory* getConstraintFactory() = 0;

        __declspec(property(get = getConstraintFactory)) Ghurund::UI::ConstraintFactory* ConstraintFactory;

        virtual LayoutLoader* getLayoutLoader() = 0;

        __declspec(property(get = getLayoutLoader)) LayoutLoader* LayoutLoader;
    };
}