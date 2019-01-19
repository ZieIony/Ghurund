using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using Ghurund.Controls.Workspace;
using Ghurund.Managed;
using Ghurund.Managed.Game;
using Ghurund.Managed.Graphics;
using Ghurund.Managed.Resource;
using Ninject;

namespace Ghurund.Editor.ResourceEditor {
    public interface ISceneEditor : IDockableControl {
        Scene Scene { get; set; }
    }

    public partial class SceneEditorPanel : UserControl, ISceneEditor, IStateControl {

        [Inject]
        public ResourceManager ResourceManager { get; set; }

        [Inject]
        public ResourceContext ResourceContext { get; set; }

        private Material checkerMaterial;
        private Material wireframeMaterial;
        private Material normalsMaterial;

        public Scene Scene {
            get => sceneView.Scene;
            set {
                sceneView.Scene = value;
                Title = new Title(value.FileName.Substring(value.FileName.LastIndexOfAny(new char[] { '\\', '/' }) + 1), value.FileName);
            }
        }

        public ImageSource Icon { get; }
        public Control Control { get => this; }
        public Title Title { get; private set; }

        public SceneEditorPanel() {
            InitializeComponent();

            EditorKernel.Instance.Inject(this);

            cameraPicker.Items.Add(CameraMode.Default);
            cameraPicker.Items.Add(CameraMode.Side);
            cameraPicker.Items.Add(CameraMode.Front);
            cameraPicker.Items.Add(CameraMode.Top);

            checkerMaterial = Materials.MakeChecker(ResourceManager, ResourceContext);
            wireframeMaterial = Materials.MakeWireframe(ResourceManager, ResourceContext);
            normalsMaterial = Materials.MakeNormals(ResourceManager, ResourceContext);

            sceneView.Init(ResourceManager, ResourceContext);

            cameraPicker.SelectedValue = CameraMode.Default;
        }

        private bool disposed = false;

        ~SceneEditorPanel() {
            Dispose(false);
        }

        public void Dispose() {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing) {
            if (disposed)
                return;

            sceneView.Uninit();

            checkerMaterial.Dispose();
            wireframeMaterial.Dispose();
            normalsMaterial.Dispose();

            disposed = true;
        }

        public object Save() {
            return Scene?.FileName;
        }

        public void Restore(object state) {
            if (state != null) {
                string fileName = state as string;
                Scene = new Scene();
                Scene.Load(ResourceManager, ResourceContext, fileName);
            }
        }

        private void Material_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            if (sceneView == null)
                return;
            switch ((material.SelectedItem as ComboBoxItem).Name) {
                case "shaded":
                    sceneView.OverrideMaterial = null;
                    break;
                case "wireframe":
                    sceneView.OverrideMaterial = wireframeMaterial;
                    break;
                case "checker":
                    sceneView.OverrideMaterial = checkerMaterial;
                    break;
                case "normals":
                    sceneView.OverrideMaterial = normalsMaterial;
                    break;
            }
            sceneView.Refresh();
        }

        private void Perspective_Checked(object sender, RoutedEventArgs e) {
            if (sceneView == null)
                return;
            sceneView.Camera.Perspective = cameraPerspective.IsChecked.Value;
            sceneView.Refresh();
        }

        private void Orbit_Checked(object sender, RoutedEventArgs e) {
            if (sceneView == null)
                return;
            sceneView.NavigationMode = NavigationMode.Orbit;
        }

        private void Rotate_Checked(object sender, RoutedEventArgs e) {
            sceneView.NavigationMode = NavigationMode.Rotate;
        }

        private void Pan_Checked(object sender, RoutedEventArgs e) {
            sceneView.NavigationMode = NavigationMode.Pan;
        }

        private void Zoom_Checked(object sender, RoutedEventArgs e) {
            sceneView.NavigationMode = NavigationMode.Zoom;
        }

        private void ResetCamera_Click(object sender, RoutedEventArgs e) {
            sceneView.ResetCamera();
            cameraPerspective.IsChecked = sceneView.Camera.Perspective;
            sceneView.Refresh();
        }

        private void Camera_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            sceneView.CameraMode = ((CameraMode?)cameraPicker.SelectedValue) ?? CameraMode.Default;
            cameraPerspective.IsChecked = sceneView.Camera.Perspective;
            sceneView.Refresh();
        }

        private void Button_Click(object sender, RoutedEventArgs e) {
            RaiseEvent(new RoutedPropertyChangedEventArgs<Entity>(null, sceneView.Camera, SceneExplorerPanel.SelectedEntityChangedEvent));
        }
    }
}
