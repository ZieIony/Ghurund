using Ghurund.Controls.PropertyGrid;
using System.Windows;

namespace Ghurund.Editor.Property {
    public class ColorPropertyEditor: IPropertyEditor {
        public FrameworkElement MakeControl(Value property) {
            ColorPropertyControl control = new ColorPropertyControl {
                ColorProperty = property
            };
            return control;
        }

    }
}
