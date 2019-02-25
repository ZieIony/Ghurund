using System.Windows;
using System.Windows.Controls;

namespace Ghurund.Controls.PropertyGrid {
    public class PropertyEditorContainer: DockPanel {

        public Value Value {
            get { return (Value)GetValue(ValueProperty); }
            set { SetValue(ValueProperty, value); }
        }

        public static readonly DependencyProperty ValueProperty =
            DependencyProperty.Register("Value", typeof(Value), typeof(PropertyEditorContainer), new PropertyMetadata(null));

        static PropertyEditorContainer() {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(PropertyEditorContainer), new FrameworkPropertyMetadata(typeof(PropertyEditorContainer)));
        }

        protected override void OnPropertyChanged(DependencyPropertyChangedEventArgs e) {
            base.OnPropertyChanged(e);

            if (e.Property == ValueProperty) {
                var value = Value;
                if (value != null) {
                    if (value.Editor == null) {
                        var stringValue = value.Getter()?.ToString() ?? "";
                        var indexOf = stringValue.IndexOf("\n");
                        Children.Add(new TextBlock {
                            Text = indexOf > 0 ? stringValue.Substring(0, indexOf) + ".." : stringValue,
                            ToolTip = indexOf > 0 ? stringValue : null
                        });
                    } else {
                        Children.Add(value.Editor.MakeControl(value));
                    }
                }
            }
        }
    }
}
