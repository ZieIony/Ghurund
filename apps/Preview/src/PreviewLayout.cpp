#include "PreviewLayout.h"

#include "ThemeApplication.h"

namespace Preview {
	void PreviewLayout::onLoaded() {
		__super::onLoaded();

		binding.init(*this);

		binding.ThemeCheckBox.checkedChanged += [this](CheckBox& checkBox, bool checked) {
			themeChanged(checked ? ThemeType::DARK : ThemeType::LIGHT);
			return true;
			};
		binding.EnabledCheckBox.checkedChanged += [this](CheckBox& checkBox, bool checked) {
			binding.Container.Enabled = checked;
			binding.Container.repaint();
			return true;
			};

		binding.Color1.clicked += [this](Button& button, const MouseClickedEventArgs& args) {
			return onColorClicked(args, 0xffd32f2f);
			};
		binding.Color2.clicked += [this](Button& button, const MouseClickedEventArgs& args) {
			return onColorClicked(args, 0xff1976d2);
			};
		binding.Color3.clicked += [this](Button& button, const MouseClickedEventArgs& args) {
			return onColorClicked(args, 0xffffa000);
			};
		binding.Color4.clicked += [this](Button& button, const MouseClickedEventArgs& args) {
			return onColorClicked(args, 0xff388e3c);
			};

		WindowsTheme::init();
		binding.Theme.Color = ColorValue(WindowsTheme::getAccentColor());
		binding.ColorTheme.clicked += [this](Button& button, const MouseClickedEventArgs& args) {
			return onColorClicked(args, WindowsTheme::getAccentColor());
			};
	}
}
