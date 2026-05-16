#pragma once

#include "core/object/RefCountedObject.h"
#include "core/Timer.h"
#include "engine/game/tag/TagCollection.h"
#include "engine/application/UpdateGroup.h"
#include "engine/graphics/rendering/RenderGroup.h"

namespace Ghurund::Engine {
	class GameObject:public RefCountedObject {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = GameObject::GET_TYPE();
#pragma endregion

    protected:
        virtual bool getUsesFixedUpdateInternal() const {
            return true;
        }

        virtual bool getUsesUpdateInternal() const {
            return true;
        }

        virtual bool getUsesDrawInternal() const {
            return true;
        }

    public:
        bool isEnabled = true;
        WString name;
        TagCollection tags;
        UpdateGroup updateGroup;
        DrawGroup drawGroup;

        inline bool getUsesFixedUpdate() const {
            return getUsesFixedUpdateInternal();
        }

        __declspec(property(get = getUsesFixedUpdate)) bool UsesFixedUpdate;

        virtual void fixedUpdate(const Timer& timer) {}

        inline bool getUsesUpdate() const {
            return getUsesUpdateInternal();
        }

        __declspec(property(get = getUsesUpdate)) bool UsesUpdate;

        virtual void update(const Timer& timer) {}

        inline bool getUsesDraw() const {
            return getUsesDrawInternal();
        }

        __declspec(property(get = getUsesDraw)) bool UsesDraw;

        virtual void draw(RenderGroup& group) {}
	};
}
