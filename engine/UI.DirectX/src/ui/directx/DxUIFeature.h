#pragma once

#include "engine/directx/DxGraphics.h"
#include "ui/UIFeature.h"
#include "ui/constraint/ConstraintFactory.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/loading/DrawableFactory.h"
#include "ui/directx/loading/TextFormatFactory.h"

namespace Ghurund::UI::DirectX {
    using namespace Ghurund::Core;

    class DxUIFeature:public UIFeature {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = DxUIFeature::GET_TYPE();
#pragma endregion

    private:
        ResourceManager& resourceManager;
        Ghurund::UI::IDrawableFactory* drawableFactory = nullptr;
        Ghurund::UI::DirectX::TextFormatFactory* textFormatFactory = nullptr;
        Ghurund::UI::ConstraintFactory* constraintFactory = nullptr;
        IntrusivePointer<Ghurund::UI::LayoutLoader> layoutLoader;

    public:
        DxUIFeature(ResourceManager& resourceManager):resourceManager(resourceManager) {}

        virtual void onInit() override;

        virtual void onUninit() override;

        virtual Ghurund::UI::IDrawableFactory* getDrawableFactory() override {
            return drawableFactory;
        }

        virtual Ghurund::UI::TextFormatFactory* getTextFormatFactory() override {
            return textFormatFactory;
        }

        virtual Ghurund::UI::ConstraintFactory* getConstraintFactory() override {
            return constraintFactory;
        }

        virtual Ghurund::UI::LayoutLoader* getLayoutLoader() {
            return layoutLoader.get();
        }
    };
}