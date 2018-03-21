using System;
using System.Windows.Forms;
using Ghurund.Managed.Resource;

namespace Ghurund.Editor.Material {
    public partial class MaterialEditor : UserControl, IEditor {
        private readonly ResourceManager resourceManager;
        private Ghurund.Managed.Material material;

        public MaterialEditor(ResourceManager resourceManager) {
            InitializeComponent();
            this.resourceManager = resourceManager;
        }

        public bool WasSaved {
            get {
                return material.FileName != null;
            }
        }

        public IResource Document { get => material; set => material = (Ghurund.Managed.Material)value; }

        public event EventHandler DocumentChanged;

        public bool load(string fileName) {
            throw new NotImplementedException();
        }

        public void newDocument() {
            material = new Ghurund.Managed.Material();
            propertyGrid1.SelectedObject = material;
        }

        public bool save() {
            return material.save(resourceManager, material.FileName);
        }

        public bool saveAs(string fileName) {
            return material.save(resourceManager, fileName);
        }
    }
}
