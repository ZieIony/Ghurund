using System;
using System.Windows.Controls;
using System.Windows.Media;
using Ghurund.Controls.Workspace;
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
            set => sceneView.Scene = value;
        }

        public ImageSource Icon { get; }
        public Control Control { get => this; }
        public Title Title { get; } = new Title("Scene");

        public SceneEditorPanel() {
            InitializeComponent();

            EditorKernel.Instance.Inject(this);

            checkerMaterial = Materials.makeChecker(ResourceManager, ResourceContext);
            wireframeMaterial = Materials.MakeWireframe(ResourceManager, ResourceContext);
            normalsMaterial = Materials.MakeNormals(ResourceManager, ResourceContext);

            sceneView.Init(ResourceManager, ResourceContext);
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
                    sceneView.Renderer.Material = null;
                    break;
                case "wireframe":
                    sceneView.Renderer.Material = wireframeMaterial;
                    break;
                case "checker":
                    sceneView.Renderer.Material = checkerMaterial;
                    break;
                case "normals":
                    sceneView.Renderer.Material = normalsMaterial;
                    break;
            }
            sceneView.Refresh();
        }

        private void Perspective_Checked(object sender, System.Windows.RoutedEventArgs e) {
            if (sceneView == null)
                return;
            sceneView.Camera.Perspective = cameraPerspective.IsChecked.Value;
            sceneView.Refresh();
        }
    }
}
