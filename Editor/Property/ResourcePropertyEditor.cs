using Ghurund.Controls;
using Ghurund.Controls.PropertyGrid;
using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

namespace Ghurund.Editor.Property {
    public class ResourcePropertyEditor: IPropertyEditor {
        public FrameworkElement MakeControl(Value property) {
            DockPanel dockPanel = new DockPanel();

            IconButton button = new IconButton();
            button.Icon = BitmapFrame.Create(new Uri("pack://application:,,,/Resources/addNew32.png"));
            button.SetResourceReference(FrameworkElement.StyleProperty, "IconButton_Small");
            button.Click += (object sender, RoutedEventArgs e) => {
                button.RaiseEvent(new RoutedValueEditedEventEventArgs(property, PropertyGrid.ValueEditedEvent));
            };
            DockPanel.SetDock(button, Dock.Left);
            dockPanel.Children.Add(button);

            ComboBox comboBox = new ComboBox();
            object val = property.Getter();
            if (val != null)
                comboBox.Items.Add(val);
            comboBox.SelectedItem = property.Getter();
            comboBox.SelectionChanged += (object sender, SelectionChangedEventArgs e) => {
                property.Setter(comboBox.SelectedItem);
            };
            dockPanel.Children.Add(comboBox);

            return dockPanel;
        }
    }

}
