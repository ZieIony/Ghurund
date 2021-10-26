#include "ghuipch.h"
#include "FlowLayoutManager.h"

namespace Ghurund::UI {
    void FlowLayoutManager::layoutFlowingControlsRight(float width) {
        float currentX = width;
        float currentY = 0;
        float nextY = 0;
        List<Control*> currentLine;
        for (Control* child : group->Children) {
            if (!child->Visible)
                continue;

            float minWidth = std::max(child->PreferredSize.width != PreferredSize::Width::FILL ? child->MeasuredSize.width : 0.0f, child->MinSize.width);
            float minHeight = std::max(child->PreferredSize.height != PreferredSize::Height::FILL ? child->MeasuredSize.height : 0.0f, child->MinSize.height);

            if (currentX != width && currentX - minWidth < 0) {
                currentX = width;
                currentY = nextY + spacing.vertical;
                //relayoutLine(currentLine);
                currentLine.clear();
            }

            currentLine.insert(0, child);
            float childWidth = child->PreferredSize.width == PreferredSize::Width::FILL ? currentX : minWidth;
            child->layout(currentX - childWidth, currentY, childWidth, minHeight);
            currentX -= childWidth + spacing.horizontal;
            nextY = std::max(nextY, currentY + minHeight);

            if (child->PreferredSize.width == PreferredSize::Width::FILL) {
                currentX = width;
                currentY = nextY + spacing.vertical;
                //relayoutLine(currentLine);
                currentLine.clear();
            }
        }
        //relayoutLine(currentLine);
    }

    void FlowLayoutManager::layoutFlowingControlsLeft(float width) {
        float currentX = 0;
        float currentY = 0;
        float nextY = 0;
        List<Control*> currentLine;
        for (Control* child : group->Children) {
            if (!child->Visible)
                continue;

            float minWidth = std::max(child->PreferredSize.width != PreferredSize::Width::FILL ? child->MeasuredSize.width : 0.0f, child->MinSize.width);
            float minHeight = std::max(child->PreferredSize.height != PreferredSize::Height::FILL ? child->MeasuredSize.height : 0.0f, child->MinSize.height);

            if (currentX != 0 && currentX + minWidth > width) {
                currentX = 0;
                currentY = nextY + spacing.vertical;
                //relayoutLine(currentLine);
                currentLine.clear();
            }

            currentLine.add(child);
            float childWidth = child->PreferredSize.width == PreferredSize::Width::FILL ? width - currentX : minWidth;
            child->layout(currentX, currentY, childWidth, minHeight);
            currentX += minWidth + spacing.horizontal;
            nextY = std::max(nextY, currentY + minHeight);

            if (child->PreferredSize.width == PreferredSize::Width::FILL) {
                currentX = 0;
                currentY = nextY + spacing.vertical;
                //relayoutLine(currentLine);
                currentLine.clear();
            }
        }
        //relayoutLine(currentLine);
    }

    float FlowLayoutManager::measureWidth() {
        float currentX = 0;
        for (Control* child : group->Children) {
            if (child->Visible) {
                float minWidth = std::max(child->PreferredSize.width != PreferredSize::Width::FILL ? child->MeasuredSize.width : 0.0f, child->MinSize.width);
                currentX += minWidth + spacing.horizontal;
            }
        }

        return currentX > 0 ? currentX - spacing.horizontal : 0;
    }

    float FlowLayoutManager::measureHeight(float width) {
        float currentX = 0;
        float currentY = 0;
        float nextY = 0;
        for (Control* child : group->Children) {
            if (!child->Visible)
                continue;

            float minWidth = std::max(child->PreferredSize.width != PreferredSize::Width::FILL ? child->MeasuredSize.width : 0.0f, child->MinSize.width);
            float minHeight = std::max(child->PreferredSize.height != PreferredSize::Height::FILL ? child->MeasuredSize.height : 0.0f, child->MinSize.height);

            if (currentX != 0 && currentX + minWidth > width && width != 0) {
                currentX = 0;
                currentY = nextY + spacing.vertical;
            }

            nextY = std::max(nextY, currentY + minHeight);
            if (child->PreferredSize.width == PreferredSize::Width::FILL) {
                currentX = 0;
                currentY = nextY + spacing.vertical;
            } else {
                currentX += minWidth + spacing.horizontal;
            }
        }
        return nextY;
    }

    const FloatSize FlowLayoutManager::measure(float parentWidth, float parentHeight) {
        for (Control* c : group->Children) {
            if (!c->Visible)
                continue;
            c->measure(
                group->PreferredSize.width.Type == PreferredSize::Type::PIXELS ? group->PreferredSize.width.Value : parentWidth,
                group->PreferredSize.height.Type == PreferredSize::Type::PIXELS ? group->PreferredSize.height.Value : parentHeight
            );
        }

        FloatSize measuredSize = { 0,0 };

        if (group->PreferredSize.width == PreferredSize::Width::WRAP) {
            measuredSize.width = std::min(measureWidth(), parentWidth);
        } else if (group->PreferredSize.width != PreferredSize::Width::FILL) {
            measuredSize.width = group->PreferredSize.height.Value;
        }

        if (group->PreferredSize.height == PreferredSize::Height::WRAP) {
            measuredSize.height = measureHeight(parentWidth);
        } else if (group->PreferredSize.height != PreferredSize::Height::FILL) {
            measuredSize.height = group->PreferredSize.height.Value;
        }

        return measuredSize;
    }

    void FlowLayoutManager::layout(float x, float y, float width, float height) {
        if (reverseLayout) {
            layoutFlowingControlsRight(width);
        } else {
            layoutFlowingControlsLeft(width);
        }
    }
}
