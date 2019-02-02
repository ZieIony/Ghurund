using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Ghurund.Controls.Workspace;
using Ghurund.Managed.Resource;
using Ninject;

namespace Ghurund.Editor {
    public class ResourceDirectory {
        public string Name { get; set; }
        public object Tag { get; set; }
        public ObservableCollection<object> Items { get; } = new ObservableCollection<object>();
    }

    public class Library : ResourceDirectory {
    }

    public interface IResourceManagerPanel : IDockablePanel {
    }

    public partial class ResourceManagerPanel : UserControl, IResourceManagerPanel {
        [Inject]
        public ResourceManager ResourceManager { get; set; }

        [Inject]
        public EditorSettings Settings { get; set; }

        string[] supportedExtensions;

        private bool disposed = false;


        public ResourceManagerPanel() {
            InitializeComponent();

            EditorKernel.Instance.Inject(this);

            supportedExtensions = ResourceFormat.Values.Map(format => format.Extension).Filter(extension => extension != null).ToArray();

            foreach (string library in Settings.Libraries)
                loadLibrary(library);
        }

        ~ResourceManagerPanel() {
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

        public ImageSource Icon { get; } = new BitmapImage(new Uri("pack://application:,,,/Resources/resourceManager32.png", UriKind.Absolute));
        public Control Control { get => this; }
        public Title Title { get; } = new Title("Resource Manager");

        private void Button_Click(object sender, RoutedEventArgs e) {
            var dialog = new System.Windows.Forms.FolderBrowserDialog();
            if (dialog.ShowDialog() == System.Windows.Forms.DialogResult.OK) {
                addLibrary(dialog.SelectedPath);
            }
            /*progressBar.Visibility = System.Windows.Visibility.Visible;
            resourceManager.LoadImage("D:/projekty/visual studio 2017/GhurundEngine12/Debug/cow.jpg", (status) => {
                progressBar.Dispatcher.Invoke(new Action(() => {
                    progressBar.Visibility = System.Windows.Visibility.Collapsed;
                }));
            });*/
        }

        private void addLibrary(string path) {
            Settings.Libraries.Add(path);
            loadLibrary(path);
        }

        private void loadLibrary(string path) {
            var dir = new DirectoryInfo(path);

            Library item = new Library {
                Name = dir.Name,
                Tag = dir
            };
            item.Items.Add("Loading...");
            treeView.Items.Add(item);

            /*
            List<DirectoryInfo> dirList = new List<DirectoryInfo>();
            dirList.Add(new DirectoryInfo(path));

            while (dirList.Count > 0) {
                var dir = dirList[0];
                dirList.RemoveAt(0);

                var files = dir.GetFiles();
                foreach(FileInfo file in files) {
                    
                }

                dirList.AddRange(dir.GetDirectories());
            }*/
        }

        private void treeView_Expanded(object sender, System.Windows.RoutedEventArgs e) {
            TreeViewItem tvi = e.OriginalSource as TreeViewItem;
            ResourceDirectory expandedItem = tvi.Header as ResourceDirectory;
            if ((expandedItem.Items.Count == 1) && (expandedItem.Items[0] is string)) {
                expandedItem.Items.Clear();

                DirectoryInfo expandedDir = null;
                if (expandedItem.Tag is DriveInfo)
                    expandedDir = (expandedItem.Tag as DriveInfo).RootDirectory;
                if (expandedItem.Tag is DirectoryInfo)
                    expandedDir = (expandedItem.Tag as DirectoryInfo);
                try {
                    foreach (DirectoryInfo subDir in expandedDir.GetDirectories()) {
                        ResourceDirectory item = new ResourceDirectory {
                            Name = subDir.ToString(),
                            Tag = subDir
                        };
                        if (subDir.GetDirectories().Length > 0)
                            item.Items.Add("Loading...");
                        expandedItem.Items.Add(item);
                    }
                } catch { }
            }
        }

        private void treeView_SelectedItemChanged(object sender, RoutedPropertyChangedEventArgs<object> e) {
            ResourceDirectory expandedItem = e.NewValue as ResourceDirectory;

            resourceGrid.Items.Clear();

            var expandedDir = (expandedItem.Tag as DirectoryInfo);

            foreach (FileInfo file in expandedDir.GetFiles()) {
                if (file.Extension.StartsWith(".") && supportedExtensions.Contains(file.Extension.Substring(1)))
                    resourceGrid.Items.Add(new ResourceFile(file));
            }
        }

        private void treeView_MouseDoubleClick(object sender, System.Windows.Input.MouseButtonEventArgs e) {
            if (resourceGrid.SelectedItem != null) {
                var resourceFile = resourceGrid.SelectedItem as ResourceFile;
                RaiseEvent(new RoutedFileOpenedEventArgs(resourceFile.Path, MainWindow.FileOpenedEvent));
            }
        }
    }
}
