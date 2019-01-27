#pragma once

#include "collection/String.h"

namespace Ghurund {
    class Entity;

    class ObservableObject {
    private:
        std::function<void()> onObjectChanged = nullptr;

    protected:
        void notifyObjectChanged() {
            if(onObjectChanged!=nullptr)
                onObjectChanged();
        }

    public:
        virtual ~ObservableObject() = default;

        void setOnChangedListener(std::function<void()> listener) {
            onObjectChanged = listener;
        }

        __declspec(property(put = setOnChangedListener)) std::function<void()> OnChangedListener;
    };
}