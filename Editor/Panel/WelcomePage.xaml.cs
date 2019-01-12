using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
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

            recentProjects.ItemsSource = Settings.RecentProjects.Select(path => new ResourceFile(path)).ToList();
            recentFiles.ItemsSource = Settings.RecentFiles.Select(path => new ResourceFile(path)).ToList();
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

        private void RecentProjects_SelectionChanged(object sender, System.Windows.Input.MouseButtonEventArgs e) {
            var resourceFile = recentProjects.SelectedItem as ResourceFile;
            if (!resourceFile.Exists) {
                if (MessageBox.Show("The selected project doesn't exist. Do you want to remove it from the recent projects list?", "Project doesn't exist", MessageBoxButton.YesNo, MessageBoxImage.Question) == MessageBoxResult.Yes) {
                    Settings.RecentProjects.Remove(resourceFile.Path);
                    recentProjects.ItemsSource = Settings.RecentProjects.Select(path => new ResourceFile(path)).ToList();
                }
            } else {
                RaiseEvent(new RoutedFileOpenedEventArgs(resourceFile.Path, MainWindow.FileOpenedEvent));
            }
        }

        private void RecentFiles_SelectionChanged(object sender, System.Windows.Input.MouseButtonEventArgs e) {
            var resourceFile = recentFiles.SelectedItem as ResourceFile;
            if (!resourceFile.Exists) {
                if (MessageBox.Show("The selected file doesn't exist. Do you want to remove it from the recent files list?", "File doesn't exist", MessageBoxButton.YesNo, MessageBoxImage.Question) == MessageBoxResult.Yes) {
                    Settings.RecentFiles.Remove(resourceFile.Path);
                    recentFiles.ItemsSource = Settings.RecentFiles.Select(path => new ResourceFile(path)).ToList();
                }
            } else {
                RaiseEvent(new RoutedFileOpenedEventArgs(resourceFile.Path, MainWindow.FileOpenedEvent));
            }
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
