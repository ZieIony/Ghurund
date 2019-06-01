#pragma once

#include "Ghurund.h"

#include "application/Settings.h"
#include "application/WindowProc.h"
#include "collection/Array.h"
#include "core/NamedObject.h"
#include "core/Object.h"
#include "game/parameter/ParameterProvider.h"
#include "game/parameter/ValueParameter.h"

#include "d3dx12.h"

namespace Ghurund {
    class Window: public ParameterProvider, public NamedObject, public Object {
    private:
        static const tchar* WINDOW_CLASS_NAME;

        String title;
        WNDCLASSEX windowClass;
        HWND handle;
        HINSTANCE hInst;
        bool visible;
        D3D12_VIEWPORT viewport;
        D3D12_RECT scissorRect;
        XMINT2 size;

        PointerArray<Parameter*> parameters;
        ValueParameter* parameterViewportSize = nullptr;

    public:

        Window():parameters(PointerArray<Parameter*>(1)) {
            Name = _T("window");
        }

        ~Window() {
            uninit();
        }

        virtual void initParameters(ParameterManager& parameterManager) override {
            if (parameterViewportSize != nullptr)
                return;

            parameters[0] = parameterViewportSize = (ValueParameter*)parameterManager.Parameters[(size_t)ParameterId::VIEWPORT_SIZE.Value];
        }

        virtual void updateParameters() override {
            parameterViewportSize->setValue(&XMFLOAT2((float)size.x, (float)size.y));
        }

        virtual const PointerArray<Parameter*>& getParameters() const override {
            return parameters;
        }

        void init(HWND handle);
        void init(Settings& settings, WindowProc& windowProc);

        void uninit();

        inline void setTitle(const String& title) {
            this->title = title;
            SetWindowText(handle, title);
        }

        inline const String& getTitle()const {
            return title;
        }

        __declspec(property(put = setTitle, get = getTitle)) String& Title;

        inline HWND getHandle() {
            return handle;
        }

        __declspec(property(get = getHandle)) HWND Handle;

        inline void setVisible(bool visible) {
            this->visible = visible;
            ShowWindow(handle, visible ? SW_SHOW : SW_HIDE);
        }

        inline bool isVisible() {
            return visible;
        }

        __declspec(property(put = setVisible, get = isVisible)) bool Visible;

        D3D12_VIEWPORT& getViewport() {
            return viewport;
        }

        D3D12_RECT& getScissorRect() {
            return scissorRect;
        }

        inline const XMINT2& getSize() const {
            return size;
        }

        inline void setSize(const XMINT2& size) {
            this->size = size;
            SetWindowPos(handle, HWND_TOPMOST, 0, 0, size.x, size.y, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER);
            updateSize();
        }

        inline void setSize(unsigned int w, unsigned int h) {
            size = XMINT2(w, h);
            SetWindowPos(handle, HWND_TOPMOST, 0, 0, size.x, size.y, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER);
            updateSize();
        }

        __declspec(property(get = getSize, put = setSize)) XMINT2& Size;

        inline unsigned int getWidth() const {
            return size.x;
        }

        inline void setWidth(unsigned int val) {
            size.x = val;
        }

        __declspec(property(get = getWidth, put = setWidth)) unsigned int Width;

        inline unsigned int getHeight() const {
            return size.y;
        }

        inline void setHeight(unsigned int val) {
            size.y = val;
        }

        __declspec(property(get = getHeight, put = setHeight)) unsigned int Height;

        void updateSize();

        const static Ghurund::Type& TYPE;

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}