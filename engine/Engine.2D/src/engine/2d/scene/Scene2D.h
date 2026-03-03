#pragma once

#include "Entity2D.h"

#include "core/resource/Resource.h"
#include <engine/2d/IGraphics2DContext.h>

namespace Ghurund::Engine::_2D {
    class Scene2D:public Resource {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Scene2D::GET_TYPE();
#pragma endregion

    private:
        IGraphics2DContext& context;
        List<IntrusivePointer<Entity2D>> entities;

    public:
        Scene2D(IGraphics2DContext& context):context(context) {}

        inline List<IntrusivePointer<Entity2D>>& getEntities() {
            return entities;
        }

        __declspec(property(get = getEntities)) List<IntrusivePointer<Entity2D>>& Entities;

        inline void update(uint64_t time) {
            for (auto& entity : entities)
                entity->update(time);
        }

        inline void draw(RenderGroup& group) {
            for (auto& entity : entities)
                entity->draw(group);
        }
#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return Scene2D::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_SCENE = ResourceFormat(L"scene", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_SCENE };
#pragma endregion
    };
}