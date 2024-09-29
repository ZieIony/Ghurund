#pragma once

#include "engine/directx/Graphics.h"
#include "core/feature/Feature.h"
#include "ui/constraint/ConstraintFactory.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/loading/DrawableFactory.h"
#include "ui/directx/loading/ShapeFactory.h"
#include "ui/directx/loading/TextFormatFactory.h"

namespace Ghurund::UI::DirectX {
    using namespace Ghurund::Core;

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
        Ghurund::UI::DirectX::ShapeFactory* shapeFactory = nullptr;
        Ghurund::UI::IDrawableFactory* drawableFactory = nullptr;
        Ghurund::UI::DirectX::TextFormatFactory* textFormatFactory = nullptr;
        Ghurund::UI::ConstraintFactory* constraintFactory = nullptr;
        Ghurund::UI::IBitmapFactory* bitmapFactory = nullptr;
        IntrusivePointer<LayoutLoader> layoutLoader;

    public:
        UIFeature(ResourceManager& resourceManager):resourceManager(resourceManager) {}

        virtual void onInit() override;

        virtual void onUninit() override;

        inline LayoutLoader& getLayoutLoader() {
            return *layoutLoader.get();
        }

        __declspec(property(get = getLayoutLoader)) LayoutLoader& LayoutLoader;
    };
}