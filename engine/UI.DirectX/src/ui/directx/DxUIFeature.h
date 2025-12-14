#pragma once

#include "engine/directx/DxGraphics.h"
#include "engine/directx/material/DxMaterialFactory.h"
#include "ui/constraint/ConstraintFactory.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/UIFeature.h"

namespace Ghurund::UI::DirectX {
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine::DirectX;

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
        DxGraphics& graphics;
        IntrusivePointer<CommandList> commandList;
        ITextureFactory* textureFactory = nullptr;
        Ghurund::UI::ConstraintFactory* constraintFactory = nullptr;
        DxMaterialFactory materialFactory;
        IntrusivePointer<Ghurund::UI::LayoutLoader> layoutLoader;

    public:
        DxUIFeature(ResourceManager& resourceManager, DxGraphics& graphics):resourceManager(resourceManager), graphics(graphics) {}

        virtual void onInit() override;

        virtual void onUninit() override;

        virtual ITextureFactory* getTextureFactory() override {
            return textureFactory;
        }

        virtual Ghurund::UI::ConstraintFactory* getConstraintFactory() override {
            return constraintFactory;
        }

        virtual Ghurund::UI::LayoutLoader* getLayoutLoader() {
            return layoutLoader.get();
        }
    };
}