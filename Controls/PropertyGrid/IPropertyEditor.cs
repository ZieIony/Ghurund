using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace Ghurund.Controls.PropertyGrid {
    public interface IPropertyEditor {
        FrameworkElement MakeControl(Property property);
    }

    public class BooleanPropertyEditor : IPropertyEditor {
        public FrameworkElement MakeControl(Property property) {
            CheckBox checkBox = new CheckBox();
            checkBox.IsChecked = (bool)property.ValueGetter.Invoke();
            checkBox.Checked += (object sender, RoutedEventArgs e) => {
                property.ValueSetter.Invoke(checkBox.IsChecked);
            };
            checkBox.Unchecked += (object sender, RoutedEventArgs e) => {
                property.ValueSetter.Invoke(checkBox.IsChecked);
            };
            return checkBox;
        }
    }

    public class FloatPropertyEditor : IPropertyEditor {
        public FrameworkElement MakeControl(Property property) {
            TextBox textBox = new TextBox();
            textBox.Text = property.ValueGetter.Invoke().ToString();
            textBox.KeyDown += (object sender, KeyEventArgs e) => {
                if (e.Key == Key.Enter) {
                    float val;
                    property.ValueSetter.Invoke(float.TryParse(textBox.Text, out val) ? val : property.ValueGetter.Invoke());
                }
            };
            return textBox;
        }
    }
}
