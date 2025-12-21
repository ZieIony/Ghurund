#include "ghuipch.h"
#include "BaseTheme.h"
#include "FileLayoutProvider.h"

#include "ui/widget/button/Button.h"
#include "ui/widget/button/CheckBox.h"
#include "ui/widget/button/RadioButton.h"
#include "ui/widget/ExpandableContainer.h"
#include "FileTextureProvider.h"
#include "FileMaterialProvider.h"

#include <format>

namespace Ghurund::UI {
	IntrusivePointer<TextStyle> BaseTheme::makeTextStyle(const wchar_t* style, float size) {
		IntrusivePointer<TextStyle> textStyle;
		auto textStylePathStr = std::format(L"resources/textStyles/lato_{}_{}.bin", style, (uint16_t)size);
		auto textStylePath = ResourcePath(FilePath(textStylePathStr.c_str()));
		if (textStylePath.exists(DirectoryPath(), resourceManager.Libraries)) {
			textStyle.set(resourceManager.load<TextStyle>(textStylePath, DirectoryPath(), TextStyle::FORMAT_BIN));
		} else {
			auto fontPathStr = std::format(L"resources/fonts/lato_{}.ttf", style);
			auto font = IntrusivePointer<Font>(resourceManager.load<Font>(ResourcePath(FilePath(fontPathStr.c_str()))));
			textStyle.set(ghnew TextStyle());
			textStyle->init(font.ref(), size);
			auto atlasPathStr = std::format(L"resources/textStyles/lato_{}_{}.png", style, (uint16_t)size);
			auto atlasPath = ResourcePath(FilePath(atlasPathStr.c_str()));
			resourceManager.save(*textStyle->Atlas->Image, atlasPath, DirectoryPath(), Image::FORMAT_PNG);
			resourceManager.save(textStyle.ref(), textStylePath, DirectoryPath(), TextStyle::FORMAT_BIN);
		}
		textStyle->addReference();
		return textStyle;
	};

	BaseTheme::BaseTheme(
		Ghurund::Core::ResourceManager& resourceManager,
		ITextureFactory& textureFactory
	):Theme(), resourceManager(resourceManager) {
		auto buttonLayoutPath = ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/layouts/ButtonDefaultLayout.xml");
		Layouts.put(LayoutKey(Button::GET_TYPE().Name), makeShared<FileLayoutProvider>(resourceManager, buttonLayoutPath));
		auto checkBoxLayoutPath = ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/layouts/CheckBoxLayout.xml");
		Layouts.put(LayoutKey(CheckBox::GET_TYPE().Name), makeShared<FileLayoutProvider>(resourceManager, checkBoxLayoutPath));
		auto radioLayoutPath = ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/layouts/RadioButtonLayout.xml");
		Layouts.put(LayoutKey(RadioButton::GET_TYPE().Name), makeShared<FileLayoutProvider>(resourceManager, radioLayoutPath));
		auto expandableContainerLayoutPath = ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/layouts/ExpandableContainer.xml");
		Layouts.put(LayoutKey(ExpandableContainer::GET_TYPE().Name), makeShared<FileLayoutProvider>(resourceManager, expandableContainerLayoutPath));

		TextStyles.put(Theme::TEXT_STYLE_BUTTON, makeTextStyle(L"medium", 12.0f));
		TextStyles.put(Theme::TEXT_STYLE_LIST_HEADER, makeTextStyle(L"light", 14.0f));
		TextStyles.put(Theme::TEXT_STYLE_TEXT_PRIMARY, makeTextStyle(L"regular", 12.0f));
		TextStyles.put(Theme::TEXT_STYLE_TEXT_SECONDARY, makeTextStyle(L"regular", 12.0f));

		auto checkboxCheckedPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/icons\\checkbox checked 18.png");
		Textures.put(Theme::TEXTURE_CHECKBOX_CHECKED, makeShared<FileTextureProvider>(resourceManager, textureFactory, checkboxCheckedPath));
		auto checkBoxUncheckedPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/icons\\checkbox unchecked 18.png");
		Textures.put(Theme::TEXTURE_CHECKBOX_UNCHECKED, makeShared<FileTextureProvider>(resourceManager, textureFactory, checkBoxUncheckedPath));
		auto radioCheckedPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/icons\\radiobutton checked 18.png");
		Textures.put(Theme::TEXTURE_RADIOBUTTON_CHECKED, makeShared<FileTextureProvider>(resourceManager, textureFactory, radioCheckedPath));
		auto radioUncheckedPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/icons\\radiobutton unchecked 18.png");
		Textures.put(Theme::TEXTURE_RADIOBUTTON_UNCHECKED, makeShared<FileTextureProvider>(resourceManager, textureFactory, radioUncheckedPath));
		auto arrowUpPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/icons\\arrow up 18.png");
		Textures.put(Theme::TEXTURE_ARROWUP, makeShared<FileTextureProvider>(resourceManager, textureFactory, arrowUpPath));
		auto arrowDownPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/icons\\arrow down 18.png");
		Textures.put(Theme::TEXTURE_ARROWDOWN, makeShared<FileTextureProvider>(resourceManager, textureFactory, arrowDownPath));
		auto arrowRightPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/icons\\arrow right 18.png");
		Textures.put(Theme::TEXTURE_ARROWRIGHT, makeShared<FileTextureProvider>(resourceManager, textureFactory, arrowRightPath));

		auto materialTextPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/materials/directx/ui/text.xml");
		Materials.put(Theme::MATERIAL_TEXT, makeShared<FileMaterialProvider>(resourceManager, materialTextPath));
	}
}
