using System.ComponentModel;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Imaging;
using Ghurund.Controls.Workspace;
using Ghurund.Editor.ResourceEditor;
using Ghurund.Managed.Game;
using Ghurund.Managed.Graphics;
using Ghurund.Managed.Resource;
using Microsoft.Win32;
using Ninject;

namespace Ghurund.Editor {
    public partial class MainWindow : Window {

        [Inject]
        public IProjectExplorerPanel ProjectExplorer { get; set; }

        [Inject]
        public IWelcomePage WelcomePage { get; set; }

        [Inject]
        public IPropertiesPanel PropertiesPanel { get; set; }

        [Inject]
        public IParametersPanel ParametersPanel { get; set; }

        [Inject]
        public IResourceManagerPanel ResourceManagerPanel { get; set; }

        [Inject]
        public ISceneExplorerPanel SceneExplorer { get; set; }

        [Inject]
        public ParameterManager ParameterManager { get; set; }

        [Inject]
        public EditorSettings Settings { get; set; }

        [Inject]
        public ResourceManager ResourceManager { get; set; }

        public MainWindow() {
            InitializeComponent();

            EditorKernel.Instance.Inject(this);

            workspacePanel.Loaded += WorkspacePanel_Loaded;
            SceneExplorer.SelectedEntityChanged += SceneExplorer_SelectedEntityChanged;

            var scene = new Scene();
            scene.Load(ResourceManager, "test.scene");
            scene.Entities.SyncList();
            //scene.Entities.Add(new Camera());
            //scene.Entities.Add(new Light());
            //scene.initParameters(ParameterManager);
            SceneExplorer.Scene = scene;
            SceneExplorer.EditorOpened += SceneExplorer_EditorOpened;

            ProjectExplorer.Project = new Project() {
                Name = "test project",
                Directory = new DirectoryInfo(Directory.GetCurrentDirectory())
            };

            ResourceManagerPanel.EditorOpened += SceneExplorer_EditorOpened;
        }

        private void SceneExplorer_EditorOpened(object sender, RoutedEditorOpenedEventArgs e) {
            if (e.EditedResource is BitmapImage) {
                var panel = new ImageEditorPanel();
                panel.Image = e.EditedResource as BitmapImage;
                openPanel(sender, panel);
            } else {
                var panel = new SceneEditorPanel();
                panel.Scene = e.EditedResource as Scene;
                openPanel(sender, panel);
            }
        }

        private void SceneExplorer_SelectedEntityChanged(object sender, RoutedPropertyChangedEventArgs<Entity> e) {
            PropertiesPanel.SelectedObject = e.NewValue;
            ParametersPanel.Parameters.Clear();
            /*for (int i = 0; i < e.NewValue.Parameters.Count; i++) {
                Parameter p = e.NewValue.Parameters[i];
                ParametersPanel.Parameters.Add(new Controls.Property() {
                    DisplayName = p.Name,
                    Value = p.Value
                });
            }*/
        }

        private void WorkspacePanel_Loaded(object sender, RoutedEventArgs e) {
            workspacePanel.Restore(Settings.WorkspaceState, new DockableControlFactory());
        }

        private void Exit_Click(object sender, RoutedEventArgs e) {
            Application.Current.Shutdown();
        }

        private void FileNew_Click(object sender, RoutedEventArgs e) {
            new EditorWindow(workspacePanel, new DockableControls(new IDockableControl[] { new ProjectExplorerPanel(), new ProjectExplorerPanel() })).Show();
        }

        private void ProjectExplorer_Click(object sender, RoutedEventArgs e) => openPanel(sender, ProjectExplorer);
        private void WelcomePage_Click(object sender, RoutedEventArgs e) => openPanel(sender, WelcomePage);
        private void Properties_Click(object sender, RoutedEventArgs e) => openPanel(sender, PropertiesPanel);
        private void Parameters_Click(object sender, RoutedEventArgs e) => openPanel(sender, ParametersPanel);
        private void ResourceManager_Click(object sender, RoutedEventArgs e) => openPanel(sender, ResourceManagerPanel);
        private void SceneExplorer_Click(object sender, RoutedEventArgs e) => openPanel(sender, SceneExplorer);

        private void openPanel(object sender, IDockableControl panel) {
            new EditorWindow(workspacePanel, panel).Show();
        }

        protected override void OnClosing(CancelEventArgs e) {
            base.OnClosing(e);
            saveSettings();
        }

        private void btnOpenFile_Click(object sender, RoutedEventArgs e) {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            /*if (openFileDialog.ShowDialog() == true)
                txtEditor.Text = File.ReadAllText(openFileDialog.FileName);*/
        }

        private void saveSettings() {
            Settings.WorkspaceState = workspacePanel.Save();
            Settings.WriteToBinaryFile(EditorSettings.EDITOR_SETTINGS_FILE_NAME);
        }
    }

}
