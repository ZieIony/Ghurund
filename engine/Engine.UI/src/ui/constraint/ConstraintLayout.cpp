#include "ghuipch.h"
#include "ConstraintLayout.h"

#include "Constraint.h"
#include "Guide.h"
#include "core/collection/Set.h"
#include "ui/constraint/ConstraintGraph.h"
#include "ui/loading/LayoutLoader.h"

namespace Ghurund::UI {
    void ConstraintLayout::onContextChanged() {
        __super::onContextChanged();
        if (Context) {
            Array<float> dashes = { 3.0f, 4.0f };
            strokeStyle.reset(Context->makeStrokeStyle(dashes));
        }
    }

    void ConstraintLayout::onLayout(float x, float y, float width, float height) {
        __super::onLayout(x, y, width, height);
        for (Control* control : Children) {
            control->layout(x, y, control->MeasuredSize.Width, control->MeasuredSize.Height);
        }
    }

    void ConstraintLayout::load(LayoutLoader& loader, ResourceManager& resourceManager, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) {
        __super::load(loader, resourceManager, workingDir, xml);
        const tinyxml2::XMLElement* child = xml.FirstChildElement();
        while (child != nullptr) {
            if (strcmp(child->Name(), "Guide") == 0)
                guides.add(Guide::load(*child));
            child = child->NextSiblingElement();
        }
    }

    void ConstraintLayout::onDraw(ICanvas& canvas) {
        __super::onDraw(canvas);
        Color color = Color(0x7f0000ff);
        for (Guide& guide : guides) {
            float position = guide.Value;
            canvas.Color = color;
            if (guide.side == Side::TOP || guide.side == Side::BOTTOM) {
                canvas.drawLine(0, position, Size.Width, position, 1.0f, strokeStyle.get());
            } else {
                canvas.drawLine(position, 0, position, Size.Height, 1.0f, strokeStyle.get());
            }
        }
    }

    void ConstraintLayout::resolveConstraints(ConstraintGraph& graph) {
        __super::resolveConstraints(graph);
        for (Guide& guide : guides)
            guide.resolve(*this);
        for (Guide& guide : guides) {
            if (guide.positionConstraint)
                graph.add(guide.positionConstraint);
            if (guide.sizeConstraint)
                graph.add(guide.sizeConstraint);
        }
    }

    const Ghurund::Core::Type& ConstraintLayout::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<ConstraintLayout>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<ConstraintLayout>(Ghurund::UI::NAMESPACE_NAME, GH_STRINGIFY(ConstraintLayout))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
