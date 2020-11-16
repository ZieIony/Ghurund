#include "TextLayoutManager.h"

namespace Ghurund::UI {
    void TextLayoutManager::layoutFlowingControlsRight(ControlGroup& group, float width) {
        float currentX = width;
        float currentY = 0;
        float nextY = 0;
        List<Control*> currentLine;
        for (Control* child : group.Children) {
            if (!child->Visible)
                continue;

            float minWidth = std::max(child->PreferredSize.width != PreferredSize::Width::FILL ? child->MeasuredSize.width : 0.0f, child->MinSize.width);
            float minHeight = std::max(child->PreferredSize.height != PreferredSize::Height::FILL ? child->MeasuredSize.height : 0.0f, child->MinSize.height);

            if (currentX != width && currentX - minWidth < 0) {
                currentX = width;
                currentY = nextY + verticalSpacing;
                //relayoutLine(currentLine);
                currentLine.clear();
            }

            currentLine.insert(0, child);
            float childWidth = child->PreferredSize.width == PreferredSize::Width::FILL ? currentX : minWidth;
            child->layout(currentX - childWidth, currentY, childWidth, minHeight);
            currentX -= childWidth + horizontalSpacing;
            nextY = std::max(nextY, currentY + minHeight);

            if (child->PreferredSize.width == PreferredSize::Width::FILL) {
                currentX = width;
                currentY = nextY + verticalSpacing;
                //relayoutLine(currentLine);
                currentLine.clear();
            }
        }
        //relayoutLine(currentLine);
    }

    void TextLayoutManager::layoutFlowingControlsLeft(ControlGroup& group, float width) {
        float currentX = 0;
        float currentY = 0;
        float nextY = 0;
        List<Control*> currentLine;
        for (Control* child : group.Children) {
            if (!child->Visible)
                continue;

            float minWidth = std::max(child->PreferredSize.width != PreferredSize::Width::FILL ? child->MeasuredSize.width : 0.0f, child->MinSize.width);
            float minHeight = std::max(child->PreferredSize.height != PreferredSize::Height::FILL ? child->MeasuredSize.height : 0.0f, child->MinSize.height);

            if (currentX != 0 && currentX + minWidth > width) {
                currentX = 0;
                currentY = nextY + verticalSpacing;
                //relayoutLine(currentLine);
                currentLine.clear();
            }

            currentLine.add(child);
            float childWidth = child->PreferredSize.width == PreferredSize::Width::FILL ? width - currentX : minWidth;
            child->layout(currentX, currentY, childWidth, minHeight);
            currentX += minWidth + horizontalSpacing;
            nextY = std::max(nextY, currentY + minHeight);

            if (child->PreferredSize.width == PreferredSize::Width::FILL) {
                currentX = 0;
                currentY = nextY + verticalSpacing;
                //relayoutLine(currentLine);
                currentLine.clear();
            }
        }
        //relayoutLine(currentLine);
    }

    float TextLayoutManager::measureWidth(ControlGroup& group) {
        float currentX = 0;
        for (Control* child : group.Children) {
            if (child->Visible) {
                float minWidth = std::max(child->PreferredSize.width != PreferredSize::Width::FILL ? child->MeasuredSize.width : 0.0f, child->MinSize.width);
                currentX += minWidth + horizontalSpacing;
            }
        }

        return currentX > 0 ? currentX - horizontalSpacing : 0;
    }

    int TextLayoutManager::measureHeight(ControlGroup& group, int width) {
        int currentX = 0;
        int currentY = 0;
        float nextY = 0;
        for (Control* child : group.Children) {
            if (!child->Visible)
                continue;

            float minWidth = std::max(child->PreferredSize.width != PreferredSize::Width::FILL ? child->MeasuredSize.width : 0.0f, child->MinSize.width);
            float minHeight = std::max(child->PreferredSize.height != PreferredSize::Height::FILL ? child->MeasuredSize.height : 0.0f, child->MinSize.height);

            if (currentX != 0 && currentX + minWidth > width && width != 0) {
                currentX = 0;
                currentY = nextY + verticalSpacing;
            }

            nextY = std::max(nextY, currentY + minHeight);
            if (child->PreferredSize.width == PreferredSize::Width::FILL) {
                currentX = 0;
                currentY = nextY + verticalSpacing;
            } else {
                currentX += minWidth + horizontalSpacing;
            }
        }
        return nextY;
    }

    const FloatSize TextLayoutManager::measure(ControlGroup& group, ChildrenProvider& provider, float parentWidth, float parentHeight) {
        for (Control* c : group.Children) {
            if (!c->Visible)
                continue;
            c->measure(
                group.PreferredSize.width >= 0 ? (float)group.PreferredSize.width : parentWidth,
                group.PreferredSize.height >= 0 ? (float)group.PreferredSize.height : parentHeight
            );
        }

        FloatSize measuredSize = { 0,0 };

        if (group.PreferredSize.width == PreferredSize::Width::WRAP) {
            measuredSize.width = std::min(measureWidth(group), parentWidth);
        } else if (group.PreferredSize.width != PreferredSize::Width::FILL) {
            measuredSize.width = (float)group.PreferredSize.height;
        }

        if (group.PreferredSize.height == PreferredSize::Height::WRAP) {
            measuredSize.height = measureHeight(group, parentWidth);
        } else if (group.PreferredSize.height != PreferredSize::Height::FILL) {
            measuredSize.height = (float)group.PreferredSize.height;
        }

        return measuredSize;
    }

    void TextLayoutManager::layout(ControlGroup& group, ChildrenProvider& provider, float x, float y, float width, float height) {
        if (reverseLayout) {
            layoutFlowingControlsRight(group, width);
        } else {
            layoutFlowingControlsLeft(group, width);
        }
    }
}
