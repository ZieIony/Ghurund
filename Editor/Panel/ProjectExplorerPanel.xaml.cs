using System;
using System.IO;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Ghurund.Controls.Workspace;

namespace Ghurund.Editor {

    public interface IProjectExplorerPanel : IDockablePanel {
        Project Project { get; set; }
    }

    public partial class ProjectExplorerPanel : UserControl, IProjectExplorerPanel {
        private bool disposed = false;

        public ProjectExplorerPanel() {
            InitializeComponent();

            hint.Visibility = System.Windows.Visibility.Visible;
            content.Visibility = System.Windows.Visibility.Collapsed;
        }

        ~ProjectExplorerPanel() {
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

        public ImageSource Icon { get; } = new BitmapImage(new Uri("pack://application:,,,/Resources/icons/projectExplorer32.png", UriKind.Absolute));
        public Control Control { get => this; }
        public Title Title { get; } = new Title("Project Explorer");

        private Project project;
        public Project Project {
            get => project;
            set {
                project = value;
                treeView.Items.Clear();
                if (project != null) {
                    content.Visibility = System.Windows.Visibility.Visible;
                    hint.Visibility = System.Windows.Visibility.Collapsed;
                    TreeViewItem item = new TreeViewItem {
                        Header = value.Name,
                        Tag = new FileInfo(value.Path).Directory
                    };
                    item.Items.Add("Loading...");
                    treeView.Items.Add(item);
                } else {
                    content.Visibility = System.Windows.Visibility.Collapsed;
                    hint.Visibility = System.Windows.Visibility.Visible;
                }
            }
        }

        private void treeView_Expanded(object sender, System.Windows.RoutedEventArgs e) {
            TreeViewItem expandedItem = e.Source as TreeViewItem;
            if ((expandedItem.Items.Count == 1) && (expandedItem.Items[0] is string)) {
                expandedItem.Items.Clear();

                DirectoryInfo expandedDir = null;
                if (expandedItem.Tag is DriveInfo)
                    expandedDir = (expandedItem.Tag as DriveInfo).RootDirectory;
                if (expandedItem.Tag is DirectoryInfo)
                    expandedDir = expandedItem.Tag as DirectoryInfo;
                try {
                    foreach (DirectoryInfo subDir in expandedDir.GetDirectories()) {
                        TreeViewItem item = new TreeViewItem {
                            Header = subDir.Name,
                            Tag = subDir
                        };
                        item.Items.Add("Loading...");
                        expandedItem.Items.Add(item);
                    }
                    foreach (FileInfo fileInfo in expandedDir.GetFiles()) {
                        TreeViewItem item = new TreeViewItem {
                            Header = fileInfo.Name,
                            Tag = fileInfo
                        };
                        expandedItem.Items.Add(item);
                    }
                } catch { }
            }
        }

        private void OnItemMouseDoubleClick(object sender, System.Windows.Input.MouseButtonEventArgs e) {
            TreeViewItem item = treeView.SelectedItem as TreeViewItem;
            if (!(item.Tag is FileInfo))
                return;

            FileInfo info = item.Tag as FileInfo;
            RaiseEvent(new RoutedFileOpenedEventArgs(info.FullName, MainWindow.FileOpenedEvent));
        }
    }
}
