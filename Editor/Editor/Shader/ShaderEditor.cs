using System;
using System.Windows.Forms;
using Ghurund.Managed.Resource;

namespace Ghurund.Editor.Shader {
    public partial class ShaderEditor : UserControl, IEditor {
        public Managed.Shader Shader { get; private set; }
        public ResourceManager resourceManager;

        public event EventHandler DocumentChanged;

        public bool WasSaved {
            get {
                return Shader.FileName != null;
            }
        }

        public IResource Document {
            get {
                return Shader;
            }
            set {
                Shader = (Managed.Shader)value;
            }
        }

        public ShaderEditor(ResourceManager resourceManager) {
            InitializeComponent();
            this.resourceManager = resourceManager;
        }

        public bool load(string fileName) {
            Shader = new Managed.Shader();
            bool result = Shader.load(resourceManager, fileName);
            if (result)
                shaderSourceCodeTextBox.Text = Shader.SourceCode;
            return result;
        }

        public void newDocument() {
            Shader = new Managed.Shader();
        }

        private void newToolStripButton_Click(object sender, EventArgs e) => newDocument();

        private void toolStripButton1_Click(object sender, EventArgs e) {
            Shader.SourceCode = shaderSourceCodeTextBox.Text;
            String errors = Shader.compile();
            if (errors != null) {
                splitContainer1.Panel2Collapsed = false;
                errorMessagesTextBox.Text = errors;
            } else {
                splitContainer1.Panel2Collapsed = true;
            }
        }

        public bool saveAs(string fileName) {
            Shader.SourceCode = shaderSourceCodeTextBox.Text;
            return Shader.save(resourceManager, fileName);
        }

        public bool save() {
            Shader.SourceCode = shaderSourceCodeTextBox.Text;
            return Shader.save(resourceManager, Shader.FileName);
        }

        private void tabControl1_SelectedIndexChanged(object sender, EventArgs e) {
            switch (tabControl1.SelectedIndex) {
                case 0:
                    break;
                case 1:
                    shaderSourceCodeTextBox.Text = Shader.SourceCode;
                    break;
                case 2:
                    propertyGrid1.SelectedObject = Shader;
                    break;
            }
        }
    }
}
