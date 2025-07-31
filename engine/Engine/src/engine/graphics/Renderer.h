#pragma once

#include "core/object/Object.h"
#include "engine/graphics/RenderingStatistics.h"

namespace Ghurund::Engine {
	class Renderer: public Ghurund::Core::Object {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Renderer::GET_TYPE();
#pragma endregion
    private:
        RenderingStatistics stats;

    public:
        RenderingStatistics& getStatistics() {
            return stats;
        }

        __declspec(property(get = getStatistics)) RenderingStatistics& Statistics;
	};
}