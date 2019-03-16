using Ghurund.Controls.PropertyGrid;
using System;
using System.Globalization;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace Ghurund.Managed {
    public class Float3PropertyEditor: IPropertyEditor {
        public FrameworkElement MakeControl(Value property) {
            TextBox textBox = new TextBox();
            textBox.Text = property.Getter().ToString();
            textBox.KeyDown += (object sender, KeyEventArgs e) => {
                if (e.Key == Key.Enter)
                    setValue(property, textBox);
            };
            textBox.LostFocus += (object sender, RoutedEventArgs e) => {
                setValue(property, textBox);
            };
            return textBox;
        }

        private static void setValue(Value property, TextBox textBox) {
            var values = textBox.Text.Split(',');
            try {
                property.Setter(new Float3(float.Parse(values[0], NumberStyles.Any), float.Parse(values[1], NumberStyles.Any), float.Parse(values[2], NumberStyles.Any)));
            } catch (Exception) {
            }
            textBox.Text = property.Getter().ToString();
        }
    }
}
