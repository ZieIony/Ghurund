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

        [Inject]
        public ResourceManager ResourceManager { get; set; }

        private List<object> selectedItems = new List<object>();
        public List<object> SelectedItems {
            get => selectedItems;
            set {
                if (selectedItems == value)
                    return;
                selectedItems = value;
                if (selectedItems == null)
                    return;
                foreach (var item in selectedItems) {
                    if (item is Scene)
                        Scene = item as Scene;
                }
            }
        }

        public static readonly RoutedEvent SelectionChangedEvent = EventManager.RegisterRoutedEvent("SelectionChanged", RoutingStrategy.Bubble, typeof(RoutedSelectionChangedEventHandler), typeof(ISceneExplorerPanel));

        public event RoutedSelectionChangedEventHandler SelectionChanged {
            add { AddHandler(SelectionChangedEvent, value); }
            remove { RemoveHandler(SelectionChangedEvent, value); }
        }


        private bool disposed = false;

        public SceneExplorerPanel() {
            InitializeComponent();

            EditorKernel.Instance.Inject(this);

            content.Visibility = Visibility.Collapsed;
            hint.Visibility = Visibility.Visible;

            geometryComboBox.Items.Add(GeometryType.Cube);
            geometryComboBox.Items.Add(GeometryType.Cone);
            geometryComboBox.Items.Add(GeometryType.Sphere);
            geometryComboBox.Items.Add(GeometryType.Plane);
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
            RaiseEvent(new RoutedSelectionChangedEventArgs(SelectedItems, SelectionChangedEvent));
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

        private void geometryComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            switch(geometryComboBox.SelectedItem){
                case GeometryType.Cube:
                    scene.Entities.Add(Models.MakeCube(ResourceContext, Materials.MakeChecker(ResourceManager, ResourceContext)));
                    break;
                case GeometryType.Cone:
                    scene.Entities.Add(Models.MakeCone(ResourceContext, Materials.MakeChecker(ResourceManager, ResourceContext)));
                    break;
                case GeometryType.Sphere:
                    scene.Entities.Add(Models.MakeSphere(ResourceContext, Materials.MakeChecker(ResourceManager, ResourceContext)));
                    break;
                case GeometryType.Plane:
                    scene.Entities.Add(Models.MakePlane(ResourceContext, Materials.MakeChecker(ResourceManager, ResourceContext)));
                    break;
            }
        }
    }
}
