#pragma once

#include "Layer.h"

#include "core/collection/List.h"
#include "core/input/EventConsumer.h"
#include "core/math/Size.h"
#include "core/object/IntrusivePointer.h"
#include "engine/graphics/RenderingContext.h"

namespace Ghurund::Engine {
    class LayerList {
    private:
        List<IntrusivePointer<Layer>> layers;
        IntSize size = {};
        IntrusivePointer<Layer> focusedLayer, prevFocusedLayer;

    public:
        ~LayerList() {
            clear();
        }

        inline void add(Layer* layer) {
            layer->addReference();
            layer->Size = size;
            layers.add(IntrusivePointer(layer));
        }

        void remove(Layer* layer);

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
            for (IntrusivePointer<Layer>& layer : layers)
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

        bool dispatchMouseButtonEvent(const MouseButtonEventArgs& args);

        inline bool dispatchMouseMotionEvent(const MouseMotionEventArgs& args) {
            bool consumed = false;
            // TODO: inverse layers for events
            for (auto& layer : layers)
                consumed |= layer->dispatchMouseMotionEvent(args);
            return consumed;
        }

        inline bool dispatchMouseWheelEvent(const MouseWheelEventArgs& args) {
            bool consumed = false;
            // TODO: inverse layers for events
            for (auto& layer : layers)
                consumed |= layer->dispatchMouseWheelEvent(args);
            return consumed;
        }

        inline void update(uint64_t time) {
            for (auto& layer : layers)
                layer->update(time);
        }

        inline void draw(RenderingContext& renderingContext, ParameterManager& parameterManager) {
            for (auto& layer : layers)
                layer->draw(renderingContext, parameterManager);
        }
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::Engine::LayerList>();
}