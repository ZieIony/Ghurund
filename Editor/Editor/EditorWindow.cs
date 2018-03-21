using System.Windows.Forms;
using Ghurund.Managed.Resource;

namespace Ghurund.Editor {
    public partial class EditorWindow : Form {
        private IEditor editor;

        public EditorWindow(IEditor editor) {
            InitializeComponent();
            this.editor = editor;
            editor.DocumentChanged += Editor_DocumentChanged;
            System.Windows.Forms.Control editorControl = editor as System.Windows.Forms.Control;
            editorControl.Dock = DockStyle.Fill;
            panel1.Controls.Add(editorControl);
            newDocument();
        }

        private void Editor_DocumentChanged(object sender, System.EventArgs e) {
            Text = editor.Document.FileName;
        }

        private void newToolStripMenuItem_Click(object sender, System.EventArgs e) => newDocument();

        private void newDocument() {
            editor.newDocument();
        }

        private void openToolStripMenuItem_Click(object sender, System.EventArgs e) {
            openFileDialog1.ShowDialog(this);
        }

        private void saveFileDialog1_FileOk(object sender, System.ComponentModel.CancelEventArgs e) {
            editor.saveAs(saveFileDialog1.FileName);
        }

        private void openFileDialog1_FileOk(object sender, System.ComponentModel.CancelEventArgs e) {
            editor.load(openFileDialog1.FileName);
        }

        private void saveToolStripMenuItem_Click(object sender, System.EventArgs e) {
            if (editor.WasSaved) {
                editor.save();
            } else {
                saveAsToolStripMenuItem_Click(sender, e);
            }
        }

        private void saveAsToolStripMenuItem_Click(object sender, System.EventArgs e) {
            saveFileDialog1.ShowDialog(this);
        }
    }
}
