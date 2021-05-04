#pragma once

#include "BitmapImage.h"
#include "resource/Loader.h"

namespace Ghurund {
    class BitmapImageLoader:public Loader {
    private:
        Ghurund::Graphics2D& graphics2d;

    public:
        BitmapImageLoader(Ghurund::Graphics2D& graphics2d):graphics2d(graphics2d) {}

        virtual Status load(ResourceManager& manager, MemoryInputStream& stream, Resource& resource, LoadOption options) const override {
        }

        virtual Status save(ResourceManager& manager, MemoryOutputStream& stream, Resource& resource, SaveOption options) const override {

        }
    };
}