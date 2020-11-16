#include "LinearLayoutManager.h"

namespace Ghurund::UI {
    FloatSize LinearLayoutManager::measureHorizontal(ControlGroup& group, float parentWidth, float parentHeight) {
        contentSize = 0.0f;
        spreadCount = 0;

        for (Control* c : group.Children) {
            c->measure(
                group.PreferredSize.width >= 0 ? (float)group.PreferredSize.width : parentWidth,
                group.PreferredSize.height >= 0 ? (float)group.PreferredSize.height : parentHeight
            );
            if (c->PreferredSize.width != PreferredSize::Width::FILL) {
                contentSize += (float)c->MeasuredSize.width;
            } else {
                spreadCount++;
            }
        }

        float measuredwidth = 0;
        if (group.PreferredSize.width == PreferredSize::Width::WRAP) {
            for (Control* c : group.Children) {
                if (c->PreferredSize.width != PreferredSize::Width::FILL)
                    measuredwidth += (float)c->MeasuredSize.width;
            }
        } else if (group.PreferredSize.width != PreferredSize::Width::FILL) {
            measuredwidth = (float)group.PreferredSize.width;
        }

        return { measuredwidth, measureMaxHeight(group) };
    }

    FloatSize LinearLayoutManager::measureVertical(ControlGroup& group, float parentWidth, float parentHeight) {
        contentSize = 0.0f;
        spreadCount = 0;

        for (Control* c : group.Children) {
            if (!c->Visible)
                continue;
            c->measure(
                group.PreferredSize.width >= 0 ? (float)group.PreferredSize.width : parentWidth,
                group.PreferredSize.height >= 0 ? (float)group.PreferredSize.height : parentHeight
            );
            if (c->PreferredSize.height != PreferredSize::Height::FILL) {
                contentSize += (float)c->MeasuredSize.height;
            } else {
                spreadCount++;
            }
        }

        float measuredHeight = 0;
        if (group.PreferredSize.height == PreferredSize::Height::WRAP) {
            for (Control* c : group.Children) {
                if (c->PreferredSize.height != PreferredSize::Height::FILL)
                    measuredHeight += (float)c->MeasuredSize.height;
            }
        } else if (group.PreferredSize.height != PreferredSize::Height::FILL) {
            measuredHeight = (float)group.PreferredSize.height;
        }

        return { measureMaxWidth(group), measuredHeight };
    }

    void LinearLayoutManager::layoutHorizontal(ControlGroup& group, float x, float y, float width, float height) {
        float spaceLeft = std::max(0.0f, width - contentSize);
        float currentX;
        if (alignment.horizontal == Alignment::Horizontal::LEFT || spreadCount > 0) {
            currentX = 0.0f;
        } else if (alignment.horizontal == Alignment::Horizontal::CENTER) {
            currentX = spaceLeft / 2.0f;
        } else {
            currentX = spaceLeft;
        }

        for (Control* c : group.Children) {
            if (!c->Visible)
                continue;
            float w;
            if (c->PreferredSize.width == PreferredSize::Width::FILL) {
                w = spaceLeft / spreadCount;
            } else {
                w = std::min(c->MeasuredSize.width, width);
            }

            float h;
            if (c->PreferredSize.height == PreferredSize::Height::FILL) {
                h = height;
            } else {
                h = std::min((float)c->MeasuredSize.height, height);
            }

            float ity;
            if (alignment.vertical == Alignment::Vertical::TOP) {
                ity = 0;
            } else if (alignment.vertical == Alignment::Vertical::BOTTOM) {
                ity = height - h;
            } else {
                ity = (height - h) / 2;
            }

            c->layout(currentX, ity, w, h);
            currentX += w;
        }
    }

    void LinearLayoutManager::layoutVertical(ControlGroup& group, float x, float y, float width, float height) {
        float spaceLeft = std::max(0.0f, height - contentSize);
        float currentY = 0.0f;
        if (alignment.vertical == Alignment::Vertical::TOP || spreadCount > 0) {
            currentY = 0.0f;
        } else if (alignment.vertical == Alignment::Vertical::CENTER) {
            currentY = spaceLeft / 2.0f;
        } else {
            currentY = spaceLeft;
        }

        for (Control* c : group.Children) {
            if (!c->Visible)
                continue;
            float w;
            if (c->PreferredSize.width == PreferredSize::Width::FILL) {
                w = width;
            } else {
                w = std::min((float)c->MeasuredSize.width, width);
            }

            float h;
            if (c->PreferredSize.height == PreferredSize::Height::FILL) {
                h = spaceLeft / spreadCount;
            } else {
                h = std::min((float)c->MeasuredSize.height, height);
            }

            float itx;
            if (alignment.horizontal == Alignment::Horizontal::LEFT) {
                itx = 0;
            } else if (alignment.horizontal == Alignment::Horizontal::RIGHT) {
                itx = width - w;
            } else {
                itx = (width - w) / 2;
            }

            c->layout(itx, currentY, w, h);
            currentY += h;
        }
    }

    const FloatSize LinearLayoutManager::measure(ControlGroup& group, ChildrenProvider& provider, float parentWidth, float parentHeight) {
        if (orientation == Orientation::HORIZONTAL) {
            return measureHorizontal(group, parentWidth, parentHeight);
        } else {
            return measureVertical(group, parentWidth, parentHeight);
        }
    }
    
    void LinearLayoutManager::layout(ControlGroup& group, ChildrenProvider& provider, float x, float y, float width, float height) {
        if (orientation == Orientation::HORIZONTAL) {
            layoutHorizontal(group, x, y, width, height);
        } else {
            layoutVertical(group, x, y, width, height);
        }
    }
}
