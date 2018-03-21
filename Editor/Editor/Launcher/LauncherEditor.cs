using Ghurund.Managed;
using Ghurund.Managed.Resource;
using System;
using System.Diagnostics;
using System.IO;
using System.Windows.Forms;

namespace Ghurund.Editor.Editor.Launcher {
    public partial class LauncherEditor : UserControl, IEditor {
        private LauncherSettings resource;

        public ResourceManager resourceManager;

        public event EventHandler DocumentChanged;

        public bool WasSaved { get; private set; }

        public IResource Document {
            get {
                return resource;
            }
            set {
                resource = (LauncherSettings)value;
            }
        }

        public LauncherEditor() {
            InitializeComponent();
        }

        public bool load(string fileName) {
            resource = new LauncherSettings();
            bool result = resource.load(resourceManager, fileName);
            if (result) {
                propertyGrid1.SelectedObject = resource.Data;
                WasSaved = true;
            }
            return result;
        }

        public void newDocument() {
            resource = new LauncherSettings();
            propertyGrid1.SelectedObject = resource.Data;
            WasSaved = false;
        }

        public bool saveAs(string fileName) {
            WasSaved = resource.save(resourceManager, fileName);
            //if(WasSaved)
            //Tex
            return WasSaved;
        }

        public bool save() {
            return WasSaved = resource.save(resourceManager, resource.FileName);
        }

        private void toolStripButton1_Click(object sender, System.EventArgs e) {
            save();
            File.Copy(resource.FileName, "launcher." + resource.DefaultExtension, true);
            Process.Start("Launcher.exe");
        }
    }
}
