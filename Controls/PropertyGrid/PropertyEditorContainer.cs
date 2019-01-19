using System.Windows;
using System.Windows.Controls;

namespace Ghurund.Controls.PropertyGrid {
    public class PropertyEditorContainer : DockPanel {

        public Property Property {
            get { return (Property)GetValue(PropertyProperty); }
            set { SetValue(PropertyProperty, value); }
        }

        public static readonly DependencyProperty PropertyProperty =
            DependencyProperty.Register("Property", typeof(Property), typeof(PropertyEditorContainer), new PropertyMetadata(null));

        static PropertyEditorContainer() {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(PropertyEditorContainer), new FrameworkPropertyMetadata(typeof(PropertyEditorContainer)));
        }

        protected override void OnPropertyChanged(DependencyPropertyChangedEventArgs e) {
            base.OnPropertyChanged(e);

            if (e.Property == PropertyProperty) {
                var property = Property;
                if (property != null) {
                    if (property.Editor == null) {
                        var stringValue = property.ValueGetter().ToString();
                        var indexOf = stringValue.IndexOf("\n");
                        Children.Add(new TextBlock {
                            Text = indexOf > 0 ? stringValue.Substring(0, indexOf) + ".." : stringValue,
                            ToolTip = indexOf > 0 ? stringValue : null
                        });
                    } else {
                        Children.Add(property.Editor.MakeControl(property));
                    }
                }
            }
        }
    }
}
