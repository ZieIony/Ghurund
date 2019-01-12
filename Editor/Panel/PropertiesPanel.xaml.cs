using System;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Ghurund.Controls.Workspace;

namespace Ghurund.Editor {
    public interface IPropertiesPanel : IDockableControl {
        object SelectedObject { get; set; }
    }

    public partial class PropertiesPanel : UserControl, IPropertiesPanel {
        private bool disposed = false;

        public PropertiesPanel() {
            InitializeComponent();
        }

        ~PropertiesPanel() {
            Dispose(false);
        }

        public void Dispose() {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing) {
            if (disposed)
                return;

            disposed = true;
        }

        public ImageSource Icon { get; } = new BitmapImage(new Uri("pack://application:,,,/Resources/properties32.png", UriKind.Absolute));
        public Control Control { get => this; }
        public Title Title { get; } = new Title("Properties");
        public object SelectedObject { get => propertyGrid.SelectedObject; set => propertyGrid.SelectedObject = value; }
    }
}
