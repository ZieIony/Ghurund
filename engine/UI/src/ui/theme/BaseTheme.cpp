#include "ghuipch.h"
#include "BaseTheme.h"
#include "FileLayoutProvider.h"
#include "FileDrawableProvider.h"

#include "ui/widget/button/Button.h"
#include "ui/widget/button/CheckBox.h"
#include "ui/widget/button/RadioButton.h"
#include "ui/widget/ExpandableContainer.h"

namespace Ghurund::UI {
	BaseTheme::BaseTheme(
		NotNull<Ghurund::Core::ResourceManager> resourceManager,
		NotNull<Ghurund::UI::IDrawableFactory> drawableFactory
	):Theme(), resourceManager(&resourceManager) {
		auto buttonLayoutPath = ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/layouts/ButtonDefaultLayout.xml");
		Layouts.put(LayoutKey(Button::GET_TYPE().Name), std::make_shared<FileLayoutProvider>(resourceManager, buttonLayoutPath));
		auto checkBoxLayoutPath = ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/layouts/CheckBoxLayout.xml");
		Layouts.put(LayoutKey(CheckBox::GET_TYPE().Name), std::make_shared<FileLayoutProvider>(resourceManager, checkBoxLayoutPath));
		auto radioLayoutPath = ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/layouts/RadioButtonLayout.xml");
		Layouts.put(LayoutKey(RadioButton::GET_TYPE().Name), std::make_shared<FileLayoutProvider>(resourceManager, radioLayoutPath));
		auto expandableContainerLayoutPath = ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/layouts/ExpandableContainer.xml");
		Layouts.put(LayoutKey(ExpandableContainer::GET_TYPE().Name), std::make_shared<FileLayoutProvider>(resourceManager, expandableContainerLayoutPath));

		Ghurund::Core::IntrusivePointer<Ghurund::UI::Font> latoMediumFont = [&]{
			auto latoMediumPathAtlas = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/fonts\\lato_medium.fontatlas");
			if (latoMediumPathAtlas.exists(DirectoryPath(), resourceManager->Libraries)) {
				return IntrusivePointer<Font>(resourceManager->load<Ghurund::UI::Font>(latoMediumPathAtlas, DirectoryPath()));
			} else {
				auto latoMediumPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/fonts\\lato_medium.ttf");
				Ghurund::Core::IntrusivePointer<Ghurund::UI::Font> latoMediumFont(resourceManager->load<Ghurund::UI::Font>(latoMediumPath, DirectoryPath()));
				//resourceManager.save(*latoMediumFont.get(), latoMediumPathAtlas, DirectoryPath(), Font::FORMAT_ATLAS);
				return latoMediumFont;
			}
		}();
		auto latoLightPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/fonts\\lato_light.ttf");
		Ghurund::Core::IntrusivePointer<Ghurund::UI::Font> latoLightFont(resourceManager->load<Ghurund::UI::Font>(latoLightPath, DirectoryPath()));

		auto buttonFont = Ghurund::Core::makeIntrusive<TextFormat>(latoMediumFont.get(), 10.0f, FW_MEDIUM);    // TODO: should medium font use FW_MEDIUM or FW_REGULAR?
		TextFormats.put(Theme::TEXTFORMAT_BUTTON, buttonFont);

		auto listHeaderFont = Ghurund::Core::makeIntrusive<TextFormat>(latoLightFont.get(), 14.0f, FW_LIGHT);
		TextFormats.put(Theme::TEXTFORMAT_LIST_HEADER, listHeaderFont);

		auto textPrimaryFont = Ghurund::Core::makeIntrusive<TextFormat>(latoMediumFont.get(), 11.0f, FW_REGULAR);
		TextFormats.put(Theme::TEXTFORMAT_TEXT_PRIMARY, textPrimaryFont);

		auto textSecondaryFont = Ghurund::Core::makeIntrusive<TextFormat>(latoMediumFont.get(), 50.0f, FW_REGULAR);
		TextFormats.put(Theme::TEXTFORMAT_TEXT_SECONDARY, textSecondaryFont);

		auto checkboxCheckedPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/icons\\checkbox checked 18.png");
		Drawables.put(Theme::DRAWABLE_CHECKBOX_CHECKED, std::make_shared<FileDrawableProvider>(drawableFactory, checkboxCheckedPath));
		auto checkBoxUncheckedPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/icons\\checkbox unchecked 18.png");
		Drawables.put(Theme::DRAWABLE_CHECKBOX_UNCHECKED, std::make_shared<FileDrawableProvider>(drawableFactory, checkBoxUncheckedPath));
		auto radioCheckedPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/icons\\radiobutton checked 18.png");
		Drawables.put(Theme::DRAWABLE_RADIOBUTTON_CHECKED, std::make_shared<FileDrawableProvider>(drawableFactory, radioCheckedPath));
		auto radioUncheckedPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/icons\\radiobutton unchecked 18.png");
		Drawables.put(Theme::DRAWABLE_RADIOBUTTON_UNCHECKED, std::make_shared<FileDrawableProvider>(drawableFactory, radioUncheckedPath));
		auto arrowUpPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/icons\\arrow up 18.png");
		Drawables.put(Theme::DRAWABLE_ARROWUP, std::make_shared<FileDrawableProvider>(drawableFactory, arrowUpPath));
		auto arrowDownPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/icons\\arrow down 18.png");
		Drawables.put(Theme::DRAWABLE_ARROWDOWN, std::make_shared<FileDrawableProvider>(drawableFactory, arrowDownPath));
		auto arrowRightPath = Ghurund::Core::ResourcePath(ResourceManager::ENGINE_LIB_NAME, L"/icons\\arrow right 18.png");
		Drawables.put(Theme::DRAWABLE_ARROWRIGHT, std::make_shared<FileDrawableProvider>(drawableFactory, arrowRightPath));
	}
}
