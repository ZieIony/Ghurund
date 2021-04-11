#include "ghuipch.h"
#include "LinearLayoutManager.h"

namespace Ghurund::UI {
    FloatSize LinearLayoutManager::measureHorizontal(float parentWidth, float parentHeight) {
        contentSize = 0.0f;
        spreadCount = 0;

        for (Control* c : group->Children) {
            c->measure(
                group->PreferredSize.width >= 0 ? (float)group->PreferredSize.width : parentWidth,
                group->PreferredSize.height >= 0 ? (float)group->PreferredSize.height : parentHeight
            );
            if (c->PreferredSize.width == PreferredSize::Width::FILL) {
                spreadCount++;
            } else if (c->PreferredSize.width >= 0) {
                contentSize += std::max(c->MinSize.width, (float)c->PreferredSize.width);
            } else {
                contentSize += c->MeasuredSize.width;
            }
        }

        float measuredwidth = 0;
        if (group->PreferredSize.width >= 0) {
            measuredwidth = (float)group->PreferredSize.width;
        } else {
            for (Control* c : group->Children) {
                if (c->PreferredSize.width >= 0) {
                    measuredwidth += std::max(c->MinSize.width, (float)c->PreferredSize.width);
                } else {
                    measuredwidth += c->MeasuredSize.width;
                }
            }
        }

        return { std::max(group->MinSize.width, measuredwidth), measureMaxHeight() };
    }

    FloatSize LinearLayoutManager::measureVertical(float parentWidth, float parentHeight) {
        contentSize = 0.0f;
        spreadCount = 0;

        for (Control* c : group->Children) {
            if (!c->Visible)
                continue;
            c->measure(
                group->PreferredSize.width >= 0 ? (float)group->PreferredSize.width : parentWidth,
                group->PreferredSize.height >= 0 ? (float)group->PreferredSize.height : parentHeight
            );
            if (c->PreferredSize.height == PreferredSize::Height::FILL) {
                spreadCount++;
            } else if (c->PreferredSize.height >= 0) {
                contentSize += std::max(c->MinSize.height, (float)c->PreferredSize.height);
            } else {
                contentSize += c->MeasuredSize.height;
            }
        }

        float measuredHeight = 0;
        if (group->PreferredSize.height >= 0) {
            measuredHeight = (float)group->PreferredSize.height;
        } else {
            for (Control* c : group->Children) {
                if (c->PreferredSize.height >= 0) {
                    measuredHeight += std::max(c->MinSize.height, (float)c->PreferredSize.height);
                } else {
                    measuredHeight += c->MeasuredSize.height;
                }
            }
        }

        return { measureMaxWidth(), std::max(group->MinSize.height, measuredHeight) };
    }

    void LinearLayoutManager::layoutHorizontal(float x, float y, float width, float height) {
        float spaceLeft = std::max(0.0f, width - contentSize);
        float currentX;
        if (alignment.horizontal == Alignment::Horizontal::LEFT || spreadCount > 0) {
            currentX = 0.0f;
        } else if (alignment.horizontal == Alignment::Horizontal::CENTER) {
            currentX = spaceLeft / 2.0f;
        } else {
            currentX = spaceLeft;
        }

        for (Control* c : group->Children) {
            if (!c->Visible)
                continue;
            float w;
            if (c->PreferredSize.width == PreferredSize::Width::FILL) {
                w = std::max(spaceLeft / spreadCount, c->MinSize.width);
            } else if (c->PreferredSize.width >= 0) {
                w = std::min((float)c->PreferredSize.width, width);
                w = std::max(w, c->MinSize.width);
            } else {
                w = std::min(c->MeasuredSize.width, width);
            }

            float h;
            if (c->PreferredSize.height == PreferredSize::Height::FILL) {
                h = std::max(height, c->MinSize.height);
            } else if (c->PreferredSize.height >= 0) {
                h = std::min((float)c->PreferredSize.height, height);
                h = std::max(h, c->MinSize.height);
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

    void LinearLayoutManager::layoutVertical(float x, float y, float width, float height) {
        float spaceLeft = std::max(0.0f, height - contentSize);
        float currentY = 0.0f;
        if (alignment.vertical == Alignment::Vertical::TOP || spreadCount > 0) {
            currentY = 0.0f;
        } else if (alignment.vertical == Alignment::Vertical::CENTER) {
            currentY = spaceLeft / 2.0f;
        } else {
            currentY = spaceLeft;
        }

        for (Control* c : group->Children) {
            if (!c->Visible)
                continue;
            float w;
            if (c->PreferredSize.width == PreferredSize::Width::FILL) {
                w = std::max(width, c->MinSize.height);
            } else if (c->PreferredSize.width >= 0) {
                w = std::min((float)c->PreferredSize.width, width);
                w = std::max(w, c->MinSize.width);
            } else {
                w = std::min((float)c->MeasuredSize.width, width);
            }

            float h;
            if (c->PreferredSize.height == PreferredSize::Height::FILL) {
                h = std::max(spaceLeft / spreadCount, c->MinSize.height);
            } else if (c->PreferredSize.height >= 0) {
                h = std::min((float)c->PreferredSize.height, height);
                h = std::max(h, c->MinSize.height);
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

    const FloatSize LinearLayoutManager::measure(float parentWidth, float parentHeight) {
        if (orientation == Orientation::HORIZONTAL) {
            return measureHorizontal(parentWidth, parentHeight);
        } else {
            return measureVertical(parentWidth, parentHeight);
        }
    }

    void LinearLayoutManager::layout(float x, float y, float width, float height) {
        if (orientation == Orientation::HORIZONTAL) {
            layoutHorizontal(x, y, width, height);
        } else {
            layoutVertical(x, y, width, height);
        }
    }
}
