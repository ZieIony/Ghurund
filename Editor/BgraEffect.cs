using System;
using System.Drawing;
using System.Windows;
using System.Windows.Media.Effects;

namespace Ghurund.Editor {
    public class BgraEffect: ShaderEffect {
        private static PixelShader pixelShader = new PixelShader() {
            UriSource = new Uri("pack://application:,,,/Resources/effects/bgra.ps", UriKind.Absolute)
        };

        public BgraEffect() {
            PixelShader = pixelShader;

            UpdateShaderValue(InputProperty);
        }

        public Brush Input {
            get { return (Brush)GetValue(InputProperty); }
            set { SetValue(InputProperty, value); }
        }

        public static readonly DependencyProperty InputProperty = RegisterPixelShaderSamplerProperty("Input", typeof(BgraEffect), 0);
    }
}
