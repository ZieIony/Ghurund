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

        public ParametersPanel() {
            InitializeComponent();

            EditorKernel.Instance.Inject(this);
        }

        public ImageSource Icon { get; } = new BitmapImage(new Uri("pack://application:,,,/Resources/properties32.png", UriKind.Absolute));
        public Control Control { get => this; }
        public string Title { get => "Parameters"; }

        public ObservableCollection<Property> Parameters {
            get => propertyGrid.Properties;
            set => propertyGrid.Properties = value;
        }
    }
}
