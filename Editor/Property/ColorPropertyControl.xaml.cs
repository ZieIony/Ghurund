using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using Ghurund.Controls.PropertyGrid;
using Ghurund.Managed;

namespace Ghurund.Editor.Property {

    public partial class ColorPropertyControl: UserControl {
        private ColorPickerWindow picker;

        private Value colorProperty;
        public Value ColorProperty {
            get => colorProperty;
            set {
                colorProperty = value;
                textBox.Text = ColorProperty.Getter().ToString();
                Color c = (Color)ColorProperty.Getter();
                var c2 = System.Windows.Media.Color.FromArgb((byte)(c.A * 255), (byte)(c.R * 255), (byte)(c.G * 255), (byte)(c.B * 255));
                color.Background = new System.Windows.Media.SolidColorBrush(c2);
            }
        }

        public ColorPropertyControl() {
            InitializeComponent();

            picker = EditorKernel.GetService(typeof(ColorPickerWindow)) as ColorPickerWindow;
        }

        private void TextBox_LostFocus(object sender, RoutedEventArgs e) {
            color.Background = new System.Windows.Media.SolidColorBrush((System.Windows.Media.Color)System.Windows.Media.ColorConverter.ConvertFromString(textBox.Text));
            ColorProperty.Setter(new Color(textBox.Text));
        }

        private void TextBox_KeyDown(object sender, KeyEventArgs e) {
            if (e.Key == Key.Enter) {
                color.Background = new System.Windows.Media.SolidColorBrush((System.Windows.Media.Color)System.Windows.Media.ColorConverter.ConvertFromString(textBox.Text));
                ColorProperty.Setter(new Color(textBox.Text));
            }
        }

        private void Border_MouseUp(object sender, MouseButtonEventArgs e) {
            Color c = (Color)ColorProperty.Getter();
            picker.ColorPicker.ColorChanged += ColorPicker_ColorChanged;
            picker.ColorPicker.OriginalColor = System.Windows.Media.Color.FromArgb((byte)(c.A * 255), (byte)(c.R * 255), (byte)(c.G * 255), (byte)(c.B * 255));
            picker.Show();
        }

        private void ColorPicker_ColorChanged(object sender, ColorPicker.ColorChangedEventArgs e) {
            Color c = new Color {
                A = e.Color.A / 255.0f,
                R = e.Color.R / 255.0f,
                G = e.Color.G / 255.0f,
                B = e.Color.B / 255.0f
            };
            ColorProperty.Setter(c);
            color.Background = new System.Windows.Media.SolidColorBrush(e.Color);
            textBox.Text = ColorProperty.Getter().ToString();
        }
    }
}
