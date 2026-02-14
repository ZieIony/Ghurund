#pragma once

#include "engine/graphics/RenderGroup.h"

#include <cstdint>

namespace Ghurund::Engine::_2D {
	class Component2D:public RefCountedObject {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Component2D::GET_TYPE();
#pragma endregion

	protected:
		float drawOrder = 0;
		Ghurund::Core::AString* name = nullptr;
		Component2D* parent = nullptr;

	public:
		virtual ~Component2D() = 0 {
			delete name;
		}

		inline const Ghurund::Core::AString* getName() const {
			return name;
		}

		inline void setName(const AString* name) {
			if (this->name)
				delete this->name;
			if (name)
				this->name = ghnew AString(*name);
		}

		inline void setName(const AString& name) {
			if (this->name)
				delete this->name;
			this->name = ghnew AString(name);
		}

		__declspec(property(get = getName, put = setName)) const Ghurund::Core::AString* Name;

		inline Component2D* getParent() const {
			return parent;
		}

		inline void setParent(Component2D* parent) {
			this->parent = parent;
		}

		__declspec(property(get = getParent, put = setParent)) Component2D* Parent;

		virtual void update(const XMFLOAT4X4& parentTransformation, uint64_t time) {}

		virtual void draw(RenderGroup& group) {}

#ifdef _DEBUG
		virtual String printTree() const;
#endif
	};
}
