#pragma once

#include <core/string/String.h>

#define SWAPWORD(x) MAKEWORD(HIBYTE(x), LOBYTE(x))
#define SWAPLONG(x) MAKELONG(SWAPWORD(HIWORD(x)), SWAPWORD(LOWORD(x)))

inline uint16_t make16(uint8_t a, uint8_t b) {
	return (a << 8) | b;
}

inline uint32_t make32(uint16_t a, uint16_t b) {
	return (b << 16) | a;
}

inline uint16_t low16(uint32_t a) {
	return a & 0xffff;
}

inline uint16_t hi16(uint32_t a) {
	return (a >> 16) & 0xffff;
}

inline uint8_t low8(uint16_t a) {
	return a & 0xff;
}

inline uint8_t hi8(uint16_t a) {
	return (a >> 8) & 0xff;
}

inline uint16_t swap16(uint16_t a) {
	return make16(low8(a), hi8(a));
}

inline uint32_t swap32(uint32_t a) {
	return make32(low16(a), hi16(a));
}

namespace Ghurund::Core {

	//This is TTF file header
	struct TT_OFFSET_TABLE {
		uint16_t uMajorVersion;
		uint16_t uMinorVersion;
		uint16_t uNumOfTables;
		uint16_t uSearchRange;
		uint16_t uEntrySelector;
		uint16_t uRangeShift;

		static TT_OFFSET_TABLE make(const void* pointer) {
			TT_OFFSET_TABLE table = *(TT_OFFSET_TABLE*)pointer;
			table.uMajorVersion = swap16(table.uMajorVersion);
			table.uMinorVersion = swap16(table.uMinorVersion);
			table.uNumOfTables = swap16(table.uNumOfTables);
			table.uSearchRange = swap16(table.uSearchRange);
			table.uEntrySelector = swap16(table.uEntrySelector);
			table.uRangeShift = swap16(table.uRangeShift);
			return table;
		}
	};

	//Tables in TTF file and there placement and name (tag)
	struct TT_TABLE_DIRECTORY {
		char szTag[4]; //table name
		ULONG uCheckSum; //Check sum
		ULONG uOffset; //Offset from beginning of file
		ULONG uLength; //length of the table in bytes

		static TT_TABLE_DIRECTORY make(const void* pointer) {
			TT_TABLE_DIRECTORY directory = *(TT_TABLE_DIRECTORY*)pointer;
			return directory;
		}
	};

	//Header of names table
	struct TT_NAME_TABLE_HEADER {
		uint16_t uFSelector; //format selector. Always 0
		uint16_t uNRCount; //Name Records count
		uint16_t uStorageOffset; //Offset for strings storage, 
		//from start of the table

		static TT_NAME_TABLE_HEADER make(const void* pointer) {
			TT_NAME_TABLE_HEADER header = *(TT_NAME_TABLE_HEADER*)pointer;
			header.uFSelector = swap16(header.uFSelector);
			header.uNRCount = swap16(header.uNRCount);
			header.uStorageOffset = swap16(header.uStorageOffset);
			return header;
		}
	};

	//Record in names table
	struct TT_NAME_RECORD {
		uint16_t uPlatformID;
		uint16_t uEncodingID;
		uint16_t uLanguageID;
		uint16_t uNameID;
		uint16_t uStringLength;
		uint16_t uStringOffset; //from start of storage area

		static TT_NAME_RECORD make(const void* pointer) {
			TT_NAME_RECORD record = *(TT_NAME_RECORD*)pointer;
			record.uPlatformID = swap16(record.uPlatformID);
			record.uEncodingID = swap16(record.uEncodingID);
			record.uLanguageID = swap16(record.uLanguageID);
			record.uNameID = swap16(record.uNameID);
			record.uStringLength = swap16(record.uStringLength);
			record.uStringOffset = swap16(record.uStringOffset);
			return record;
		}
	};

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
		enum class NameId {
			COPYRIGHT = 0,
			FAMILY = 1,
			SUBFAMILY = 2,
			UNIQUE_SUBFAMILY_ID = 3,
			FULL_NAME = 4,
			VERSION = 5
		};

		const void* data;
		size_t size;

		TT_OFFSET_TABLE ttOffsetTable;

		bool findTable(TT_TABLE_DIRECTORY* tables, size_t numOfTables, const AString& name, TT_TABLE_DIRECTORY& tblDir);

		String readString(uint8_t* data, size_t length);

	public:
		String familyName, subfamilyName, fullName;

		void init(const void* data, size_t size);

		void readFontFamilyName();

		uint16_t readFontWeight();

		bool readFontItalic();
	};
}