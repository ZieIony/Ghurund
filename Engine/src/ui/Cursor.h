#pragma once

#include "Common.h"
#include "core/Enum.h"

namespace Ghurund::UI {
    enum class CursorEnum {
        APPSTARTING,    // Standard arrowand small hourglass
        ARROW,  // Standard arrow
        CROSS,  // Crosshair
        HAND,   // Hand
        HELP,   // Arrow and question mark
        IBEAM,  // I-beam
        NO, // Slashed circle
        SIZEALL,    // Four-pointed arrow pointing north, south, east, and west
        SIZENESW,   // Double-pointed arrow pointing northeast and southwest
        SIZENS, // Double - pointed arrow pointing north and south
        SIZENWSE,   // Double - pointed arrow pointing northwest and southeast
        SIZEWE, // Double - pointed arrow pointing west and east
        UPARROW,    // Vertical arrow
        WAIT    // Wait
    };

    class Cursor :public Enum<CursorEnum, Cursor> {
    private:
        const char* constantName;
        HCURSOR handle;

    public:
        static const Cursor APPSTARTING, ARROW, CROSS,
            HAND, HELP, IBEAM, NO, SIZEALL, SIZENESW,
            SIZENS, SIZENWSE, SIZEWE, UPARROW, WAIT;

        static const EnumValues<CursorEnum, Cursor> VALUES;

        Cursor(CursorEnum value, const tchar* name, const tchar* resource):Enum<CursorEnum, Cursor>(value, name) {
            this->constantName = constantName;
            handle = LoadCursor(nullptr, resource);
        }

        void set() {
            SetCursor(handle);
        }
    };
}