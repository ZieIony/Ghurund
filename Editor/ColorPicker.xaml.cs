using System;
using System.Globalization;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace Ghurund.Editor {
    public enum ColorPickerMode {
        Hex, Vector, Bytes
    }

    public partial class ColorPicker: UserControl {

        private Color originalColor1;
        public Color OriginalColor {
            get => originalColor1;
            set {
                originalColor1 = value;
                Color = originalColor1;
                originalColor.Background = new SolidColorBrush(originalColor1);
            }
        }

        private bool setFromCode = false;
        private Color color1;
        public Color Color {
            get => color1;
            set {
                color1 = value;
                setFromCode = true;
                alpha.Value = color1.A;
                red.Value = color1.R;
                green.Value = color1.G;
                blue.Value = color1.B;
                setFromCode = false;
                updateColors();
                colorChanged?.Invoke(this, new ColorChangedEventArgs(color1));
            }
        }

        private readonly NumberFormatInfo formatInfo = new NumberFormatInfo();

        public class ColorChangedEventArgs: EventArgs {
            public Color Color { get; set; }

            public ColorChangedEventArgs(Color color) {
                Color = color;
            }
        }

        public delegate void ColorChangedEventHandler(object sender, ColorChangedEventArgs e);

        public ColorChangedEventHandler colorChanged;
        private ColorChangedEventHandler prevColorChanged;

        public event ColorChangedEventHandler ColorChanged {
            add {
                if (prevColorChanged != null)
                    colorChanged -= prevColorChanged;
                prevColorChanged = value;
                colorChanged += value;
            }
            remove {
                colorChanged -= value;
            }
        }

        public ColorPicker() {
            InitializeComponent();

            mode.Items.Add(ColorPickerMode.Hex);
            mode.Items.Add(ColorPickerMode.Vector);
            mode.Items.Add(ColorPickerMode.Bytes);
            mode.SelectedItem = ColorPickerMode.Hex;

            formatInfo.NumberDecimalSeparator = ".";
        }

        private float[] hueToRgb(float h) {
            float r = Math.Abs(h * 6 - 3) - 1;
            float g = 2 - Math.Abs(h * 6 - 2);
            float b = 2 - Math.Abs(h * 6 - 4);
            return new float[] { Math.Max(0, Math.Min(r, 1)), Math.Max(0, Math.Min(g, 1)), Math.Max(0, Math.Min(b, 1)) };
        }

        float[] hslToRgb(float[] hsl) {
            float[] rgb = hueToRgb(hsl[0]);
            float c = (1 - Math.Abs(2 * hsl[2] - 1)) * hsl[1];
            return new float[] { (float)((rgb[0] - 0.5) * c + hsl[2]), (float)((rgb[1] - 0.5) * c + hsl[2]), (float)((rgb[2] - 0.5) * c + hsl[2]), };
        }

        private void Wheel_MouseMove(object sender, MouseEventArgs e) {
            if (e.MouseDevice.LeftButton == MouseButtonState.Pressed) {
                Point position = e.GetPosition(wheel);
                float x = (float)(position.X / wheel.Width * 2 - 1);
                float y = (float)(position.Y / wheel.Height * 2 - 1);
                float a = (float)(Math.Atan2(y, x) / Math.PI / 2 + 0.5);
                float[] rgb = hslToRgb(new float[] { a, (float)saturation.Value, (float)lightness.Value });
                Color = Color.FromArgb((byte)alpha.Value, (byte)(rgb[0] * 255), (byte)(rgb[1] * 255), (byte)(rgb[2] * 255));
            }
        }

        private void Mode_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            updateColors();
        }

        private void updateColors() {
            switch (mode.SelectedItem) {
                case ColorPickerMode.Hex:
                    redValue.Text = ((int)red.Value).ToString("x2");
                    greenValue.Text = ((int)green.Value).ToString("x2");
                    blueValue.Text = ((int)blue.Value).ToString("x2");
                    alphaValue.Text = ((int)alpha.Value).ToString("x2");
                    colorValue.Text = alphaValue.Text + redValue.Text + greenValue.Text + blueValue.Text;
                    colorLabel.Text = "argb";
                    break;
                case ColorPickerMode.Vector:
                    redValue.Text = (red.Value / 255.0f).ToString("N2", formatInfo);
                    greenValue.Text = (green.Value / 255.0f).ToString("N2", formatInfo);
                    blueValue.Text = (blue.Value / 255.0f).ToString("N2", formatInfo);
                    alphaValue.Text = (alpha.Value / 255.0f).ToString("N2", formatInfo);
                    colorValue.Text = redValue.Text + ", " + greenValue.Text + ", " + blueValue.Text + ", " + alphaValue.Text;
                    colorLabel.Text = "rgba";
                    break;
                case ColorPickerMode.Bytes:
                    redValue.Text = ((int)red.Value).ToString();
                    greenValue.Text = ((int)green.Value).ToString();
                    blueValue.Text = ((int)blue.Value).ToString();
                    alphaValue.Text = ((int)alpha.Value).ToString();
                    colorValue.Text = alphaValue.Text + ", " + redValue.Text + ", " + greenValue.Text + ", " + blueValue.Text;
                    colorLabel.Text = "argb";
                    break;
            }

            byte a = (byte)alpha.Value;
            byte r = (byte)red.Value;
            byte g = (byte)green.Value;
            byte b = (byte)blue.Value;
            color.Background = new SolidColorBrush(Color.FromArgb(a, r, g, b));
        }

        private void slider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e) {
            if (!setFromCode)
                Color = Color.FromArgb((byte)alpha.Value, (byte)red.Value, (byte)green.Value, (byte)blue.Value);
        }

        private int parse(string text, int defaultValue) {
            int result = defaultValue;
            switch (mode.SelectedItem) {
                case ColorPickerMode.Hex:
                    int.TryParse(text, NumberStyles.HexNumber, formatInfo, out result);
                    break;
                case ColorPickerMode.Vector: {
                        float.TryParse(text, NumberStyles.Float, formatInfo, out float result2);
                        result = (int)(result2 * 255);
                    }
                    break;
                case ColorPickerMode.Bytes:
                    int.TryParse(text, out result);
                    break;
            }

            return result;
        }

        private void redValue_KeyUp(object sender, KeyEventArgs e) {
            if (e.Key != Key.Enter) return;
            red.Value = parse(redValue.Text, (int)red.Value);
        }

        private void greenValue_KeyUp(object sender, KeyEventArgs e) {
            if (e.Key != Key.Enter) return;
            green.Value = parse(greenValue.Text, (int)green.Value);
        }

        private void blueValue_KeyUp(object sender, KeyEventArgs e) {
            if (e.Key != Key.Enter) return;
            blue.Value = parse(blueValue.Text, (int)blue.Value);
        }

        private void alphaValue_KeyUp(object sender, KeyEventArgs e) {
            if (e.Key != Key.Enter) return;
            alpha.Value = parse(alphaValue.Text, (int)alpha.Value);
        }

        private void colorValue_KeyUp(object sender, KeyEventArgs e) {
            if (e.Key != Key.Enter) return;
            int parsedColor = parse(colorValue.Text, -1);
            if (parsedColor != -1) {
                byte a = (byte)(parsedColor >> 24);
                byte r = (byte)((parsedColor >> 16) & 0xff);
                byte g = (byte)((parsedColor >> 8) & 0xff);
                byte b = (byte)(parsedColor & 0xff);
                Color = Color.FromArgb(a, r, g, b);
            }
        }

        private void saturation_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e) {
            if (effect != null)
                effect.Saturation = e.NewValue;
            saturationValue.Text = saturation.Value.ToString("N2", formatInfo);
        }

        private void saturationValue_KeyUp(object sender, KeyEventArgs e) {
            if (e.Key != Key.Enter) return;
            if (float.TryParse(saturationValue.Text, NumberStyles.Float, formatInfo, out float result))
                saturation.Value = result;
        }

        private void lightness_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e) {
            if (effect != null)
                effect.Lightness = e.NewValue;
            lightnessValue.Text = lightness.Value.ToString("N2", formatInfo);
        }

        private void lightnessValue_KeyUp(object sender, KeyEventArgs e) {
            if (e.Key != Key.Enter) return;
            if (float.TryParse(lightnessValue.Text, NumberStyles.Float, formatInfo, out float result))
                lightness.Value = result;
        }

        private void OriginalColor_MouseDown(object sender, MouseButtonEventArgs e) {
            Color = OriginalColor;
        }

        private void Color_MouseDown(object sender, MouseButtonEventArgs e) {
            OriginalColor = Color;
        }
    }
}
