using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace Ghurund.Controls {
    public class IconCheckBox : CheckBox {
        static IconCheckBox() {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(IconCheckBox), new FrameworkPropertyMetadata(typeof(IconCheckBox)));
        }

        [Bindable(true)]
        public ImageSource Icon {
            get { return (ImageSource)GetValue(IconProperty); }
            set { SetValue(IconProperty, value); }
        }

        public static readonly DependencyProperty IconProperty =
            DependencyProperty.Register("Icon", typeof(ImageSource), typeof(IconCheckBox), new PropertyMetadata(null));

    }
}
