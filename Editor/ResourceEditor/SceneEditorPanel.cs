using System;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Xml.Serialization;
using Ghurund.Controls.Workspace;
using Ghurund.Editor.Panel;
using Ghurund.Managed;
using Ghurund.Managed.Game;
using Ghurund.Managed.Graphics;
using Ghurund.Managed.Resource;
using Microsoft.Win32;
using Ninject;

namespace Ghurund.Editor.ResourceEditor {
    [Serializable]
    public class SceneEditorState {
        public string FileName { get; set; }
    }

    public interface ISceneEditor : IDockablePanel {
        Scene Scene { get; set; }

        event RoutedPropertyChangedEventHandler<object> SelectionChanged;
    }

    public partial class SceneEditorPanel : UserControl, ISceneEditor, IStateControl, IEditorPanel {

        public static readonly RoutedEvent SelectionChangedEvent = EventManager.RegisterRoutedEvent("SelectionChanged", RoutingStrategy.Bubble, typeof(RoutedPropertyChangedEventHandler<object>), typeof(SceneEditorPanel));

        public event RoutedPropertyChangedEventHandler<object> SelectionChanged {
            add { AddHandler(SelectionChangedEvent, value); }
            remove { RemoveHandler(SelectionChangedEvent, value); }
        }

        [Inject]
        public ResourceManager ResourceManager { get; set; }

        [Inject]
        public ResourceContext ResourceContext { get; set; }

        [Inject]
        public ParameterManager ParameterManager { get; set; }

        [Inject]
        public StatisticsPanel StatisticsPanel { get; set; }

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

        public bool NeedsSaving => false;

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
            StatisticsPanel.SelectedObject = sceneView.Renderer.Statistics;

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

        public bool Save(string fileName = null) {
            if (fileName == null && Scene.FileName == null) {
                SaveFileDialog saveFileDialog = new SaveFileDialog();
                var result = saveFileDialog.ShowDialog();
                if (!result.GetValueOrDefault(false))
                    return false;
                fileName = saveFileDialog.FileName;
            }
            return Scene.Save(ResourceManager, fileName) == Status.OK;
        }

        public bool Load(string fileName) {
            Scene = new Scene();
            if (Scene.Load(ResourceManager, ResourceContext, fileName) != Status.OK)
                return false;
            Scene.InitParameters(ParameterManager);
            return true;
        }

        public void SaveState(Stream stream) {
            SceneEditorState state = new SceneEditorState {
                FileName = Scene.FileName
            };
            XmlSerializer serializer = new XmlSerializer(typeof(SceneEditorState));
            serializer.Serialize(stream, state);
        }

        public void RestoreState(Stream stream) {
            XmlSerializer serializer = new XmlSerializer(typeof(SceneEditorState));
            SceneEditorState state = serializer.Deserialize(stream) as SceneEditorState;
            Load(state.FileName);
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
