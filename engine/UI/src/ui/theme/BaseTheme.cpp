#include "ghuipch.h"
#include "BaseTheme.h"
#include "FileLayoutProvider.h"

#include "FileTextureProvider.h"
#include "FileMaterialProvider.h"

#include "core/io/File.h"
#include "ui/widget/button/Button.h"
#include "ui/widget/button/CheckBox.h"
#include "ui/widget/button/RadioButton.h"
#include "ui/widget/ExpandableContainer.h"

#include <format>

namespace Ghurund::UI {
	IntrusivePointer<TextStyle> BaseTheme::makeTextStyle(const wchar_t* style, float size) {
		IntrusivePointer<TextStyle> textStyle;
		auto textStylePathStr = std::format(L"resources/textStyles/lato_{}_{}.bin", style, (uint16_t)size);
		auto textStylePath = FilePath(textStylePathStr.c_str());
		if (File(textStylePath).exists()) {
			textStyle.set(resourceManager.load<TextStyle>(textStylePath, DirectoryPath(), TextStyle::FORMAT_BIN));
		} else {
			auto fontPathStr = std::format(L"resources/fonts/lato_{}.ttf", style);
			auto font = IntrusivePointer<Font>(resourceManager.load<Font>(FilePath(fontPathStr.c_str())));
			textStyle.set(ghnew TextStyle());
			textStyle->init(font.ref(), size);
			resourceManager.save(textStyle.ref(), textStylePath, DirectoryPath(), TextStyle::FORMAT_BIN);
		}
		return textStyle;
	};

	BaseTheme::BaseTheme(
		Ghurund::Core::ResourceManager& resourceManager,
		ITextureFactory& textureFactory
	):Theme(), resourceManager(resourceManager) {
		auto buttonLayoutPath = ResourceManager::ENGINE_LIB / FilePath(L"/layouts/ButtonDefaultLayout.xml");
		Layouts.put(LayoutKey(Button::GET_TYPE().Name), makeShared<FileLayoutProvider>(resourceManager, buttonLayoutPath));
		auto checkBoxLayoutPath = ResourceManager::ENGINE_LIB / FilePath(L"/layouts/CheckBoxLayout.xml");
		Layouts.put(LayoutKey(CheckBox::GET_TYPE().Name), makeShared<FileLayoutProvider>(resourceManager, checkBoxLayoutPath));
		auto radioLayoutPath = ResourceManager::ENGINE_LIB / FilePath(L"/layouts/RadioButtonLayout.xml");
		Layouts.put(LayoutKey(RadioButton::GET_TYPE().Name), makeShared<FileLayoutProvider>(resourceManager, radioLayoutPath));
		auto expandableContainerLayoutPath = ResourceManager::ENGINE_LIB / FilePath(L"/layouts/ExpandableContainer.xml");
		Layouts.put(LayoutKey(ExpandableContainer::GET_TYPE().Name), makeShared<FileLayoutProvider>(resourceManager, expandableContainerLayoutPath));

		TextStyles.put(Theme::TEXT_STYLE_BUTTON, makeTextStyle(L"medium", 12.0f));
		TextStyles.put(Theme::TEXT_STYLE_LIST_HEADER, makeTextStyle(L"light", 14.0f));
		TextStyles.put(Theme::TEXT_STYLE_TEXT_PRIMARY, makeTextStyle(L"regular", 12.0f));
		TextStyles.put(Theme::TEXT_STYLE_TEXT_SECONDARY, makeTextStyle(L"regular", 12.0f));

		auto checkboxCheckedPath = ResourceManager::ENGINE_LIB / FilePath(L"/icons\\checkbox checked 18.png");
		Textures.put(Theme::TEXTURE_CHECKBOX_CHECKED, makeShared<FileTextureProvider>(resourceManager, textureFactory, checkboxCheckedPath));
		auto checkBoxUncheckedPath = ResourceManager::ENGINE_LIB / FilePath(L"/icons\\checkbox unchecked 18.png");
		Textures.put(Theme::TEXTURE_CHECKBOX_UNCHECKED, makeShared<FileTextureProvider>(resourceManager, textureFactory, checkBoxUncheckedPath));
		auto radioCheckedPath = ResourceManager::ENGINE_LIB / FilePath(L"/icons\\radiobutton checked 18.png");
		Textures.put(Theme::TEXTURE_RADIOBUTTON_CHECKED, makeShared<FileTextureProvider>(resourceManager, textureFactory, radioCheckedPath));
		auto radioUncheckedPath = ResourceManager::ENGINE_LIB / FilePath(L"/icons\\radiobutton unchecked 18.png");
		Textures.put(Theme::TEXTURE_RADIOBUTTON_UNCHECKED, makeShared<FileTextureProvider>(resourceManager, textureFactory, radioUncheckedPath));
		auto arrowUpPath = ResourceManager::ENGINE_LIB / FilePath(L"/icons\\arrow up 18.png");
		Textures.put(Theme::TEXTURE_ARROWUP, makeShared<FileTextureProvider>(resourceManager, textureFactory, arrowUpPath));
		auto arrowDownPath = ResourceManager::ENGINE_LIB / FilePath(L"/icons\\arrow down 18.png");
		Textures.put(Theme::TEXTURE_ARROWDOWN, makeShared<FileTextureProvider>(resourceManager, textureFactory, arrowDownPath));
		auto arrowRightPath = ResourceManager::ENGINE_LIB / FilePath(L"/icons\\arrow right 18.png");
		Textures.put(Theme::TEXTURE_ARROWRIGHT, makeShared<FileTextureProvider>(resourceManager, textureFactory, arrowRightPath));

		auto materialTextPath = ResourceManager::ENGINE_LIB / FilePath(L"/materials/directx/ui/text.xml");
		Materials.put(Theme::MATERIAL_TEXT, makeShared<FileMaterialProvider>(resourceManager, materialTextPath));
	}
}
