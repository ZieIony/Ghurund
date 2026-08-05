#pragma once

#include "Blackboard.h"

#include "core/object/RefCountedObject.h"
#include "core/object/NamedObject.h"

namespace Ghurund::Engine {
	class NodeDecorator:public RefCountedObject, public AStringNamedObject {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = NodeDecorator::GET_TYPE();
#pragma endregion

	public:
		virtual ~NodeDecorator() = 0 {}

		virtual bool shouldExecute(Blackboard* blackboard) = 0;
	};
}
