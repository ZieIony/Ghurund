using System;
using System.Collections.Generic;
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

            List<ResourceFile> projects = new List<ResourceFile>();
            foreach (string path in Settings.RecentProjects)
                projects.Add(new ResourceFile(path));
            recentProjects.ItemsSource = projects;

            List<ResourceFile> files = new List<ResourceFile>();
            foreach (string path in Settings.RecentFiles)
                files.Add(new ResourceFile(path));
            recentFiles.ItemsSource = files;
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

        private void RecentProjects_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            var resourceFile = recentProjects.SelectedItem as ResourceFile;
            RaiseEvent(new RoutedFileOpenedEventArgs(resourceFile.Path, MainWindow.FileOpenedEvent));
        }

        private void RecentFiles_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            var resourceFile = recentFiles.SelectedItem as ResourceFile;
            RaiseEvent(new RoutedFileOpenedEventArgs(resourceFile.Path, MainWindow.FileOpenedEvent));
        }

        private void Hyperlink_RequestNavigate(object sender, System.Windows.Navigation.RequestNavigateEventArgs e) {
            Process.Start(e.Uri.ToString());
        }

        private void NewProject_RequestNavigate(object sender, System.Windows.Navigation.RequestNavigateEventArgs e) {
            RaiseEvent(new RoutedActionPerformedEventArgs(EditorAction.NewProject, MainWindow.ActionPerformedEvent));
        }

        private void OpenFile_RequestNavigate(object sender, System.Windows.Navigation.RequestNavigateEventArgs e) {
            RaiseEvent(new RoutedActionPerformedEventArgs(EditorAction.OpenFile, MainWindow.ActionPerformedEvent));
        }
    }
}
