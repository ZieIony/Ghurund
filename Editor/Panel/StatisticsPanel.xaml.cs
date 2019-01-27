using System;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Ghurund.Controls.Workspace;

namespace Ghurund.Editor.Panel {
    public interface IStatisticsPanel : IDockableControl {
        object SelectedObject { get; set; }
    }

    public partial class StatisticsPanel : UserControl, IStatisticsPanel {
        private bool disposed = false;

        public StatisticsPanel() {
            InitializeComponent();
        }

        ~StatisticsPanel() {
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

        public ImageSource Icon { get; } = new BitmapImage(new Uri("pack://application:,,,/Resources/statistics32.png", UriKind.Absolute));
        public Control Control { get => this; }
        public Title Title { get; } = new Title("Statistics");
        public object SelectedObject { get => propertyGrid.SelectedObject; set => propertyGrid.SelectedObject = value; }
    }
}
