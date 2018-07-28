using System.ComponentModel;
using System.IO;
using System.Windows;
using Ghurund.Controls.Workspace;
using Ghurund.Managed.Game;
using Ghurund.Managed.Graphics;
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
        public IResourceManagerPanel ResourceManager { get; set; }

        [Inject]
        public ISceneExplorerPanel SceneExplorer { get; set; }

        [Inject]
        public ParameterManager ParameterManager { get; set; }

        [Inject]
        public EditorSettings settings { get; set; }

        public MainWindow() {
            InitializeComponent();

            EditorKernel.Instance.Inject(this);

            workspacePanel.Loaded += WorkspacePanel_Loaded;
            SceneExplorer.SelectedEntityChanged += SceneExplorer_SelectedEntityChanged;

            var scene = new Scene();
            scene.Entities.Add(new Camera());
            scene.Entities.Add(new Light());
            scene.initParameters(ParameterManager);
            SceneExplorer.Scene = scene;

            ProjectExplorer.Project = new Project() {
                Name = "test project",
                Directory = new DirectoryInfo(Directory.GetCurrentDirectory())
            };
        }

        private void SceneExplorer_SelectedEntityChanged(object sender, RoutedPropertyChangedEventArgs<Entity> e) {
            PropertiesPanel.SelectedObject = e.NewValue;
            ParametersPanel.Parameters.Clear();
            for (int i = 0; i < e.NewValue.Parameters.Count; i++) {
                Parameter p = e.NewValue.Parameters[i];
                ParametersPanel.Parameters.Add(new Controls.Property() {
                    DisplayName = p.Name,
                    Value = p.Value
                });
            }
        }

        private void WorkspacePanel_Loaded(object sender, RoutedEventArgs e) {
            workspacePanel.Restore(settings.WorkspaceState, new DockableControlFactory());
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
        private void ResourceManager_Click(object sender, RoutedEventArgs e) => openPanel(sender, ResourceManager);
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
            settings.WorkspaceState = workspacePanel.Save();
            settings.WriteToBinaryFile(EditorSettings.EDITOR_SETTINGS_FILE_NAME);
        }
    }

}
