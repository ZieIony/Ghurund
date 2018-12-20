using System;
using System.ComponentModel;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Imaging;
using Ghurund.Controls.Workspace;
using Ghurund.Editor.ResourceEditor;
using Ghurund.Managed;
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
        public ILogPanel LogPanel { get; set; }

        [Inject]
        public ParameterManager ParameterManager { get; set; }

        [Inject]
        public EditorSettings Settings { get; set; }

        [Inject]
        public ResourceManager ResourceManager { get; set; }

        [Inject]
        public ResourceContext ResourceContext { get; set; }

        public MainWindow() {
            InitializeComponent();

            EditorKernel.Instance.Inject(this);

            workspacePanel.Loaded += WorkspacePanel_Loaded;
            SceneExplorer.SelectedEntityChanged += SceneExplorer_SelectedEntityChanged;

            SceneExplorer.EditorOpened += SceneExplorer_EditorOpened;

            ProjectExplorer.Project = new Project() {
                Name = "test project",
                Directory = new DirectoryInfo(Directory.GetCurrentDirectory())
            };

            ResourceManagerPanel.EditorOpened += SceneExplorer_EditorOpened;
        }

        private void SceneExplorer_EditorOpened(object sender, RoutedEditorOpenedEventArgs e) {
            openResource(e.EditedResource);
        }

        private void openResource(ResourceFile resourceFile) {
            IDockableControl panel = null;
            var path = resourceFile.Path.ToLower();

            if (path.EndsWith("jpg") || path.EndsWith("jpeg") || path.EndsWith("png")) {
                BitmapImage image = new BitmapImage(new Uri(resourceFile.Path));
                panel = new ImageEditorPanel {
                    Image = image
                };
            } else if (path.EndsWith("scene")) {
                var scene = new Scene();
                if (Status.OK == scene.Load(ResourceManager, ResourceContext, resourceFile.Path)) {
                    panel = new SceneEditorPanel {
                        Scene = scene
                    };
                } else {
                    // TODO: show error message
                    return;
                }
            } else {
                // TODO: show error message
                return;
            }

            Settings.RecentFiles.Add(resourceFile);
            openPanel(this, panel);
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
        private void LogPanel_Click(object sender, RoutedEventArgs e) => openPanel(sender, LogPanel);

        private void openPanel(object sender, IDockableControl panel) {
            new EditorWindow(workspacePanel, panel).Show();
        }

        protected override void OnClosing(CancelEventArgs e) {
            base.OnClosing(e);
            saveSettings();

            ParameterManager.Dispose();
            ResourceManager.Dispose();
            ResourceContext.Dispose();
        }

        private void FileOpen_Click(object sender, RoutedEventArgs e) {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Images (*.jpg; *.jpeg; *.png)|*.jpg;*.jpeg;*.png|Scenes (*.scene)|*.scene";
            if (openFileDialog.ShowDialog() == true)
                openResource(new ResourceFile(new FileInfo(openFileDialog.FileName)));
        }

        private void saveSettings() {
            Settings.WorkspaceState = workspacePanel.Save();
            Settings.WriteToBinaryFile(EditorSettings.EDITOR_SETTINGS_FILE_NAME);
        }

    }

}
