#pragma once

#include "core/application/Application.h"
#include "core/application/Feature.h"
#include "ui/constraint/ConstraintFactory.h"
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
        virtual const Ghurund::Core::Type& getTypeImpl() const override { return GET_TYPE(); }

    public:
        static const Ghurund::Core::Type& GET_TYPE();
#pragma endregion

    private:
        Application& app;
        Ghurund::UI::Direct2D::Graphics2D* graphics2d = nullptr;
        Ghurund::UI::Direct2D::ShapeFactory* shapeFactory = nullptr;
        Ghurund::UI::Direct2D::ImageDrawableFactory* imageDrawableFactory = nullptr;
        Ghurund::UI::Direct2D::TextFormatFactory* textFormatFactory = nullptr;
        Ghurund::UI::ConstraintFactory* constraintFactory = nullptr;

    public:
        UIFeature(Application& app):app(app) {}

        virtual void onInit() override;

        virtual void onUninit() override;

        inline Ghurund::UI::Direct2D::Graphics2D& getGraphics2D() {
            return *graphics2d;
        }

        __declspec(property(get = getGraphics2D)) Ghurund::UI::Direct2D::Graphics2D& Graphics2D;
    };
}