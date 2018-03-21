using System;
using System.Windows.Forms;
using Ghurund.Managed.Resource;

namespace Ghurund.Editor.Editor {
    public class ResourceEditor<Type> : UserControl, IEditor where Type : IResource, new() {
        private Type resource;

        public ResourceManager resourceManager;

        public event EventHandler DocumentChanged;

        public bool WasSaved {
            get {
                return resource.FileName != null;
            }
        }

        public IResource Document {
            get {
                return resource;
            }
            set {
                resource = (Type)value;
            }
        }

        public ResourceEditor(ResourceManager resourceManager) {
            this.resourceManager = resourceManager;
        }

        public bool load(string fileName) {
            resource = new Type();
            return resource.load(resourceManager, fileName);
        }

        public void newDocument() {
            resource = new Type();
        }

        public bool saveAs(string fileName) {
            return resource.save(resourceManager, fileName);
        }

        public bool save() {
            return resource.save(resourceManager, resource.FileName);
        }

    }
}
