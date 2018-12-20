using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Ghurund.Controls.Workspace;
using Ninject;

namespace Ghurund.Editor {
    public interface IWelcomePage : IDockableControl {
    }

    public partial class WelcomePage : UserControl, IWelcomePage {

        [Inject]
        public EditorSettings Settings { get; set; }

        private bool disposed = false;

        public WelcomePage() {
            InitializeComponent();

            EditorKernel.Instance.Inject(this);

            recentProjects.ItemsSource = Settings.RecentProjects;
            recentFiles.ItemsSource = Settings.RecentFiles;
        }

        ~WelcomePage() {
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

        public ImageSource Icon { get; } = new BitmapImage(new Uri("pack://application:,,,/Resources/welcomePage32.png", UriKind.Absolute));
        public Control Control { get => this; }
        public Title Title { get; } = new Title("Welcome Page");

        public static readonly RoutedEvent RecentProjectOpenedEvent = EventManager.RegisterRoutedEvent("RecentProjectOpened", RoutingStrategy.Bubble, typeof(RoutedEditorOpenedEventHandler), typeof(IResourceManagerPanel));

        public event RoutedEditorOpenedEventHandler RecentProjectOpened {
            add { AddHandler(RecentProjectOpenedEvent, value); }
            remove { RemoveHandler(RecentProjectOpenedEvent, value); }
        }

        private void RecentProjects_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            RaiseEvent(new RoutedEditorOpenedEventArgs(recentProjects.SelectedItem as ResourceFile, RecentProjectOpenedEvent));
        }

        public static readonly RoutedEvent RecentFileOpenedEvent = EventManager.RegisterRoutedEvent("RecentFileOpened", RoutingStrategy.Bubble, typeof(RoutedEditorOpenedEventHandler), typeof(IResourceManagerPanel));

        public event RoutedEditorOpenedEventHandler RecentFileOpened {
            add { AddHandler(RecentFileOpenedEvent, value); }
            remove { RemoveHandler(RecentFileOpenedEvent, value); }
        }

        private void RecentFiles_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            RaiseEvent(new RoutedEditorOpenedEventArgs(recentFiles.SelectedItem as ResourceFile, RecentFileOpenedEvent));
        }

        private void Hyperlink_RequestNavigate(object sender, System.Windows.Navigation.RequestNavigateEventArgs e) {
            Process.Start(e.Uri.ToString());
        }
    }
}
