#include "ghuipch.h"
#include "LinearLayoutManager.h"

namespace Ghurund::UI {
    Ghurund::Core::FloatSize LinearLayoutManager::measureHorizontal(float parentWidth, float parentHeight) {
        contentSize = 0.0f;
        spreadCount = 0;

        for (Control* c : group->Children) {
            if (!c->Visible)
                continue;
            if (group->PreferredSize.height == PreferredSize::Height::WRAP && c->PreferredSize.height == PreferredSize::Height::FILL)
                continue;
            c->measure(
                group->PreferredSize.width == PreferredSize::Width::FILL ? parentWidth : group->PreferredSize.width.Value,
                group->PreferredSize.height == PreferredSize::Height::FILL ? parentHeight : group->PreferredSize.height.Value
            );
        }
        float maxHeight = measureMaxHeight();
        for (Control* c : group->Children) {
            if (!c->Visible)
                continue;
            if (group->PreferredSize.height == PreferredSize::Height::WRAP && c->PreferredSize.height == PreferredSize::Height::FILL) {
                c->measure(
                    group->PreferredSize.width == PreferredSize::Width::FILL ? parentWidth : group->PreferredSize.width.Value,
                    maxHeight
                );
            }
            if (c->PreferredSize.width == PreferredSize::Width::FILL) {
                spreadCount++;
            } else if (c->PreferredSize.width.Type == PreferredSize::Type::PIXELS) {
                contentSize += std::max(c->MinSize.width, c->PreferredSize.width.Value);
            } else {
                contentSize += c->MeasuredSize.width;
            }
        }

        float measuredwidth = 0;
        if (group->PreferredSize.width.Type == PreferredSize::Type::PIXELS) {
            measuredwidth = group->PreferredSize.width.Value;
        } else {
            for (Control* c : group->Children) {
                if (c->PreferredSize.width.Type == PreferredSize::Type::PIXELS) {
                    measuredwidth += std::max(c->MinSize.width, c->PreferredSize.width.Value);
                } else {
                    measuredwidth += c->MeasuredSize.width;
                }
            }
        }

        return { std::max(group->MinSize.width, measuredwidth), maxHeight };
    }

    Ghurund::Core::FloatSize LinearLayoutManager::measureVertical(float parentWidth, float parentHeight) {
        contentSize = 0.0f;
        spreadCount = 0;

        for (Control* c : group->Children) {
            if (!c->Visible)
                continue;
            if (group->PreferredSize.width == PreferredSize::Width::WRAP && c->PreferredSize.width == PreferredSize::Width::FILL)
                continue;
            c->measure(
                group->PreferredSize.width == PreferredSize::Width::FILL ? parentWidth : group->PreferredSize.width.Value,
                group->PreferredSize.height == PreferredSize::Height::FILL ? parentHeight : group->PreferredSize.height.Value
            );
        }
        float maxWidth = measureMaxWidth();
        for (Control* c : group->Children) {
            if (!c->Visible)
                continue;
            if (group->PreferredSize.width == PreferredSize::Width::WRAP && c->PreferredSize.width == PreferredSize::Width::FILL) {
                c->measure(
                    maxWidth,
                    group->PreferredSize.height == PreferredSize::Height::FILL ? parentHeight : group->PreferredSize.height.Value
                );
            }
            if (c->PreferredSize.height == PreferredSize::Height::FILL) {
                spreadCount++;
            } else if (c->PreferredSize.height.Type == PreferredSize::Type::PIXELS) {
                contentSize += std::max(c->MinSize.height, c->PreferredSize.height.Value);
            } else {
                contentSize += c->MeasuredSize.height;
            }
        }

        float measuredHeight = 0;
        if (group->PreferredSize.height.Type == PreferredSize::Type::PIXELS) {
            measuredHeight = group->PreferredSize.height.Value;
        } else {
            for (Control* c : group->Children) {
                if (c->PreferredSize.height.Type == PreferredSize::Type::PIXELS) {
                    measuredHeight += std::max(c->MinSize.height, c->PreferredSize.height.Value);
                } else {
                    measuredHeight += c->MeasuredSize.height;
                }
            }
        }

        return { maxWidth, std::max(group->MinSize.height, measuredHeight) };
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
            } else if (c->PreferredSize.width.Type == PreferredSize::Type::PIXELS) {
                w = std::min(c->PreferredSize.width.Value, width);
                w = std::max(w, c->MinSize.width);
            } else {
                w = std::min(c->MeasuredSize.width, width);
            }

            float h;
            if (c->PreferredSize.height == PreferredSize::Height::FILL) {
                h = std::max(height, c->MinSize.height);
            } else if (c->PreferredSize.height.Type == PreferredSize::Type::PIXELS) {
                h = std::min(c->PreferredSize.height.Value, height);
                h = std::max(h, c->MinSize.height);
            } else {
                h = std::min(c->MeasuredSize.height, height);
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
            } else if (c->PreferredSize.width.Type == PreferredSize::Type::PIXELS) {
                w = std::min(c->PreferredSize.width.Value, width);
                w = std::max(w, c->MinSize.width);
            } else {
                w = std::min(c->MeasuredSize.width, width);
            }

            float h;
            if (c->PreferredSize.height == PreferredSize::Height::FILL) {
                h = std::max(spaceLeft / spreadCount, c->MinSize.height);
            } else if (c->PreferredSize.height.Type == PreferredSize::Type::PIXELS) {
                h = std::min(c->PreferredSize.height.Value, height);
                h = std::max(h, c->MinSize.height);
            } else {
                h = std::min(c->MeasuredSize.height, height);
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
