#pragma once

#include "core/Id.h"
#include "core/NamedObject.h"
#include "core/string/String.h"
#include "game/TransformSystem.h"
#include "game/parameter/ParameterProvider.h"
#include "game/parameter/ParameterManager.h"
#include "ecs/Component.h"
#include "editor/ObservableObject.h"
#include "core/resource/Resource.h"
#include "script/Script.h"

#include <DirectXCollision.h>

namespace Ghurund {

    class Entity: public Resource, public NamedObject, public virtual ObservableObject, public IdObject<Entity> {
	private:
		Entity* parent = nullptr;

		PointerList<Component*> components;

        friend class EntityList;

    protected:
        virtual Status loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options);
        virtual Status saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const;

        static const Ghurund::Type& GET_TYPE();

    public:
		inline PointerList<Component*>& getComponents() {
			return components;
		}

		__declspec(property(get = getComponents)) PointerList<Component*>& Components;

        inline Entity* getParent() const {
            return parent;
        }

        __declspec(property(get = getParent)) Entity* Parent;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

		virtual const Ghurund::Type& getType() const override {
			return TYPE;
		}
    };

}