#pragma once

#include "SizeConstraints.h"

#include "ui/control/Control.h"
#include <ui/constraint/ParentConstraint.h>

namespace Ghurund::UI {
    class ItemAdapter {
    public:
        virtual ~ItemAdapter() = 0 {}

        virtual size_t getSize() const = 0;

        __declspec(property(get = getSize)) size_t Size;
   
        virtual size_t getType(size_t position) const {
            return 0;
        }

        virtual Control* makeControl(size_t type) const = 0;

        virtual SizeConstraints makeSizeConstraints(size_t position) const {
            return SizeConstraints(
				SharedPointer<Constraint>(ghnew ParentWidthConstraint()),
                SharedPointer<Constraint>(ghnew WrapHeightConstraint())
			);
        }

        virtual void bind(Control& control, size_t position) const = 0;
    };
}