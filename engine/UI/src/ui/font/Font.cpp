#include "ghuipch.h"
#include "Font.h"

#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/TypeBuilder.h"

#include "TtfFile.h"

namespace Ghurund::UI {

	const Ghurund::Core::Type& Font::GET_TYPE() {
		static auto PROPERTY_FAMILYNAME = Property<Font, const WString&>("FamilyName", &getFamilyName);

		static const Ghurund::Core::Type TYPE = TypeBuilder<Font>()
			.withProperty(PROPERTY_FAMILYNAME)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void Font::init(const void* data, size_t size) {
		TtfFile file = {};
		file.init(data, size);
		familyName = file.familyName;
		weight = file.readFontWeight();
		italic = file.readFontItalic();
		DWORD numFonts = {};
		uninit();
		handle = AddFontMemResourceEx((void*)data, (DWORD)size, 0, &numFonts);
	}

	void Font::uninit() {
		if (handle != INVALID_HANDLE_VALUE) {
			RemoveFontMemResourceEx(handle);
			handle = INVALID_HANDLE_VALUE;
		}
	}
}