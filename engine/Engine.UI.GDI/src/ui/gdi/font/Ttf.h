#pragma once

#include <core/string/String.h>

#define SWAPWORD(x) MAKEWORD(HIBYTE(x), LOBYTE(x))
#define SWAPLONG(x) MAKELONG(SWAPWORD(HIWORD(x)), SWAPWORD(LOWORD(x)))

namespace Ghurund::Core {

    //This is TTF file header
    typedef struct _tagTT_OFFSET_TABLE {
        USHORT uMajorVersion;
        USHORT uMinorVersion;
        USHORT uNumOfTables;
        USHORT uSearchRange;
        USHORT uEntrySelector;
        USHORT uRangeShift;
    }TT_OFFSET_TABLE;

    //Tables in TTF file and there placement and name (tag)
    typedef struct _tagTT_TABLE_DIRECTORY {
        char szTag[4]; //table name
        ULONG uCheckSum; //Check sum
        ULONG uOffset; //Offset from beginning of file
        ULONG uLength; //length of the table in bytes
    }TT_TABLE_DIRECTORY;

    //Header of names table
    typedef struct _tagTT_NAME_TABLE_HEADER {
        USHORT uFSelector; //format selector. Always 0
        USHORT uNRCount; //Name Records count
        USHORT uStorageOffset; //Offset for strings storage, 
        //from start of the table
    }TT_NAME_TABLE_HEADER;

    //Record in names table
    typedef struct _tagTT_NAME_RECORD {
        USHORT uPlatformID;
        USHORT uEncodingID;
        USHORT uLanguageID;
        USHORT uNameID;
        USHORT uStringLength;
        USHORT uStringOffset; //from start of storage area
    }TT_NAME_RECORD;

    //Header of fvar table
    typedef struct _tagTT_FVAR_TABLE_HEADER {
        uint16_t majorVersion;
        uint16_t minorVersion;
        uint16_t axesArrayOffset;
        uint16_t reserved;
        uint16_t axisCount;
        uint16_t axisSize;
        uint16_t instanceCount;
        uint16_t instanceSize;
    }TT_FVAR_TABLE_HEADER;

    //Record in fvar table
    typedef struct _tagTT_FVAR_RECORD {
        char axisTag[4];
        FIXED minValue;
        FIXED defaultValue;
        FIXED maxValue;
        uint16_t flags;
        uint16_t axisNameID;
    }TT_FVAR_RECORD;

    //Record in OS/2 table
    typedef struct _tagTT_OS2_RECORD_5 {
        uint16_t version = 5;
        int16_t xAvgCharWidth;
        uint16_t usWeightClass;
        uint16_t usWidthClass;
        uint16_t fsType;
        int16_t ySubscriptXSize;
        int16_t ySubscriptYSize;
        int16_t ySubscriptXOffset;
        int16_t ySubscriptYOffset;
        int16_t ySuperscriptXSize;
        int16_t ySuperscriptYSize;
        int16_t ySuperscriptXOffset;
        int16_t ySuperscriptYOffset;
        int16_t yStrikeoutSize;
        int16_t yStrikeoutPosition;
        int16_t sFamilyClass;
        uint8_t	panose[10];
        uint32_t ulUnicodeRange1;
        uint32_t ulUnicodeRange2;
        uint32_t ulUnicodeRange3;
        uint32_t ulUnicodeRange4;
        char	achVendID[4];
        uint16_t fsSelection;
        uint16_t usFirstCharIndex;
        uint16_t usLastCharIndex;
        int16_t sTypoAscender;
        int16_t sTypoDescender;
        int16_t sTypoLineGap;
        uint16_t usWinAscent;
        uint16_t usWinDescent;
        uint32_t ulCodePageRange1;
        uint32_t ulCodePageRange2;
        int16_t sxHeight;
        int16_t sCapHeight;
        uint16_t usDefaultChar;
        uint16_t usBreakChar;
        uint16_t usMaxContext;
        uint16_t usLowerOpticalPointSize;
        uint16_t usUpperOpticalPointSize;
    }TT_OS2_RECORD_5;

    typedef struct _tagTT_OS2_RECORD_234 {
        uint16_t version = 4;
        int16_t xAvgCharWidth;
        uint16_t usWeightClass;
        uint16_t usWidthClass;
        uint16_t fsType;
        int16_t ySubscriptXSize;
        int16_t ySubscriptYSize;
        int16_t ySubscriptXOffset;
        int16_t ySubscriptYOffset;
        int16_t ySuperscriptXSize;
        int16_t ySuperscriptYSize;
        int16_t ySuperscriptXOffset;
        int16_t ySuperscriptYOffset;
        int16_t yStrikeoutSize;
        int16_t yStrikeoutPosition;
        int16_t sFamilyClass;
        uint8_t	panose[10];
        uint32_t ulUnicodeRange1;
        uint32_t ulUnicodeRange2;
        uint32_t ulUnicodeRange3;
        uint32_t ulUnicodeRange4;
        char	achVendID[4];
        uint16_t fsSelection;
        uint16_t usFirstCharIndex;
        uint16_t usLastCharIndex;
        int16_t sTypoAscender;
        int16_t sTypoDescender;
        int16_t sTypoLineGap;
        uint16_t usWinAscent;
        uint16_t usWinDescent;
        uint32_t ulCodePageRange1;
        uint32_t ulCodePageRange2;
        int16_t sxHeight;
        int16_t sCapHeight;
        uint16_t usDefaultChar;
        uint16_t usBreakChar;
        uint16_t usMaxContext;
    }TT_OS2_RECORD_234;

    typedef struct _tagTT_OS2_RECORD_1 {
        uint16_t version = 1;
        int16_t xAvgCharWidth;
        uint16_t usWeightClass;
        uint16_t usWidthClass;
        uint16_t fsType;
        int16_t ySubscriptXSize;
        int16_t ySubscriptYSize;
        int16_t ySubscriptXOffset;
        int16_t ySubscriptYOffset;
        int16_t ySuperscriptXSize;
        int16_t ySuperscriptYSize;
        int16_t ySuperscriptXOffset;
        int16_t ySuperscriptYOffset;
        int16_t yStrikeoutSize;
        int16_t yStrikeoutPosition;
        int16_t sFamilyClass;
        uint8_t	panose[10];
        uint32_t ulUnicodeRange1;
        uint32_t ulUnicodeRange2;
        uint32_t ulUnicodeRange3;
        uint32_t ulUnicodeRange4;
        char	achVendID[4];
        uint16_t fsSelection;
        uint16_t usFirstCharIndex;
        uint16_t usLastCharIndex;
        int16_t sTypoAscender;
        int16_t sTypoDescender;
        int16_t sTypoLineGap;
        uint16_t usWinAscent;
        uint16_t usWinDescent;
        uint32_t ulCodePageRange1;
        uint32_t ulCodePageRange2;
    }TT_OS2_RECORD_1;

    typedef struct _tagTT_OS2_RECORD_0 {
        uint16_t version = 0;
        int16_t xAvgCharWidth;
        uint16_t usWeightClass;
        uint16_t usWidthClass;
        uint16_t fsType;
        int16_t ySubscriptXSize;
        int16_t ySubscriptYSize;
        int16_t ySubscriptXOffset;
        int16_t ySubscriptYOffset;
        int16_t ySuperscriptXSize;
        int16_t ySuperscriptYSize;
        int16_t ySuperscriptXOffset;
        int16_t ySuperscriptYOffset;
        int16_t yStrikeoutSize;
        int16_t yStrikeoutPosition;
        int16_t sFamilyClass;
        uint8_t	panose[10];
        uint32_t ulUnicodeRange1;
        uint32_t ulUnicodeRange2;
        uint32_t ulUnicodeRange3;
        uint32_t ulUnicodeRange4;
        char	achVendID[4];
        uint16_t fsSelection;
        uint16_t usFirstCharIndex;
        uint16_t usLastCharIndex;
        int16_t sTypoAscender;
        int16_t sTypoDescender;
        int16_t sTypoLineGap;
        uint16_t usWinAscent;
        uint16_t usWinDescent;
    }TT_OS2_RECORD_0;

    class FontFormatNotSupportedException:public std::exception {
    public:
        FontFormatNotSupportedException(const char* message = nullptr):std::exception(message) {}
    };

    class TtfFile {
    private:
        const void* data;
        size_t size;

        TT_OFFSET_TABLE ttOffsetTable;

        bool findTable(TT_TABLE_DIRECTORY* tables, size_t numOfTables, const AString& name, TT_TABLE_DIRECTORY& tblDir);

    public:
        void init(const void* data, size_t size);

        String readFontName();

        uint16_t readFontWeight();
        
        bool readFontItalic();
    };
}