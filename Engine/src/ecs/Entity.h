#pragma once

#include "collection/String.h"
#include "core/NamedObject.h"
#include "game/parameter/ParameterProvider.h"
#include "game/parameter/ParameterManager.h"
#include "editor/ObservableObject.h"
#include "resource/Resource.h"
#include "script/Script.h"
#include "ecs/Component.h"
#include "game/TransformSystem.h"

#include <atomic>
#include <DirectXCollision.h>

namespace Ghurund {

    typedef unsigned long id_t;

    class Entity: public Resource, public NamedObject, public virtual ObservableObject {
    private:
        bool editMode = false;
        id_t id = 0;
        static PointerList<Entity*> entities;
        static atomic<id_t> currentId;
        Entity* parent = nullptr;

		PointerList<Component*> components;

        friend class EntityList;

    protected:
        virtual Status loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
            Name = stream.readUnicode();
			uint32_t componentCount = stream.readUInt();
			//for(uint32_t i=0;i<componentCount;i++)
			// TODO: read components
            return Status::OK;
        }

        virtual Status saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
            stream.writeUnicode(Name);
			//uint32_t componentCount = stream.readUInt();
			//for(uint32_t i=0;i<componentCount;i++)
			// TODO: save components
			return Status::OK;
        }

    public:
        Entity() {
            id = currentId++;
        }

        id_t getId() const {
            return id;
        }

        __declspec(property(get = getId)) id_t Id;

		inline PointerList<Component*>& getComponents() {
			return components;
		}

		__declspec(property(get = getComponents)) PointerList<Component*>& Components;

        inline void setInEditMode(bool inEditMode) {
            this->editMode = inEditMode;
        }

        inline bool isInEditMode()const {
            return editMode;
        }

        __declspec(property(get = isInEditMode, put = setInEditMode)) bool InEditMode;

        static Entity* find(id_t id) {
            for (auto e : entities)
                if (e->Id == id)
                    return e;
            return nullptr;
        }

        static id_t getCurrentId() {
            return currentId;
        }

        inline Entity* getParent() const {
            return parent;
        }

        __declspec(property(get = getParent)) Entity* Parent;

		const static Ghurund::Type& TYPE;

		virtual const Ghurund::Type& getType() const override {
			return TYPE;
		}
    };

}