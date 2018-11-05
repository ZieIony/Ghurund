#pragma once

#include "Ghurund.h"
#include "Settings.h"
#include "WindowProc.h"
#include "d3dx12.h"
#include "game/ParameterProvider.h"
#include "core/NamedObject.h"
#include "collection/Array.h"

namespace Ghurund {
    class Window: public ParameterProvider, public NamedObject {
    private:
        static const tchar *WINDOW_CLASS_NAME;

        String title;
        WNDCLASSEX windowClass;
        HWND handle;
        HINSTANCE hInst;
        bool visible;
        D3D12_VIEWPORT viewport;
        D3D12_RECT scissorRect;
        unsigned int width, height;

        Array<Parameter*> parameters;
        Parameter *parameterWidth = nullptr, *parameterHeight;

    public:

        Window():parameters(Array<Parameter*>(2)) {
            Name = _T("window");
        }

        virtual void initParameters(ParameterManager &parameterManager) override {
            if(parameterWidth!=nullptr)
                return;

            parameters[0] = parameterWidth = parameterManager.add(Parameter::WIDTH, ParameterType::FLOAT);
            parameters[1] = parameterHeight = parameterManager.add(Parameter::HEIGHT, ParameterType::FLOAT);
        }

        virtual void updateParameters() override {
            parameterWidth->setValue(&width);
            parameterHeight->setValue(&height);
        }

        virtual Array<Parameter*> &getParameters() {
            return parameters;
        }

        void init(HWND handle);
        void init(Settings &settings, WindowProc &windowProc);

        void uninit();

        inline void setTitle(const String &title) {
            this->title = title;
            SetWindowText(handle, title);
        }

        inline const String &getTitle()const {
            return title;
        }

        __declspec(property(put = setTitle, get = getTitle)) String &Title;

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

        D3D12_VIEWPORT &getViewport() {
            return viewport;
        }

        D3D12_RECT &getScissorRect() {
            return scissorRect;
        }

        inline unsigned int getWidth() {
            return width;
        }

        __declspec(property(get = getWidth)) unsigned int Width;

        inline unsigned int getHeight() {
            return height;
        }

        __declspec(property(get = getHeight)) unsigned int Height;

        void updateSize();

        void setSize(unsigned int width, unsigned int height);
    };
}