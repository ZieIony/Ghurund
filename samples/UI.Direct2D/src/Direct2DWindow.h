#pragma once

#include "core/window/SystemWindow.h"
#include "core/input/Input.h"
#include "ui/RootView.h"
#include "ui/direct2d/UIContext.h"
#include "ui/direct2d/Canvas.h"

namespace Samples {
    using namespace Ghurund::Core;
    using namespace Ghurund::UI;
    using namespace Ghurund::UI::Direct2D;

    class Direct2DWindow: public Ghurund::Core::SystemWindow {
#pragma region reflection
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        
        virtual const Ghurund::Core::Type& getTypeImpl() const override { return GET_TYPE(); }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
#pragma endregion

    private:
        RootView* rootView = nullptr;
        UIContext* uiContext = nullptr;
        Canvas* canvas = nullptr;
        ResourceManager* resourceManager = nullptr;

    protected:
        virtual bool onSizeChangingEvent(const IntSize& size) override {
            __super::onSizeChangingEvent(size);
            return true;
        }

        virtual bool onSizeChangedEvent() override {
            __super::onSizeChangedEvent();
            return true;
        }

        virtual bool onFocusedChangedEvent() override;

    public:
        Direct2DWindow(Ghurund::Core::Timer& timer);

        ~Direct2DWindow() {
            uninit();
        }

        virtual void init(WindowManager& windowManager);

        void uninit();

        virtual bool onKeyEvent(const KeyEventArgs& args) override;

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& args) override;

        virtual bool onMouseMotionEvent(const MouseMotionEventArgs& args) override;

        virtual bool onMouseWheelEvent(const MouseWheelEventArgs& args) override;

        virtual void update(const uint64_t time) override;

        virtual Status paint() override;
    };
}