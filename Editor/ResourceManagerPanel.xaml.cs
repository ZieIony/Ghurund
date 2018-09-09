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
using Microsoft.WindowsAPICodePack.Shell;
using Ninject;

namespace Ghurund.Editor {
    public class ResourceDirectory {
        public string Name { get; set; }
        public object Tag { get; set; }
        public ObservableCollection<object> Items { get; } = new ObservableCollection<object>();
    }

    public class Library : ResourceDirectory {
    }

    public class ResourceFile {
        public string Path { get; set; }
        public string Name { get; set; }
        public string Size => Length / 1024 + "kB";
        public long Length { get; set; }
        public String Modified { get; set; }

        public BitmapSource Thumbnail {
            get {
                if (Path == null)
                    return null;
                ShellFile shellFile = ShellFile.FromFilePath(Path);
                return shellFile.Thumbnail.Bitmap.ToBitmapSource();
            }
        }
    }

    public interface IResourceManagerPanel : IDockableControl {
        event RoutedEditorOpenedEventHandler EditorOpened;
    }

    public partial class ResourceManagerPanel : UserControl, IResourceManagerPanel {
        [Inject]
        public ResourceManager ResourceManager { get; set; }

        [Inject]
        public EditorSettings Settings { get; set; }

        public static readonly RoutedEvent EditorOpenedEvent = EventManager.RegisterRoutedEvent("EditorOpened", RoutingStrategy.Bubble, typeof(RoutedEditorOpenedEventHandler), typeof(IResourceManagerPanel));

        public event RoutedEditorOpenedEventHandler EditorOpened {
            add { AddHandler(EditorOpenedEvent, value); }
            remove { RemoveHandler(EditorOpenedEvent, value); }
        }


        public ResourceManagerPanel() {
            InitializeComponent();

            EditorKernel.Instance.Inject(this);

            foreach (string library in Settings.Libraries)
                loadLibrary(library);
        }

        public ImageSource Icon { get; }
        public Control Control { get => this; }
        public string Title { get => "Resource Manager"; }

        private void Button_Click(object sender, System.Windows.RoutedEventArgs e) {
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
                if (file.Extension.StartsWith(".") &&
                    !ResourceFormat.Values.Where((format) => format.Extension != null && format.Extension.Equals(file.Extension.Substring(1))).Any())
                    continue;

                ResourceFile item = new ResourceFile {
                    Path = file.FullName,
                    Name = file.Name,
                    Length = file.Length,
                    Modified = file.LastWriteTime.ToShortDateString()
                };
                resourceGrid.Items.Add(item);
            }
        }

        private void treeView_MouseDoubleClick(object sender, System.Windows.Input.MouseButtonEventArgs e) {
            if (resourceGrid.SelectedItem != null) {
                var resourceFile = resourceGrid.SelectedItem as ResourceFile;
                if (resourceFile.Path.EndsWith("jpg") || resourceFile.Path.EndsWith("jpeg") || resourceFile.Path.EndsWith("png")) {
                    BitmapImage image = new BitmapImage(new Uri(resourceFile.Path));
                    RaiseEvent(new RoutedEditorOpenedEventArgs(image, EditorOpenedEvent));
                }
            }
        }
    }
}
