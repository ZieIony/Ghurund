using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace Ghurund.Controls.PropertyGrid {
    public interface IPropertyEditor {
        FrameworkElement MakeControl(Value property);
    }

    public class BooleanPropertyEditor : IPropertyEditor {
        public FrameworkElement MakeControl(Value property) {
            CheckBox checkBox = new CheckBox();
            checkBox.IsChecked = (bool)property.Getter();
            checkBox.Checked += (object sender, RoutedEventArgs e) => {
                property.Setter(checkBox.IsChecked);
            };
            checkBox.Unchecked += (object sender, RoutedEventArgs e) => {
                property.Setter(checkBox.IsChecked);
            };
            return checkBox;
        }
    }

    public class FloatPropertyEditor : IPropertyEditor {
        public FrameworkElement MakeControl(Value property) {
            TextBox textBox = new TextBox();
            textBox.Text = property.Getter().ToString();
            textBox.KeyDown += (object sender, KeyEventArgs e) => {
                if (e.Key == Key.Enter) {
                    float val;
                    property.Setter(float.TryParse(textBox.Text, out val) ? val : property.Getter());
                }
            };
            return textBox;
        }
    }
}
