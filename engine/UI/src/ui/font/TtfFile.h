#pragma once

#include <core/string/String.h>
#include "Ttf.h"

namespace Ghurund::UI {
	using namespace Ghurund::Core;

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