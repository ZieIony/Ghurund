using System;
using System.Collections.ObjectModel;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Ghurund.Controls;
using Ghurund.Controls.Workspace;
using Ghurund.Managed.Game;
using Ninject;

namespace Ghurund.Editor {
    public interface IParametersPanel : IDockableControl {
        ObservableCollection<Property> Parameters { get; set; }
    }

    public partial class ParametersPanel : UserControl, IParametersPanel {
        [Inject]
        ParameterManager ParameterManager { get; }

        private bool disposed = false;

        public ParametersPanel() {
            InitializeComponent();

            EditorKernel.Instance.Inject(this);
        }

        ~ParametersPanel() {
            Dispose(false);
        }

        public void Dispose() {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing) {
            if (disposed)
                return;

            // don't dispose parameter manager - this panel doesn't own it

            disposed = true;
        }

        public ImageSource Icon { get; } = new BitmapImage(new Uri("pack://application:,,,/Resources/properties32.png", UriKind.Absolute));
        public Control Control { get => this; }
        public Title Title { get; } = new Title("Parameters");

        public ObservableCollection<Property> Parameters {
            get => propertyGrid.Properties;
            set => propertyGrid.Properties = value;
        }
    }
}
