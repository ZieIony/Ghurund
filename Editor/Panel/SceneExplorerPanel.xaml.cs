using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Ghurund.Controls.Workspace;
using Ghurund.Managed.Game;

namespace Ghurund.Editor {
    public interface ISceneExplorerPanel : IToolPanel {
        Scene Scene { get; set; }
    }

    public partial class SceneExplorerPanel : UserControl, ISceneExplorerPanel {

        private List<object> selectedItems = new List<object>();
        public List<object> SelectedItems {
            get => selectedItems;
            set {
                if (selectedItems == value)
                    return;
                selectedItems = value;
                if (selectedItems == null)
                    return;
                foreach(var item in selectedItems) {
                    if (item is Scene)
                        Scene = item as Scene;
                }
            }
        }

        public static readonly RoutedEvent SelectionChangedEvent = EventManager.RegisterRoutedEvent("SelectionChanged", RoutingStrategy.Bubble, typeof(RoutedPropertyChangedEventHandler<List<object>>), typeof(ISceneExplorerPanel));

        public event RoutedPropertyChangedEventHandler<List<object>> SelectionChanged {
            add { AddHandler(SelectionChangedEvent, value); }
            remove { RemoveHandler(SelectionChangedEvent, value); }
        }


        private bool disposed = false;

        public SceneExplorerPanel() {
            InitializeComponent();

            content.Visibility = Visibility.Collapsed;
            hint.Visibility = Visibility.Visible;
        }

        ~SceneExplorerPanel() {
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

        public ImageSource Icon { get; } = new BitmapImage(new Uri("pack://application:,,,/Resources/sceneExplorer32.png", UriKind.Absolute));
        public Control Control { get => this; }
        public Title Title { get; } = new Title("Scene Explorer");

        private Scene scene;

        public Scene Scene {
            get => scene;
            set {
                if (scene == value)
                    return;

                scene?.Release();
                scene = value;
                treeView.Items.Clear();
                if (scene != null) {
                    scene.AddReference();
                    content.Visibility = Visibility.Visible;
                    hint.Visibility = Visibility.Collapsed;
                    treeView.Items.Add(scene);
                } else {
                    content.Visibility = Visibility.Collapsed;
                    hint.Visibility = Visibility.Visible;
                }
            }
        }

        private void treeView_SelectedItemChanged(object sender, RoutedPropertyChangedEventArgs<object> e) {
            SelectedItems.Clear();
            SelectedItems.Add(e.NewValue);
            RaiseEvent(new RoutedPropertyChangedEventArgs<List<object>>(null, SelectedItems, SelectionChangedEvent));
        }

        private void treeView_MouseDoubleClick(object sender, System.Windows.Input.MouseButtonEventArgs e) {
            if (treeView.SelectedItem != null) {
                var resourceFile = treeView.SelectedItem as ResourceFile;
                RaiseEvent(new RoutedFileOpenedEventArgs(resourceFile.Path, MainWindow.FileOpenedEvent));
            }
        }
    }
}
