using System.Windows.Forms;
using Ghurund.Editor.Editor.Launcher;
using Ghurund.Editor.Material;
using Ghurund.Editor.Shader;
using Ghurund.Managed.Game;
using Ghurund.Managed.Graphics;

namespace Ghurund.Editor {
    public partial class MainWindow : Form {
        public Managed.Resource.ResourceManager ResourceManager { get; private set; }
        public Graphics Graphics { get; private set; }
        public ParameterManager ParameterManager { get; private set; }

        PropertyGrid propertyGrid1 = new PropertyGrid();

        public MainWindow() {
            InitializeComponent();
            Graphics = new Graphics();
            ParameterManager = new ParameterManager(Graphics);
            ResourceManager = new Managed.Resource.ResourceManager(Graphics, ParameterManager);

            outlinePanel1.Entities.Add(new Camera());
            outlinePanel1.Entities.Add(new Light());

            outlinePanel1.SelectionChanged += OutlinePanel1_SelectionChanged;

            collapsedPagesContainer1.dock(propertyGrid1, Docking.DockSide.Center);
        }

        private void OutlinePanel1_SelectionChanged(object sender, Control.Outline.SelectionChangedEventArgs<Control.Outline.EntityTreeNode> e) {
            propertyGrid1.SelectedObject = e.Value.Entity;
        }

        private void newMaterialDocument_Click(object sender, System.EventArgs e) {
            newWindow(new MaterialEditor(ResourceManager));
        }

        private void newShaderDocument_Click(object sender, System.EventArgs e) {
            newWindow(new ShaderEditor(ResourceManager));
        }

        private void newLauncherDocument_Click(object sender, System.EventArgs e) {
            newWindow(new LauncherEditor());
        }

        private void newWindow(IEditor editor) {
            EditorWindow editorWindow = new EditorWindow(editor);
            editorWindow.Activated += EditorWindow_Activated;
            editorWindow.Show();
        }

        private void EditorWindow_Activated(object sender, System.EventArgs e) {
            toolStripStatusLabel1.Text = sender.ToString();
        }

        private void toolStripButton1_Click(object sender, System.EventArgs e) {
            new GraphicsSettings(Graphics).Show();
        }
    }
}
