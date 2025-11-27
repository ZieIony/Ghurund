#include "ghepch.h"
#include "LayerList.h"

namespace Ghurund::Engine {
    void LayerList::remove(Layer* layer) {
        if (focusedLayer.get() == layer) {
            focusedLayer->Focused = false;
            focusedLayer.set(nullptr);
        }
        size_t index = layers.find([&](const IntrusivePointer<Layer>& item) { return item.get() == layer; });
        if (index != layers.Size)
            layers.removeAt(index);
    }

    bool LayerList::dispatchMouseButtonEvent(const MouseButtonEventArgs& args) {
        bool consumed = false;
        // TODO: inverse layers for events
        for (IntrusivePointer<Layer>& layer : layers) {
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
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::Engine::LayerList>() {
        static Type TYPE = TypeBuilder<Ghurund::Engine::LayerList>();
        return TYPE;
    }
}