#include "ghuipch.h"
#include "BaseTheme.h"
#include "FileLayoutProvider.h"

#include "ui/widget/button/Button.h"
#include "ui/widget/button/CheckBox.h"
#include "ui/widget/button/RadioButton.h"
#include "ui/widget/ExpandableContainer.h"
#include "FileTextureProvider.h"

namespace Ghurund::UI {
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

		Ghurund::Core::IntrusivePointer<Ghurund::UI::Font> latoMediumFont = [&]{
			auto latoMediumPathAtlas = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/fonts\\lato_medium.fontatlas");
			if (latoMediumPathAtlas.exists(DirectoryPath(), resourceManager.Libraries)) {
				return IntrusivePointer<Font>(resourceManager.load<Ghurund::UI::Font>(latoMediumPathAtlas, DirectoryPath()));
			} else {
				auto latoMediumPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/fonts\\lato_medium.ttf");
				Ghurund::Core::IntrusivePointer<Ghurund::UI::Font> latoMediumFont(resourceManager.load<Ghurund::UI::Font>(latoMediumPath, DirectoryPath()));
				//resourceManager.save(*latoMediumFont.get(), latoMediumPathAtlas, DirectoryPath(), Font::FORMAT_ATLAS);
				return latoMediumFont;
			}
		}();
		//auto latoLightPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/fonts\\lato_light.ttf");
		//Ghurund::Core::IntrusivePointer<Ghurund::UI::Font> latoLightFont(resourceManager.load<Ghurund::UI::Font>(latoLightPath, DirectoryPath()));

		auto buttonFont = Ghurund::Core::makeIntrusive<TextFormat>(latoMediumFont.get(), 10.0f, FW_MEDIUM);    // TODO: should medium font use FW_MEDIUM or FW_REGULAR?
		TextFormats.put(Theme::TEXTFORMAT_BUTTON, buttonFont);

		//auto listHeaderFont = Ghurund::Core::makeIntrusive<TextFormat>(latoLightFont.get(), 14.0f, FW_LIGHT);
		//TextFormats.put(Theme::TEXTFORMAT_LIST_HEADER, listHeaderFont);

		auto textPrimaryFont = Ghurund::Core::makeIntrusive<TextFormat>(latoMediumFont.get(), 11.0f, FW_REGULAR);
		TextFormats.put(Theme::TEXTFORMAT_TEXT_PRIMARY, textPrimaryFont);

		auto textSecondaryFont = Ghurund::Core::makeIntrusive<TextFormat>(latoMediumFont.get(), 50.0f, FW_REGULAR);
		TextFormats.put(Theme::TEXTFORMAT_TEXT_SECONDARY, textSecondaryFont);

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
	}
}
