#pragma once

#include "Layer.h"
#include "core/IntrusivePointer.h"
#include "core/collection/List.h"
#include "core/input/EventConsumer.h"
#include "core/math/Size.h"


namespace Ghurund::Core {
    template<class T>
    class LayerList {
    private:
        List<IntrusivePointer<Layer<T>>> layers;
        IntSize size = {};
        IntrusivePointer<Layer<T>> focusedLayer, prevFocusedLayer;

    public:
        ~LayerList() {
            clear();
        }

        inline void add(Layer<T>* layer) {
            layer->addReference();
            layer->Size = size;
            layers.add(IntrusivePointer(layer));
        }

        inline void remove(Layer<T>* layer) {
            if (focusedLayer.get() == layer) {
                focusedLayer->Focused = false;
                focusedLayer.set(nullptr);
            }
            size_t index = layers.find([&](const IntrusivePointer<Layer<T>>& item) { return item.get() == layer; });
            if (index != layers.Size)
                layers.removeAt(index);
        }

        inline void clear() {
            clearFocus();
            layers.clear();
        }

        inline const IntSize& getSize() const {
            return size;
        }

        inline void setSize(const IntSize& size) {
            setSize(size.Width, size.Height);
        }

        virtual void setSize(uint32_t w, uint32_t h) {
            size = { w, h };
            for (IntrusivePointer<Layer<T>>& layer : layers)
                layer->Size = size;
        }

        __declspec(property(get = getSize, put = setSize)) const IntSize& Size;

        inline void clearFocus() {
            if (focusedLayer.get()) {
                focusedLayer->Focused = false;
                prevFocusedLayer = focusedLayer;
                focusedLayer.set(nullptr);
            }
        }

        inline void restoreFocus() {
            if (focusedLayer.get() || !prevFocusedLayer.get())
                return;
            focusedLayer = prevFocusedLayer;
            focusedLayer->Focused = true;
            prevFocusedLayer.set(nullptr);
        }

        inline bool dispatchKeyEvent(const KeyEventArgs& args) {
            return focusedLayer.get() && focusedLayer->dispatchKeyEvent(args);
        }

        inline bool dispatchMouseButtonEvent(const MouseButtonEventArgs& args) {
            bool consumed = false;
            // TODO: inverse layers for events
            for (IntrusivePointer<Layer<T>>& layer : layers) {
                consumed |= layer->dispatchMouseButtonEvent(args);
                if (consumed) {
                    if (!layer->Focused) {
                        if (focusedLayer.get())
                            focusedLayer->Focused = false;
                        layer->Focused = true;
                        focusedLayer = layer;
                    }
                    break;
                }
            }
            return consumed;
        }

        inline bool dispatchMouseMotionEvent(const MouseMotionEventArgs& args) {
            bool consumed = false;
            // TODO: inverse layers for events
            for (IntrusivePointer<Layer<T>>& layer : layers)
                consumed |= layer->dispatchMouseMotionEvent(args);
            return consumed;
        }

        inline bool dispatchMouseWheelEvent(const MouseWheelEventArgs& args) {
            bool consumed = false;
            // TODO: inverse layers for events
            for (IntrusivePointer<Layer<T>>& layer : layers)
                consumed |= layer->dispatchMouseWheelEvent(args);
            return consumed;
        }

        inline void update(const uint64_t time) {
            for (IntrusivePointer<Layer<T>>& layer : layers)
                layer->update(time);
        }

        inline void draw(T& context) {
            for (auto& layer : layers)
                layer->draw(context);
        }
    };
}
