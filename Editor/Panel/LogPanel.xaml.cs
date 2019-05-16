using System;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Ghurund.Controls.Workspace;
using Ghurund.Managed.Core;
using static Ghurund.Controls.LogsView;

namespace Ghurund.Editor {
    public interface ILogPanel : IDockablePanel {
    }

    public partial class LogPanel : UserControl, ILogPanel {

        Logger.LogCallback callback;
        private bool disposed = false;

        public LogPanel() {
            InitializeComponent();

            callback = new Logger.LogCallback(log);
            Logger.Init(callback);
        }

        ~LogPanel() {
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

        private void log(string log) {
            logs.Logs.Add(new Log() {
                Time = DateTime.UtcNow.ToString("HH:mm:ssZ"),
                Message = log.Substring(log.IndexOf(']')+1).Trim()
            });
        }

        public ImageSource Icon { get; } = new BitmapImage(new Uri("pack://application:,,,/Resources/icons/logs32.png", UriKind.Absolute));
        public Control Control { get => this; }
        public Title Title { get; } = new Title("Logs");

        private void ClearLogs_Click(object sender, System.Windows.RoutedEventArgs e) {
            logs.Logs.Clear();
        }

        private void ScrollToBottom_Click(object sender, System.Windows.RoutedEventArgs e) {
            logs.ScrollToBottom();
        }
    }
}
