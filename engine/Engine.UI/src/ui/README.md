### Ghurund.UI

Ghurund.UI is an event-based, retained-mode UI rendered with Direct2D. Controls, layouts and widgets, are organized in a tree hierarchy. Ghurund.UI handles focus, text editing, mouse and keyboard interaction, and many other usual things you would expect a UI library to handle.

##### Controls and hierarchy

Ghurund.UI provides very simple controls - each of them does one thing and that's it. `ColorView` only draws a colored rectangle, `Space` only provides a spacing tool for layouts, and `PaddingContainer` only adds a padding to its child control. This has a couple of benefits:

 - Controls can be composed freely without thinking much about the performance cost and flattening the hierarchy.
 - Making custom controls is really simple as there are very few things that need to be implemented.
 - Small building blocks can be styled or replaced if they don't work as intended.

Ghurund.UI provides a couple of different basic building blocks:

 - `Control` - the base for all other controls, layouts and widgets.
 - `ControlContainer` - the base for containers that can hold only one direct child.
 - `ControlGroup` - the base for layouts. Can use layout managers to measure and layout its children.
 - `Widget` - the base for widgets with layouts.
 - `ContentWidget` - the base for widgets that can hold a content child.

##### Theming and styling

Ghurund.UI has a built-in theming and styling system. Themes are very simple classes with value containers. By default there are two themes (dark and light) providing styles, text formats, images and colors. If you wish, you can add your own values and value types there.

Styles are just C++ pieces of code attached to a control that update the control's look to match its state. State handlers can do anything inside and react to any state changes specific to the control.

The following code shows a state handler for TextBlock:

```C++
struct TextBlockButtonStyle: public Style {
	virtual void onStateChanged(Control& control) const override {
		TextBlock& textBlock = (TextBlock&)control;
		if (control.Enabled) {
			textBlock.TextColor = ColorRef(Theme::COLOR_PRIMARY_ONBACKGROUND);
		} else {
			textBlock.TextColor = ColorRef(Theme::COLOR_DISABLED_ONBACKGROUND);
		}
	}
};
```

There's one more thing that can be used to style widgets - layouts. Widgets only define logic and contracts that need to be fulfilled for them to work. The programmer is free to replace the underlying layout with a different one as long as it meets the requirements of the contract.

For example a button, in general, is a clickable area on the screen. The details are not important here - the only requirement is that the layout contains a clickable control. In this way each widget can be customized to a great extent:

<img src="../../../images/buttons.png"/>

Themes, styles and layouts can be replaced at runtime and the changes are propagated immediately.

##### XML

Ghurund.UI controls can be loaded from .xml files using `LayoutLoader`. Layout files provide a way to quickly define static layouts of widgets and screens used in a project. The engine provides a basic xsd schema that can be used to validate xml format and provide code completion. Xml layouts can refer to files, and to theme values using `file://` and `theme://` prefixes.

The following code shows an xml layout of a check box:

```xml
<?xml version="1.0" encoding="utf-8"?>
<layout xmlns="https://github.com/Zielony/Ghurund/Engine/UISchema.xsd">
	<SelectableView name="selectable" preferredSize="wrap, wrap">
		<StackLayout>
			<FocusIndicator style="theme://style/colorView_accent"/>
			<LinearLayout alignment="center, center" orientation="horizontal">
				<ImageView name="image" image="theme://image/checkBox_checked"
							imageTint="theme://color/accent"/>
				<Space preferredSize="4,4"/>
				<ControlContainer preferredSize="wrap, wrap" name="content"/>
			</LinearLayout>
		</StackLayout>
	</SelectableView>
</layout>
```

##### Hot reload and layout editing

Like everything in Ghurund, UI can be reloaded without restarting the application. Ghurund.UI doesn't provide a dedicated UI editor, but a simple `Preview` project with hot reloading enabled. You can use it and any xml editor to quickly iterate UI changes and see them rendered by the engine.