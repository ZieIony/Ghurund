#pragma once

#include "Control.h"
#include "core/Object.h"

namespace Ghurund::UI {
    class BaseItemTypeAdapter {
    public:
        ~BaseItemTypeAdapter() {}

        virtual Control* makeControl()const = 0;

        virtual void bind(const void* item, Control& control) const {}
    };

    template<class T>
    class ItemTypeAdapter :public BaseItemTypeAdapter {
    public:
        virtual void bind(const T* item, Control& control) const override {}
    };

    class ItemAdapter {
    private:
        Map<type_info, BaseItemTypeAdapter*> adapters;

    public:
        virtual ~ItemAdapter() {
            for (BaseItemTypeAdapter* adapter : adapters)
                delete adapter;
        }

        virtual size_t getItemCount() = 0;

        template<class T>
        inline void registerType(const type_info& type, ItemTypeAdapter<T>* adapter) {
            adapters.set(type, adapter);
        }

        virtual Control* makeControl(size_t position) const = 0;

        virtual void bind(Control& control, size_t position) = 0;
    };
}