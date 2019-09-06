#pragma once

#include "core/string/String.h"

namespace Ghurund {
    class Entity;

    typedef void (__stdcall *listener_t)();

    class ObservableObject {
    private:
        listener_t onObjectChanged = nullptr;

    protected:
        void notifyObjectChanged() {
            if(onObjectChanged!=nullptr)
                onObjectChanged();
        }

    public:
        virtual ~ObservableObject() = default;

        void setOnChangedListener(listener_t listener) {
            onObjectChanged = listener;
        }

        listener_t getOnChangedListener() {
            return onObjectChanged;
        }

        __declspec(property(put = setOnChangedListener)) listener_t OnChangedListener;
    };
}