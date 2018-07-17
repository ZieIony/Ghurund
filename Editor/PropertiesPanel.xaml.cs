using System;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Ghurund.Controls.Workspace;
using Ghurund.Managed.Graphics;

namespace Ghurund.Editor {
    public interface IPropertiesPanel : IDockableControl {
        object SelectedObject { get; set; }
    }

    public partial class PropertiesPanel : UserControl, IPropertiesPanel {
        public PropertiesPanel() {
            InitializeComponent();
        }

        public ImageSource Icon { get; } = new BitmapImage(new Uri("pack://application:,,,/Resources/properties32.png", UriKind.Absolute));
        public Control Control { get => this; }
        public string Title { get => "Properties"; }
        public object SelectedObject { get => propertyGrid.SelectedObject; set => propertyGrid.SelectedObject = value; }
    }
}
