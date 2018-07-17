using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace Ghurund.Controls {
    public class HintTextBox : TextBox {

        public string HintText {
            get { return (string)GetValue(HintTextProperty); }
            set { SetValue(HintTextProperty, value); }
        }

        public static readonly DependencyProperty HintTextProperty =
            DependencyProperty.Register("HintText", typeof(string), typeof(HintTextBox), new PropertyMetadata(null));

        public Brush HintBrush {
            get { return (Brush)GetValue(HintBrushProperty); }
            set { SetValue(HintBrushProperty, value); }
        }

        public static readonly DependencyProperty HintBrushProperty =
            DependencyProperty.Register("HintBrush", typeof(Brush), typeof(HintTextBox), new PropertyMetadata(null));

        static HintTextBox() {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(HintTextBox), new FrameworkPropertyMetadata(typeof(HintTextBox)));
        }
    }
}
