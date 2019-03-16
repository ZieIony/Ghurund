#pragma once

#include "collection/String.h"
#include "core/NamedObject.h"
#include "game/entity/TransformedObject.h"
#include "game/parameter/ParameterProvider.h"
#include "game/parameter/ParameterManager.h"
#include "editor/ObservableObject.h"
#include "resource/Resource.h"
#include "script/Script.h"

#include <atomic>
#include <DirectXCollision.h>

namespace Ghurund {

    class RenderStep;

    typedef unsigned long id_t;

    class Entity: public Resource, public NamedObject, public ParameterProvider, public virtual ObservableObject {
    private:
        bool selectable;
        id_t id = 0;
        static PointerList<Entity*> entities;
        static atomic<id_t> currentId;
        Script* script;
        Entity* parent;

        friend class EntityList;

    public:
        Entity() {
            id = currentId++;
        }

        id_t getId() const {
            return id;
        }

        __declspec(property(get = getId)) id_t Id;

        virtual void flatten(RenderStep& step, XMFLOAT4X4& transformation) = 0;

        virtual bool intersects(XMFLOAT3& pos, XMFLOAT3& dir, float& dist) {
            return false;
        }

        void setSelectable(bool selectable) {
            this->selectable = selectable;
        }

        bool isSelectable() const {
            return selectable;
        }

        __declspec(property(get = isSelectable, put = setSelectable)) bool Selectable;

        static Entity* find(id_t id) {
            for (auto e : entities)
                if (e->Id == id)
                    return e;
            return nullptr;
        }

        static id_t getCurrentId() {
            return currentId;
        }

        inline Script* getScript() {
            return script;
        }

        inline void setScript(Script * script) {
            this->script = script;
        }

        __declspec(property(get = getScript, put = setScript)) Script * Script;

        inline Entity * getParent() const {
            return parent;
        }

        __declspec(property(get = getParent)) Entity * Parent;
    };
}