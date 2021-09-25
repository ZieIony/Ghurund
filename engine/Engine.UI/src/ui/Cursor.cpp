#include "ghuipch.h"
#include "Cursor.h"

namespace Ghurund::UI {
    const Cursor Cursor::APPSTARTING = Cursor(CursorEnum::APPSTARTING, "APPSTARTING", IDC_APPSTARTING);
    const Cursor Cursor::ARROW = Cursor(CursorEnum::ARROW, "ARROW", IDC_ARROW);
    const Cursor Cursor::CROSS = Cursor(CursorEnum::CROSS, "CROSS", IDC_CROSS);
    const Cursor Cursor::HAND = Cursor(CursorEnum::HAND, "HAND", IDC_HAND);
    const Cursor Cursor::HELP = Cursor(CursorEnum::HELP, "HELP", IDC_HELP);
    const Cursor Cursor::IBEAM = Cursor(CursorEnum::IBEAM, "IBEAM", IDC_IBEAM);
    const Cursor Cursor::NO = Cursor(CursorEnum::NO, "NO", IDC_NO);
    const Cursor Cursor::SIZEALL = Cursor(CursorEnum::SIZEALL, "SIZEALL", IDC_SIZEALL);
    const Cursor Cursor::SIZENESW = Cursor(CursorEnum::SIZENESW, "SIZENESW", IDC_SIZENESW);
    const Cursor Cursor::SIZENS = Cursor(CursorEnum::SIZENS, "SIZENS", IDC_SIZENS);
    const Cursor Cursor::SIZENWSE = Cursor(CursorEnum::SIZENWSE, "SIZENWSE", IDC_SIZENWSE);
    const Cursor Cursor::SIZEWE = Cursor(CursorEnum::SIZEWE, "SIZEWE", IDC_SIZEWE);
    const Cursor Cursor::UPARROW = Cursor(CursorEnum::UPARROW, "UPARROW", IDC_UPARROW);
    const Cursor Cursor::WAIT = Cursor(CursorEnum::WAIT, "WAIT", IDC_WAIT);

    const Ghurund::Core::EnumValues<CursorEnum, Cursor> Cursor::VALUES = {
        &Cursor::APPSTARTING,
        &Cursor::ARROW,
        &Cursor::CROSS,
        &Cursor::HAND,
        &Cursor::HELP,
        &Cursor::IBEAM,
        &Cursor::NO,
        &Cursor::SIZEALL,
        &Cursor::SIZENESW,
        &Cursor::SIZENS,
        &Cursor::SIZENWSE,
        &Cursor::SIZEWE,
        &Cursor::UPARROW,
        &Cursor::WAIT
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::Cursor>() {
        static Type TYPE = Type(Ghurund::UI::NAMESPACE_NAME, "Cursor", sizeof(Ghurund::UI::Cursor));
        return TYPE;
    }
}