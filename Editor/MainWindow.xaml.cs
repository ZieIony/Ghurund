using System;
using System.ComponentModel;
using System.IO;
using System.Windows;
using Ghurund.Controls.Workspace;
using Ghurund.Editor.Panel;
using Ghurund.Editor.ResourceEditor;
using Ghurund.Managed;
using Ghurund.Managed.Game;
using Ghurund.Managed.Resource;
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
        public IStatisticsPanel StatisticsPanel { get; set; }

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

        private System.Collections.Generic.List<IDocumentPanel> documentPanels = new System.Collections.Generic.List<IDocumentPanel>();

        public MainWindow() {
            InitializeComponent();

            EditorKernel.Instance.Inject(this);

            removeInvalidRecents();

            workspacePanel.Loaded += WorkspacePanel_Loaded;
            Width = Settings.WindowSize.Width != 0 ? Settings.WindowSize.Width : 800;
            Height = Settings.WindowSize.Height != 0 ? Settings.WindowSize.Height : 600;

            if (Settings.ReopenMostRecentProject && Settings.RecentProjects.Count > 0) {
                // TODO: reopen project
                string path = Settings.RecentProjects[0];
                Project project = Controls.Workspace.Extensions.ReadFromBinaryFile<Project>(path);
                ProjectExplorer.Project = project;
            }

            AddHandler(ActionPerformedEvent, new RoutedActionPerformedEventHandler(actionPerformedHandler));
            AddHandler(FileOpenedEvent, new RoutedFileOpenedEventHandler(fileOpenedHandler));

            AddHandler(TitleBar.WindowDraggedEvent, new WindowEventHandler(titleBar_WindowDragged));
            AddHandler(TitleBar.WindowActionEvent, new WindowActionEventHandler(titleBar_WindowAction));

            AddHandler(SceneEditorPanel.SelectionChangedEvent, new RoutedSelectionChangedEventHandler(selectionChangedHandler));
            AddHandler(SceneExplorerPanel.SelectionChangedEvent, new RoutedSelectionChangedEventHandler(selectionChangedHandler));
            AddHandler(WorkspacePanel.PanelFocusedEvent, new PanelActionEventHandler(panelFocused));
        }

        IDocumentPanel mostRecentDocumentPanel;
        IToolPanel mostRecentToolPanel;
        TabControl mostRecentDocumentTabControl, mostRecentToolTabControl;

        private void panelFocused(object sender, PanelActionEventArgs args) {
            if (args.Panel.Content is IDocumentPanel || args.Panel.Content is WelcomePage) {
                mostRecentDocumentPanel = args.Panel.Content as IDocumentPanel;
                mostRecentDocumentTabControl = args.TabControl;
            } else if (args.Panel.Content is IToolPanel) {
                mostRecentToolPanel = args.Panel.Content as IToolPanel;
                mostRecentToolTabControl = args.TabControl;
            }

            if(args.Panel.Content is ISceneEditor) {
                var editor = args.Panel.Content as ISceneEditor;
                SceneExplorer.Scene = editor.Scene;
            }
        }

        private void selectionChangedHandler(object sender, RoutedSelectionChangedEventArgs e) {
            foreach (var documentPanel in documentPanels)
                documentPanel.SelectedItems = e.Items;
            SceneExplorer.SelectedItems = e.Items;
            PropertiesPanel.SelectedItems = e.Items;
            ParametersPanel.SelectedItems = e.Items;
            //ProjectExplorer.SelectedItems = e.NewValue;
        }

        private void removeInvalidRecents() {
            System.Collections.Generic.List<string> recentFiles = new System.Collections.Generic.List<string>();
            foreach (string file in Settings.RecentFiles) {
                if (File.Exists(file))
                    recentFiles.Add(file);
            }
            Settings.RecentFiles.Clear();
            Settings.RecentFiles.AddRange(recentFiles);

            System.Collections.Generic.List<string> recentProjects = new System.Collections.Generic.List<string>();
            foreach (string file in Settings.RecentProjects) {
                if (File.Exists(file))
                    recentProjects.Add(file);
            }
            Settings.RecentProjects.Clear();
            Settings.RecentProjects.AddRange(recentProjects);
        }

        private void WorkspacePanel_Loaded(object sender, RoutedEventArgs e) {
            workspacePanel.Restore(Settings.WorkspaceState, new DockableControlFactory());
        }

        private void Exit_Click(object sender, RoutedEventArgs e) {
            Application.Current.Shutdown();
        }

        private void ProjectExplorer_Click(object sender, RoutedEventArgs e) => openPanel(sender, ProjectExplorer);
        private void WelcomePage_Click(object sender, RoutedEventArgs e) => openPanel(sender, WelcomePage);
        private void Properties_Click(object sender, RoutedEventArgs e) => openPanel(sender, PropertiesPanel);
        private void Parameters_Click(object sender, RoutedEventArgs e) => openPanel(sender, ParametersPanel);
        private void ResourceManager_Click(object sender, RoutedEventArgs e) => openPanel(sender, ResourceManagerPanel);
        private void SceneExplorer_Click(object sender, RoutedEventArgs e) => openPanel(sender, SceneExplorer);
        private void StatisticsPanel_Click(object sender, RoutedEventArgs e) => openPanel(sender, StatisticsPanel);
        private void LogPanel_Click(object sender, RoutedEventArgs e) => openPanel(sender, LogPanel);

        private void openPanel(object sender, IDockablePanel panel) {
            // TODO: what if panel is no longer visible?
            if (mostRecentDocumentTabControl != null && panel is IDocumentPanel) {
                var item = new EditorTab(panel);
                mostRecentDocumentTabControl.Items.Add(item);
                mostRecentDocumentTabControl.SelectedItem = item;
            } else if (mostRecentToolTabControl != null && panel is IToolPanel) {
                var item = new EditorTab(panel);
                mostRecentToolTabControl.Items.Add(item);
                mostRecentToolTabControl.SelectedItem = item;
            } else {
                new EditorWindow(workspacePanel, panel).Show();
            }
        }

        protected override void OnClosing(CancelEventArgs e) {
            base.OnClosing(e);
            saveSettings();

            ParameterManager.Dispose();
            ResourceManager.Dispose();
            ResourceContext.Dispose();
        }

        private string makeFilter(string name, Array<ResourceFormat> formats) {
            string filter = "";
            foreach (ResourceFormat format in formats) {
                if (filter.Length > 0)
                    filter += ";";
                filter += "*." + format.Extension;
            }
            return name + " (" + filter + ")|" + filter;
        }

        private void FileOpen_Click(object sender, RoutedEventArgs e) {
            openFile();
        }

        private void Settings_Click(object sender, RoutedEventArgs e) {
            new SettingsWindow().Show();
        }

        private void saveSettings() {
            Settings.WindowSize = new Size(Width, Height);
            Settings.WorkspaceState = workspacePanel.Save();
            Settings.WriteToBinaryFile(EditorSettings.EDITOR_SETTINGS_FILE_NAME);
        }
    }

}
