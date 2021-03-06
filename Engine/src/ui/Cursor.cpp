#include "ghpch.h"
#include "Cursor.h"

namespace Ghurund::UI {
    const Cursor Cursor::APPSTARTING = Cursor(CursorEnum::APPSTARTING, _T("APPSTARTING"), IDC_APPSTARTING);
    const Cursor Cursor::ARROW = Cursor(CursorEnum::ARROW, _T("ARROW"), IDC_ARROW);
    const Cursor Cursor::CROSS = Cursor(CursorEnum::CROSS, _T("CROSS"), IDC_CROSS);
    const Cursor Cursor::HAND = Cursor(CursorEnum::HAND, _T("HAND"), IDC_HAND);
    const Cursor Cursor::HELP = Cursor(CursorEnum::HELP, _T("HELP"), IDC_HELP);
    const Cursor Cursor::IBEAM = Cursor(CursorEnum::IBEAM, _T("IBEAM"), IDC_IBEAM);
    const Cursor Cursor::NO = Cursor(CursorEnum::NO, _T("NO"), IDC_NO);
    const Cursor Cursor::SIZEALL = Cursor(CursorEnum::SIZEALL, _T("SIZEALL"), IDC_SIZEALL);
    const Cursor Cursor::SIZENESW = Cursor(CursorEnum::SIZENESW, _T("SIZENESW"), IDC_SIZENESW);
    const Cursor Cursor::SIZENS = Cursor(CursorEnum::SIZENS, _T("SIZENS"), IDC_SIZENS);
    const Cursor Cursor::SIZENWSE = Cursor(CursorEnum::SIZENWSE, _T("SIZENWSE"), IDC_SIZENWSE);
    const Cursor Cursor::SIZEWE = Cursor(CursorEnum::SIZEWE, _T("SIZEWE"), IDC_SIZEWE);
    const Cursor Cursor::UPARROW = Cursor(CursorEnum::UPARROW, _T("UPARROW"), IDC_UPARROW);
    const Cursor Cursor::WAIT = Cursor(CursorEnum::WAIT, _T("WAIT"), IDC_WAIT);

    const EnumValues<CursorEnum, Cursor> Cursor::VALUES = {
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