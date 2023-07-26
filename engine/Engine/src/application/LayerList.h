#pragma once

#include "Status.h"
#include "core/collection/List.h"
#include "core/input/EventConsumer.h"
#include "core/directx/buffer/RenderTarget.h"
#include "core/math/Size.h"

#include "application/Layer.h"

namespace Ghurund {
    using namespace Ghurund::Core;

    class LayerList {
    private:
        List<SharedPointer<Layer>> layers;
        IntSize size = {};
        SharedPointer<Layer> focusedLayer, prevFocusedLayer;

    public:
        ~LayerList() {
            clear();
        }

        inline void add(Layer* layer) {
            layer->addReference();
            layer->Size = size;
            layers.add(SharedPointer(layer));
        }

        inline void remove(Layer* layer) {
            if (focusedLayer.get() == layer) {
                focusedLayer->Focused = false;
                focusedLayer.set(nullptr);
            }
            size_t index = layers.find([&](const SharedPointer<Layer>& item) { return item.get() == layer; });
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
            for (SharedPointer<Layer>& layer : layers)
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
            for (SharedPointer<Layer>& layer : layers) {
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
            for (SharedPointer<Layer>& layer : layers)
                consumed |= layer->dispatchMouseMotionEvent(args);
            return consumed;
        }

        inline bool dispatchMouseWheelEvent(const MouseWheelEventArgs& args) {
            bool consumed = false;
            // TODO: inverse layers for events
            for (SharedPointer<Layer>& layer : layers)
                consumed |= layer->dispatchMouseWheelEvent(args);
            return consumed;
        }

        inline void update(const uint64_t time) {
            for (SharedPointer<Layer>& layer : layers)
                layer->update(time);
        }

        inline Status draw(Ghurund::Core::DirectX::RenderTarget& renderTarget) {
            for (SharedPointer<Layer>& layer : layers) {
                Status result = layer->draw(renderTarget);
                if (result != Status::OK)
                    return result;
            }
            return Status::OK;
        }
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<LayerList>();
}