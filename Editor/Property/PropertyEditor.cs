using Ghurund.Controls.PropertyGrid;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace Ghurund.Editor.Property {

    public class BooleanPropertyEditor: IPropertyEditor {
        public FrameworkElement MakeControl(Value property) {
            CheckBox checkBox = new CheckBox {
                IsChecked = (bool)property.Getter()
            };
            checkBox.Checked += (object sender, RoutedEventArgs e) => {
                property.Setter(checkBox.IsChecked);
            };
            checkBox.Unchecked += (object sender, RoutedEventArgs e) => {
                property.Setter(checkBox.IsChecked);
            };
            return checkBox;
        }
    }

    public class TextPropertyEditor: IPropertyEditor {
        public FrameworkElement MakeControl(Value property) {
            TextBox textBox = new TextBox {
                Text = property.Getter() as string
            };
            textBox.KeyDown += (object sender, KeyEventArgs e) => {
                if (e.Key == Key.Enter) {
                    property.Setter(textBox.Text);
                }
            };
            textBox.LostFocus += (object sender, RoutedEventArgs e) => {
                property.Setter(textBox.Text);
            };
            return textBox;
        }
    }

    public class EnumPropertyEditor: IPropertyEditor {
        public FrameworkElement MakeControl(Value property) {
            ComboBox comboBox = new ComboBox();
            foreach (var item in property.Type.GetEnumValues())
                comboBox.Items.Add(item);
            comboBox.SelectedItem = property.Getter();
            comboBox.SelectionChanged += (object sender, SelectionChangedEventArgs e) => {
                property.Setter(comboBox.SelectedItem);
            };
            return comboBox;
        }
    }

}
