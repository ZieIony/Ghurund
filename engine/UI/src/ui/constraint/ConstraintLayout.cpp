#include "ghuipch.h"
#include "ConstraintLayout.h"

#include <tinyxml2.h>

#include "Guide.h"
#include "ConstraintGraph.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& ConstraintLayout::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<ConstraintLayout>();
		static Ghurund::Core::Type TYPE = TypeBuilder<ConstraintLayout>()
			.withConstructor(CONSTRUCTOR)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void ConstraintLayout::loadInternal(LayoutLoader& loader, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) {
		__super::loadInternal(loader, workingDir, xml);
		/*const tinyxml2::XMLElement* child = xml.FirstChildElement();
		while (child != nullptr) {
			if (strcmp(child->Name(), "Guide") == 0)
				guides.add(Guide::load(*child));
			child = child->NextSiblingElement();
		}*/
	}

    void ConstraintLayout::onDraw(RenderGroup& group, const XMFLOAT2& parentPosition) {
        __super::onDraw(group, parentPosition);
#ifdef _DEBUG
        /*for (Guide& guide : guides) {
            float position = guide.Value;
            canvas.Color = UIDebugTools::colorConstraints2;
            if (guide.side == Side::TOP || guide.side == Side::BOTTOM) {
                canvas.drawLine(0, position, Size.Width, position, 1.0f, UIDebugTools::getStrokeStyle3());
            } else {
                canvas.drawLine(position, 0, position, Size.Height, 1.0f, UIDebugTools::getStrokeStyle3());
            }
        }*/
#endif
    }

    /*void ConstraintLayout::resolveConstraints(ConstraintGraph& graph) {
        __super::resolveConstraints(graph);
        for (Guide& guide : guides)
            guide.resolve(*this);
        for (Guide& guide : guides) {
            if (guide.positionConstraint)
                graph.add(guide.positionConstraint);
            if (guide.sizeConstraint)
                graph.add(guide.sizeConstraint);
        }
    }*/
}