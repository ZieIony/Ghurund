using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Ghurund.Controls.Workspace;
using Ghurund.Managed.Game;
using Ghurund.Managed.Graphics;
using Ghurund.Managed.Resource;
using Ninject;

namespace Ghurund.Editor {
    public interface ISceneExplorerPanel: IToolPanel {
        Scene Scene { get; set; }
    }

    public enum GeometryType {
        Cube, Cone, Sphere, Plane
    }

    public partial class SceneExplorerPanel: UserControl, ISceneExplorerPanel {

        [Inject]
        public ParameterManager ParameterManager { get; set; }

        [Inject]
        public ResourceContext ResourceContext { get; set; }

        private readonly List<object> selectedItems = new List<object>();
        public List<object> SelectedItems {
            get => selectedItems;
            set {
                selectedItems.Clear();
                selectedItems.AddRange(value);
                foreach (var item in selectedItems) {
                    if (item is Scene)
                        Scene = item as Scene;
                }
            }
        }

        private bool disposed = false;

        public SceneExplorerPanel() {
            InitializeComponent();

            EditorKernel.Inject(this);

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

        public ImageSource Icon { get; } = new BitmapImage(new Uri("pack://application:,,,/Resources/icons/sceneExplorer32.png", UriKind.Absolute));
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
            RaiseEvent(new RoutedSelectionChangedEventArgs(new List<object>(SelectedItems), WorkspacePanel.SelectionChangedEvent));
        }

        private void treeView_MouseDoubleClick(object sender, System.Windows.Input.MouseButtonEventArgs e) {
            if (treeView.SelectedItem != null) {
                var resourceFile = treeView.SelectedItem as ResourceFile;
                RaiseEvent(new RoutedFileOpenedEventArgs(resourceFile.Path, MainWindow.FileOpenedEvent));
            }
        }

        private void addLight_Click(object sender, RoutedEventArgs e) {
            var l = new Light();
            l.InitParameters(ParameterManager);
            scene.Entities.Add(l);
        }

        private void addCamera_Click(object sender, RoutedEventArgs e) {
            var c = new Camera();
            c.InitParameters(ParameterManager);
            scene.Entities.Add(c);
        }

        private void addCube_Click(object sender, RoutedEventArgs e) {
            scene.Entities.Add(Models.MakeCube(ResourceContext, Materials.MakeChecker(ResourceContext)));
        }

        private void addCone_Click(object sender, RoutedEventArgs e) {
            scene.Entities.Add(Models.MakeCone(ResourceContext, Materials.MakeChecker(ResourceContext)));
        }

        private void addSphere_Click(object sender, RoutedEventArgs e) {
            scene.Entities.Add(Models.MakeSphere(ResourceContext, Materials.MakeChecker(ResourceContext)));
        }

        private void addPlane_Click(object sender, RoutedEventArgs e) {
            scene.Entities.Add(Models.MakePlane(ResourceContext, Materials.MakeChecker(ResourceContext)));
        }
    }
}
