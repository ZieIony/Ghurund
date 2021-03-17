#pragma once

#include "Layer.h"
#include "Status.h"
#include "core/collection/List.h"
#include "input/EventConsumer.h"

namespace Ghurund {
    class LayerList {
    private:
        List<Layer*> layers;
        IntSize size = {};
        Layer* focusedLayer = nullptr, * prevFocusedLayer = nullptr;

    public:
        ~LayerList() {
            clear();
        }

        inline void add(Layer* layer) {
            layers.add(layer);
            layer->Size = size;
        }

        inline void remove(Layer* layer) {
            if (focusedLayer == layer) {
                focusedLayer->Focused = false;
                focusedLayer = nullptr;
            }
            layers.remove(layer);
        }

        inline void clear() {
            clearFocus();
            layers.deleteItems();
            layers.clear();
        }

        inline const IntSize& getSize() const {
            return size;
        }

        inline void setSize(const IntSize& size) {
            setSize(size.width, size.height);
        }

        virtual void setSize(unsigned int w, unsigned int h) {
            size = { w, h };
            for (Layer* layer : layers)
                layer->Size = size;
        }

        __declspec(property(get = getSize, put = setSize)) const IntSize& Size;

        inline void clearFocus() {
            if (focusedLayer) {
                focusedLayer->Focused = false;
                prevFocusedLayer = focusedLayer;
                focusedLayer = nullptr;
            }
        }

        inline void restoreFocus() {
            if (focusedLayer || !prevFocusedLayer)
                return;
            focusedLayer = prevFocusedLayer;
            focusedLayer->Focused = true;
            prevFocusedLayer = nullptr;
        }

        inline bool dispatchKeyEvent(const Input::KeyEventArgs& args) {
            return focusedLayer && focusedLayer->dispatchKeyEvent(args);
        }

        inline bool dispatchMouseButtonEvent(const Input::MouseButtonEventArgs& args) {
            bool consumed = false;
            // TODO: inverse layers for events
            for (Layer* layer : layers) {
                consumed |= layer->dispatchMouseButtonEvent(args);
                if (consumed) {
                    if (!layer->Focused) {
                        if (focusedLayer)
                            focusedLayer->Focused = false;
                        layer->Focused = true;
                        focusedLayer = layer;
                    }
                    break;
                }
            }
            return consumed;
        }

        inline bool dispatchMouseMotionEvent(const Input::MouseMotionEventArgs& args) {
            bool consumed = false;
            // TODO: inverse layers for events
            for (Layer* layer : layers)
                consumed |= layer->dispatchMouseMotionEvent(args);
            return consumed;
        }

        inline bool dispatchMouseWheelEvent(const Input::MouseWheelEventArgs& args) {
            bool consumed = false;
            // TODO: inverse layers for events
            for (Layer* layer : layers)
                consumed |= layer->dispatchMouseWheelEvent(args);
            return consumed;
        }

        inline void update(const uint64_t time) {
            for (Layer* layer : layers)
                layer->update(time);
        }

        inline Status draw() {
            for (Layer* layer : layers) {
                Status result = layer->draw();
                if (result != Status::OK)
                    return result;
            }
            return Status::OK;
        }
    };
}