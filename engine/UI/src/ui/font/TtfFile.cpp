#include "ghuipch.h"
#include "TtfFile.h"

namespace Ghurund::UI {
	bool TtfFile::findTable(TT_TABLE_DIRECTORY* tables, size_t numOfTables, const AString& name, TT_TABLE_DIRECTORY& tblDir) {
		for (size_t i = 0; i < numOfTables; i++) {
			tblDir = *tables;

			//table's tag cannot exceed 4 characters
			AString tableName = AString(tblDir.szTag, 4);
			if (tableName == name) {
				//we found our table. Rearrange order and quit the loop
				tblDir.uLength = swap32(tblDir.uLength);
				tblDir.uOffset = swap32(tblDir.uOffset);
				return true;
			}

			tables++;
		}

		return false;
	}

	void TtfFile::init(const void* data, size_t size) {
		this->data = data;
		this->size = size;

		// see: https://www.codeproject.com/Articles/2293/Retrieving-Font-Name-from-TTF-File
		//define and read file header
		ttOffsetTable = TT_OFFSET_TABLE::make(data);

		//check is this is a true type font and the version is 1.0
		if (ttOffsetTable.uMajorVersion != 1 || ttOffsetTable.uMinorVersion != 0)
			throw FontFormatNotSupportedException();

		readFontFamilyName();
	}

	void TtfFile::readFontFamilyName() {
		TT_TABLE_DIRECTORY tblDir;
		const uint8_t* pointer = (const uint8_t*)data + sizeof(TT_OFFSET_TABLE);
		bool found = findTable((TT_TABLE_DIRECTORY*)pointer, ttOffsetTable.uNumOfTables, "name", tblDir);

		if (found) {
			//move to offset we got from Offsets Table
			pointer = (const uint8_t*)data + tblDir.uOffset;
			TT_NAME_TABLE_HEADER ttNTHeader = TT_NAME_TABLE_HEADER::make(pointer);
			pointer += sizeof(TT_NAME_TABLE_HEADER);

			found = false;

			for (size_t i = 0; i < ttNTHeader.uNRCount; i++) {
				TT_NAME_RECORD ttRecord = TT_NAME_RECORD::make(pointer);
				pointer += sizeof(TT_NAME_RECORD);

				if (ttRecord.uNameID == (uint8_t)NameId::FAMILY) {
					uint8_t* namePointer = (uint8_t*)data + tblDir.uOffset + ttRecord.uStringOffset + ttNTHeader.uStorageOffset;
					this->familyName = readString(namePointer, ttRecord.uStringLength);
				} else if (ttRecord.uNameID == (uint8_t)NameId::SUBFAMILY) {
					uint8_t* namePointer = (uint8_t*)data + tblDir.uOffset + ttRecord.uStringOffset + ttNTHeader.uStorageOffset;
					this->subfamilyName = readString(namePointer, ttRecord.uStringLength);
				} else if (ttRecord.uNameID == (uint8_t)NameId::FULL_NAME) {
					uint8_t* namePointer = (uint8_t*)data + tblDir.uOffset + ttRecord.uStringOffset + ttNTHeader.uStorageOffset;
					this->fullName = readString(namePointer, ttRecord.uStringLength);
				}
			}
		}
	}

	String TtfFile::readString(uint8_t* data, size_t length) {
		AString str = [&] {
			if (data[0] == 0) {
				AString familyName(length / 2);
				for (size_t i = 0; i < length / 2; i++) {
					familyName.add(data[i * 2 + 1]);
				}
				return familyName;
			} else {
				return AString((char*)data, length);
			}
		}();
		if (strlen((char*)str.Data) > 0)
			return convertText<char, tchar>(str);
		return String();
	}

	uint16_t TtfFile::readFontWeight() {
		TT_TABLE_DIRECTORY tblDir;
		const uint8_t* pointer = (const uint8_t*)data + sizeof(TT_OFFSET_TABLE);
		bool found = findTable((TT_TABLE_DIRECTORY*)pointer, ttOffsetTable.uNumOfTables, "OS/2", tblDir);
		if (found) {
			//move to offset we got from Offsets Table
			pointer = (const uint8_t*)data + tblDir.uOffset;
			uint16_t version = *(uint16_t*)pointer;
			version = swap16(version);
			if (version == 0) {
				TT_OS2_RECORD_0 record = *(TT_OS2_RECORD_0*)pointer;
				return swap16(record.usWeightClass);
			} else if (version == 1) {
				TT_OS2_RECORD_1 record = *(TT_OS2_RECORD_1*)pointer;
				return swap16(record.usWeightClass);
			} else if (version == 2 || version == 3 || version == 4) {
				TT_OS2_RECORD_234 record = *(TT_OS2_RECORD_234*)pointer;
				return swap16(record.usWeightClass);
			} else if (version == 5) {
				TT_OS2_RECORD_5 record = *(TT_OS2_RECORD_5*)pointer;
				return swap16(record.usWeightClass);
			}
		}

		found = findTable((TT_TABLE_DIRECTORY*)pointer, ttOffsetTable.uNumOfTables, "fvar", tblDir);

		if (found) {
			//move to offset we got from Offsets Table
			pointer = (const uint8_t*)data + tblDir.uOffset;
			TT_FVAR_TABLE_HEADER ttFTHeader = *(TT_FVAR_TABLE_HEADER*)pointer;
			pointer += sizeof(TT_FVAR_TABLE_HEADER);

			//again, don't forget to swap bytes!
			ttFTHeader.axisCount = swap16(ttFTHeader.axisCount);
			found = false;

			for (size_t i = 0; i < ttFTHeader.axisCount; i++) {
				TT_FVAR_RECORD ttRecord = *(TT_FVAR_RECORD*)pointer;
				pointer += sizeof(TT_FVAR_RECORD);

				if (AString(ttRecord.axisTag, 4) == "wght")
					return ttRecord.defaultValue.value;
			}
		}

		return 400;
	}

	bool TtfFile::readFontItalic() {
		TT_TABLE_DIRECTORY tblDir;
		const uint8_t* pointer = (const uint8_t*)data + sizeof(TT_OFFSET_TABLE);
		bool found = findTable((TT_TABLE_DIRECTORY*)pointer, ttOffsetTable.uNumOfTables, "OS/2", tblDir);
		if (found) {
			//move to offset we got from Offsets Table
			pointer = (const uint8_t*)data + tblDir.uOffset;
			uint16_t version = *(uint16_t*)pointer;
			version = swap16(version);
			if (version == 0) {
				TT_OS2_RECORD_0 record = *(TT_OS2_RECORD_0*)pointer;
				return swap16(record.fsSelection) & 0x1;
			} else if (version == 1) {
				TT_OS2_RECORD_1 record = *(TT_OS2_RECORD_1*)pointer;
				return swap16(record.fsSelection) & 0x1;
			} else if (version == 2 || version == 3 || version == 4) {
				TT_OS2_RECORD_234 record = *(TT_OS2_RECORD_234*)pointer;
				return swap16(record.fsSelection) & 0x1;
			} else if (version == 5) {
				TT_OS2_RECORD_5 record = *(TT_OS2_RECORD_5*)pointer;
				return swap16(record.fsSelection) & 0x1;
			}
		}

		return false;
	}
}