#pragma once

#include "ui/control/ControlGroup.h"
#include "ui/layout/LayoutManager.h"
#include "core/xml/XMLElement.h"

namespace Ghurund::UI {

	class ConstraintLayoutManager:public LayoutManager {
	public:
	};

	class ConstraintLayout:public ControlGroup {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = ConstraintLayout::GET_TYPE();
#pragma endregion

	private:
		//List<Guide> guides;

	protected:
		virtual void loadInternal(LayoutLoader& loader, const DirectoryPath& workingDir, const XMLElement& xml) override;

		virtual void onDraw(RenderGroup& group, const XMFLOAT2& parentPosition) override;

	public:
		/*inline List<Guide>& getGuides() {
			return guides;
		}

		__declspec(property(get = getGuides)) List<Guide>& Guides;*/
	};
}
