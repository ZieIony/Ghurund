#include "ghuipch.h"
#include "TextFormatAttr.h"

#include "ui/control/Control.h"

namespace Ghurund::UI {

    const TextFormat* TextFormatRef::getValue(const Control& owner) const {
        return owner.Theme->TextFormats[key].get();
    }

}
