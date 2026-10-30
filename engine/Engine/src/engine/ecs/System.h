#pragma once

#include "core/object/Initializable.h"
#include <engine/application/DrawGroup.h>
#include <engine/application/UpdateGroup.h>
#include <engine/graphics/rendering/RenderingContext.h>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class System:public RefCountedObject, public WStringNamedObject, public Initializable {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = System::GET_TYPE();
#pragma endregion

    protected:
        virtual bool getUsesFixedUpdate_internal() const {
            return true;
        }

        virtual bool getUsesUpdate_internal() const {
            return true;
        }

        virtual bool getUsesDraw_internal() const {
            return true;
        }

        virtual const Array<std::reference_wrapper<const Ghurund::Core::Type>>& getDependencies_internal() const {
            static Array<std::reference_wrapper<const Ghurund::Core::Type>> dependencies;
            return dependencies;
        }

        virtual const Array<std::reference_wrapper<const Ghurund::Core::Type>>& getDependents_internal() const {
            static Array<std::reference_wrapper<const Ghurund::Core::Type>> dependents;
            return dependents;
        }

    public:
        bool isEnabled = true;

        UpdateGroup updateGroup;
        DrawGroup drawGroup;

        inline bool getUsesFixedUpdate() const {
            return getUsesFixedUpdate_internal();
        }

        __declspec(property(get = getUsesFixedUpdate)) bool UsesFixedUpdate;

        virtual void fixedUpdate(const Timer& timer) {}

        inline bool getUsesUpdate() const {
            return getUsesUpdate_internal();
        }

        __declspec(property(get = getUsesUpdate)) bool UsesUpdate;

        virtual void update(const Timer& timer) {}

        inline bool getUsesDraw() const {
            return getUsesDraw_internal();
        }

        __declspec(property(get = getUsesDraw)) bool UsesDraw;

        virtual void queueDraw(RenderingContext& renderingContext) {}

		/**
		* System types that need to execute before this system.
		**/
        inline const Array<std::reference_wrapper<const Ghurund::Core::Type>>& getDependencies() const {
            return getDependencies_internal();
        }

        __declspec(property(get = getDependencies)) const Array<std::reference_wrapper<const Ghurund::Core::Type>>& Dependencies;

		/**
		* System types that need to execute after this system.
		**/
        inline const Array<std::reference_wrapper<const Ghurund::Core::Type>>& getDependents() const {
            return getDependents_internal();
        }

        __declspec(property(get = getDependents)) const Array<std::reference_wrapper<const Ghurund::Core::Type>>& Dependents;
    };
}
