#pragma once

#include "core/directx/Graphics.h"
#include "core/application/Feature.h"
#include "ui/constraint/ConstraintFactory.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/direct2d/Graphics2D.h"
#include "ui/direct2d/loading/ShapeFactory.h"
#include "ui/direct2d/loading/ImageDrawableFactory.h"
#include "ui/direct2d/loading/TextFormatFactory.h"

namespace Ghurund {
    using namespace Ghurund::Core;
    using namespace Ghurund::UI;
    using namespace Ghurund::UI::Direct2D;

    class UIFeature:public Feature {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = UIFeature::GET_TYPE();
#pragma endregion

    private:
        ResourceManager& resourceManager;
        Ghurund::UI::Direct2D::Graphics2D& graphics2d;
        Ghurund::UI::Direct2D::ShapeFactory* shapeFactory = nullptr;
        Ghurund::UI::Direct2D::DrawableFactory* drawableFactory = nullptr;
        Ghurund::UI::Direct2D::TextFormatFactory* textFormatFactory = nullptr;
        Ghurund::UI::ConstraintFactory* constraintFactory = nullptr;
        SharedPointer<LayoutLoader> layoutLoader;

    public:
        UIFeature(Ghurund::UI::Direct2D::Graphics2D& graphics2d, ResourceManager& resourceManager):graphics2d(graphics2d), resourceManager(resourceManager) {}

        virtual void onInit() override;

        virtual void onUninit() override;

        inline LayoutLoader& getLayoutLoader() {
            return *layoutLoader.get();
        }

        __declspec(property(get = getLayoutLoader)) LayoutLoader& LayoutLoader;
    };
}