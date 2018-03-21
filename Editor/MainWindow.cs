using System.Windows.Forms;
using Ghurund.Editor.Editor.Launcher;
using Ghurund.Editor.Material;
using Ghurund.Editor.Shader;

namespace Ghurund.Editor {
    public partial class MainWindow : Form {
        public Managed.Resource.ResourceManager ResourceManager { get; private set; }
        public Managed.Graphics.Graphics Graphics { get; private set; }
        public Managed.Game.ParameterManager ParameterManager { get; private set; }

        public MainWindow() {
            InitializeComponent();
            Graphics = new Managed.Graphics.Graphics();
            Graphics.init();
            ParameterManager = new Managed.Game.ParameterManager(Graphics);
            ResourceManager = new Managed.Resource.ResourceManager(Graphics, ParameterManager);
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

    }
}
