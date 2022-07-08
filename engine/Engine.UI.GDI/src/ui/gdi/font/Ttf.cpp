#include "ghuigdipch.h"
#include "Ttf.h"

#include "core/string/TextConversionUtils.h"

namespace Ghurund::Core {
    bool TtfFile::findTable(TT_TABLE_DIRECTORY* tables, size_t numOfTables, const AString& name, TT_TABLE_DIRECTORY& tblDir) {
        for (size_t i = 0; i < numOfTables; i++) {
            tblDir = *tables;

            //table's tag cannot exceed 4 characters
            AString tableName = AString(tblDir.szTag, 4);
            if (tableName == name) {
                //we found our table. Rearrange order and quit the loop
                tblDir.uLength = SWAPLONG(tblDir.uLength);
                tblDir.uOffset = SWAPLONG(tblDir.uOffset);
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
        ttOffsetTable = *(TT_OFFSET_TABLE*)data;

        //remember to rearrange bytes in the field you gonna use
        ttOffsetTable.uNumOfTables = SWAPWORD(ttOffsetTable.uNumOfTables);
        ttOffsetTable.uMajorVersion = SWAPWORD(ttOffsetTable.uMajorVersion);
        ttOffsetTable.uMinorVersion = SWAPWORD(ttOffsetTable.uMinorVersion);

        //check is this is a true type font and the version is 1.0
        if (ttOffsetTable.uMajorVersion != 1 || ttOffsetTable.uMinorVersion != 0)
            throw FontFormatNotSupportedException();
    }

    String TtfFile::readFontName() {
        TT_TABLE_DIRECTORY tblDir;
        const uint8_t* pointer = (const uint8_t*)data + sizeof(TT_OFFSET_TABLE);
        bool found = findTable((TT_TABLE_DIRECTORY*)pointer, ttOffsetTable.uNumOfTables, "name", tblDir);

        if (found) {
            //move to offset we got from Offsets Table
            pointer = (const uint8_t*)data + tblDir.uOffset;
            TT_NAME_TABLE_HEADER ttNTHeader = *(TT_NAME_TABLE_HEADER*)pointer;
            pointer += sizeof(TT_NAME_TABLE_HEADER);

            //again, don't forget to swap bytes!
            ttNTHeader.uNRCount = SWAPWORD(ttNTHeader.uNRCount);
            ttNTHeader.uStorageOffset = SWAPWORD(ttNTHeader.uStorageOffset);
            found = false;

            for (size_t i = 0; i < ttNTHeader.uNRCount; i++) {
                TT_NAME_RECORD ttRecord = *(TT_NAME_RECORD*)pointer;
                pointer += sizeof(TT_NAME_RECORD);
                ttRecord.uNameID = SWAPWORD(ttRecord.uNameID);

                //1 says that this is font name. 0 for example determines copyright info
                if (ttRecord.uNameID == 1) {
                    ttRecord.uStringLength = SWAPWORD(ttRecord.uStringLength);
                    ttRecord.uStringOffset = SWAPWORD(ttRecord.uStringOffset);

                    uint8_t* namePointer = (uint8_t*)data + tblDir.uOffset + ttRecord.uStringOffset + ttNTHeader.uStorageOffset;
                    AString familyName = AString((char*)namePointer, ttRecord.uStringLength);

                    if (familyName.Length > 0)
                        return convertText<char, tchar>(familyName);
                }
            }
        }

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
            version = SWAPWORD(version);
            if (version == 0) {
                TT_OS2_RECORD_0 record = *(TT_OS2_RECORD_0*)pointer;
                return SWAPWORD(record.usWeightClass);
            } else if (version == 1) {
                TT_OS2_RECORD_1 record = *(TT_OS2_RECORD_1*)pointer;
                return SWAPWORD(record.usWeightClass);
            } else if (version == 2 || version == 3 || version == 4) {
                TT_OS2_RECORD_234 record = *(TT_OS2_RECORD_234*)pointer;
                return SWAPWORD(record.usWeightClass);
            } else if (version == 5) {
                TT_OS2_RECORD_5 record = *(TT_OS2_RECORD_5*)pointer;
                return SWAPWORD(record.usWeightClass);
            }
        }

        found = findTable((TT_TABLE_DIRECTORY*)pointer, ttOffsetTable.uNumOfTables, "fvar", tblDir);

        if (found) {
            //move to offset we got from Offsets Table
            pointer = (const uint8_t*)data + tblDir.uOffset;
            TT_FVAR_TABLE_HEADER ttFTHeader = *(TT_FVAR_TABLE_HEADER*)pointer;
            pointer += sizeof(TT_FVAR_TABLE_HEADER);

            //again, don't forget to swap bytes!
            ttFTHeader.axisCount = SWAPWORD(ttFTHeader.axisCount);
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
            version = SWAPWORD(version);
            if (version == 0) {
                TT_OS2_RECORD_0 record = *(TT_OS2_RECORD_0*)pointer;
                return SWAPWORD(record.fsSelection) & 0x1;
            } else if (version == 1) {
                TT_OS2_RECORD_1 record = *(TT_OS2_RECORD_1*)pointer;
                return SWAPWORD(record.fsSelection) & 0x1;
            } else if (version == 2 || version == 3 || version == 4) {
                TT_OS2_RECORD_234 record = *(TT_OS2_RECORD_234*)pointer;
                return SWAPWORD(record.fsSelection) & 0x1;
            } else if (version == 5) {
                TT_OS2_RECORD_5 record = *(TT_OS2_RECORD_5*)pointer;
                return SWAPWORD(record.fsSelection) & 0x1;
            }
        }

        return false;
    }
}