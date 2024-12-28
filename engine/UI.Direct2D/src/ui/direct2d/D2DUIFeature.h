#pragma once

#include "engine/directx/Graphics.h"
#include "ui/UIFeature.h"
#include "ui/constraint/ConstraintFactory.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/loading/DrawableFactory.h"
#include "ui/direct2d/Graphics2D.h"
#include "ui/direct2d/loading/ShapeFactory.h"
#include "ui/direct2d/loading/TextFormatFactory.h"

namespace Ghurund::UI::Direct2D {
    using namespace Ghurund::Core;

    class D2DUIFeature:public UIFeature {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = D2DUIFeature::GET_TYPE();
#pragma endregion

    private:
        ResourceManager& resourceManager;
        Ghurund::UI::Direct2D::Graphics2D& graphics2d;
        Ghurund::UI::Direct2D::ShapeFactory* shapeFactory = nullptr;
        Ghurund::UI::IDrawableFactory* drawableFactory = nullptr;
        Ghurund::UI::Direct2D::TextFormatFactory* textFormatFactory = nullptr;
        Ghurund::UI::ConstraintFactory* constraintFactory = nullptr;
        Ghurund::UI::IBitmapFactory* bitmapFactory = nullptr;
        IntrusivePointer<Ghurund::UI::LayoutLoader> layoutLoader;

    public:
        D2DUIFeature(Ghurund::UI::Direct2D::Graphics2D& graphics2d, ResourceManager& resourceManager):graphics2d(graphics2d), resourceManager(resourceManager) {}

        virtual void onInit() override;

        virtual void onUninit() override;

        virtual Ghurund::UI::ShapeFactory& getShapeFactory() override {
            return *shapeFactory;
        }

        virtual Ghurund::UI::IDrawableFactory& getDrawableFactory() override {
            return *drawableFactory;
        }

        virtual Ghurund::UI::TextFormatFactory& getTextFormatFactory() override {
            return *textFormatFactory;
        }

        virtual Ghurund::UI::ConstraintFactory& getConstraintFactory() override {
            return *constraintFactory;
        }

        virtual IBitmapFactory& getBitmapFactory() override {
            return *bitmapFactory;
        }

        virtual Ghurund::UI::LayoutLoader& getLayoutLoader() {
            return *layoutLoader.get();
        }
    };
}