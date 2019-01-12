using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Ghurund.Controls.Workspace;
using Ghurund.Managed.Game;

namespace Ghurund.Editor {
    public interface ISceneExplorerPanel : IDockableControl {
        Scene Scene { get; set; }

        event RoutedPropertyChangedEventHandler<Entity> SelectedEntityChanged;
    }

    public partial class SceneExplorerPanel : UserControl, ISceneExplorerPanel {

        public static readonly RoutedEvent SelectedEntityChangedEvent = EventManager.RegisterRoutedEvent("SelectedEntityChanged", RoutingStrategy.Bubble, typeof(RoutedPropertyChangedEventHandler<Entity>), typeof(ISceneExplorerPanel));

        public event RoutedPropertyChangedEventHandler<Entity> SelectedEntityChanged {
            add { AddHandler(SelectedEntityChangedEvent, value); }
            remove { RemoveHandler(SelectedEntityChangedEvent, value); }
        }


        private bool disposed = false;

        public SceneExplorerPanel() {
            InitializeComponent();
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
                scene = value;
                treeView.Items.Clear();
                treeView.Items.Add(scene);
            }
        }

        private void treeView_SelectedItemChanged(object sender, RoutedPropertyChangedEventArgs<object> e) {
            RaiseEvent(new RoutedPropertyChangedEventArgs<Entity>(e.OldValue as Entity, e.NewValue as Entity, SelectedEntityChangedEvent));
        }

        private void treeView_MouseDoubleClick(object sender, System.Windows.Input.MouseButtonEventArgs e) {
            if (treeView.SelectedItem != null) {
                var resourceFile = treeView.SelectedItem as ResourceFile;
                RaiseEvent(new RoutedFileOpenedEventArgs(resourceFile.Path, MainWindow.FileOpenedEvent));
            }
        }
    }
}
