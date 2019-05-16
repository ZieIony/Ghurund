using System;
using System.Drawing;
using System.Windows;
using System.Windows.Media.Effects;

namespace Ghurund.Editor {
    public class ColorWheelEffect: ShaderEffect {
        private static PixelShader pixelShader = new PixelShader() {
            UriSource = new Uri("pack://application:,,,/Resources/effects/colorWheel.ps", UriKind.Absolute)
        };

        public ColorWheelEffect() {
            PixelShader = pixelShader;

            UpdateShaderValue(InputProperty);
            UpdateShaderValue(SaturationProperty);
            UpdateShaderValue(LightnessProperty);
        }

        public Brush Input {
            get { return (Brush)GetValue(InputProperty); }
            set { SetValue(InputProperty, value); }
        }

        public static readonly DependencyProperty InputProperty = RegisterPixelShaderSamplerProperty("Input", typeof(ColorWheelEffect), 0);

        public double Saturation {
            get { return (double)GetValue(SaturationProperty); }
            set { SetValue(SaturationProperty, value); }
        }

        public static readonly DependencyProperty SaturationProperty =
            DependencyProperty.Register("saturation", typeof(double), typeof(ColorWheelEffect),
                    new UIPropertyMetadata(1.0, PixelShaderConstantCallback(0)));

        public double Lightness {
            get { return (double)GetValue(LightnessProperty); }
            set { SetValue(LightnessProperty, value); }
        }

        public static readonly DependencyProperty LightnessProperty =
            DependencyProperty.Register("lightness", typeof(double), typeof(ColorWheelEffect),
                    new UIPropertyMetadata(0.5, PixelShaderConstantCallback(1)));

    }
}
