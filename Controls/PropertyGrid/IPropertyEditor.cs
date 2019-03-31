using System.Windows;

namespace Ghurund.Controls.PropertyGrid {
    public interface IPropertyEditor {
        FrameworkElement MakeControl(Value property);
    }

}
