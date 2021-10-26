#pragma once

#include "ui/text/TextFormat.h"

namespace Ghurund::UI {
    __interface TextFormatFactory {
        TextFormat* makeTextFormat();
    };
}