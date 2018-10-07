using System;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Ghurund.Controls.Workspace;
using Ghurund.Managed.Core;

namespace Ghurund.Editor {
    public interface ILogPanel : IDockableControl {
    }

    public partial class LogPanel : UserControl, ILogPanel {

        Logger.LogCallback callback;

        public LogPanel() {
            InitializeComponent();

            callback = new Logger.LogCallback(log);
            Logger.Init(callback);
        }

        private void log(string log) {
            logs.Text += DateTime.UtcNow.ToString("HH:mm:ssZ")+"\t"+log;
        }

        public ImageSource Icon { get; } = new BitmapImage(new Uri("pack://application:,,,/Resources/properties32.png", UriKind.Absolute));
        public Control Control { get => this; }
        public string Title { get => "Logs"; }
    }
}
