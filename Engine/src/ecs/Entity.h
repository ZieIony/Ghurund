#pragma once

#include "core/string/String.h"
#include "core/Id.h"
#include "core/NamedObject.h"
#include "game/parameter/ParameterProvider.h"
#include "game/parameter/ParameterManager.h"
#include "editor/ObservableObject.h"
#include "resource/Resource.h"
#include "script/Script.h"
#include "ecs/Component.h"
#include "game/TransformSystem.h"

#include <DirectXCollision.h>

namespace Ghurund {

    class Entity: public Resource, public NamedObject<String>, public virtual ObservableObject, public IdObject<Entity> {
	private:
		inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<Entity>();
		
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
            stream.writeUnicode((UnicodeString)Name);
			//uint32_t componentCount = stream.readUInt();
			//for(uint32_t i=0;i<componentCount;i++)
			// TODO: save components
			return Status::OK;
        }

    public:
		inline PointerList<Component*>& getComponents() {
			return components;
		}

		__declspec(property(get = getComponents)) PointerList<Component*>& Components;

        inline Entity* getParent() const {
            return parent;
        }

        __declspec(property(get = getParent)) Entity* Parent;

		inline static const Ghurund::Type& TYPE = Ghurund::Type(CONSTRUCTOR, "Ghurund", "Entity");

		virtual const Ghurund::Type& getType() const override {
			return TYPE;
		}
    };

}