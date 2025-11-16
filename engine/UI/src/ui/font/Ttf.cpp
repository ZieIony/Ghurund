#include "ghuipch.h"
#include "Ttf.h"

namespace Ghurund::UI {
	TT_OFFSET_TABLE TT_OFFSET_TABLE::make(const void* pointer) {
		TT_OFFSET_TABLE table = *(TT_OFFSET_TABLE*)pointer;
		table.uMajorVersion = swap16(table.uMajorVersion);
		table.uMinorVersion = swap16(table.uMinorVersion);
		table.uNumOfTables = swap16(table.uNumOfTables);
		table.uSearchRange = swap16(table.uSearchRange);
		table.uEntrySelector = swap16(table.uEntrySelector);
		table.uRangeShift = swap16(table.uRangeShift);
		return table;
	}
	
	TT_NAME_TABLE_HEADER TT_NAME_TABLE_HEADER::make(const void* pointer) {
		TT_NAME_TABLE_HEADER header = *(TT_NAME_TABLE_HEADER*)pointer;
		header.uFSelector = swap16(header.uFSelector);
		header.uNRCount = swap16(header.uNRCount);
		header.uStorageOffset = swap16(header.uStorageOffset);
		return header;
	}
	
	TT_NAME_RECORD TT_NAME_RECORD::make(const void* pointer) {
		TT_NAME_RECORD record = *(TT_NAME_RECORD*)pointer;
		record.uPlatformID = swap16(record.uPlatformID);
		record.uEncodingID = swap16(record.uEncodingID);
		record.uLanguageID = swap16(record.uLanguageID);
		record.uNameID = swap16(record.uNameID);
		record.uStringLength = swap16(record.uStringLength);
		record.uStringOffset = swap16(record.uStringOffset);
		return record;
	}
}