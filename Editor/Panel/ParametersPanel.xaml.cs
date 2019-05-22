using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Ghurund.Controls;
using Ghurund.Controls.PropertyGrid;
using Ghurund.Controls.Workspace;
using Ghurund.Editor.Property;
using Ghurund.Managed.Game;
using Ninject;

namespace Ghurund.Editor {
    public interface IParametersPanel: IToolPanel {
        Entity SelectedEntity { get; set; }
    }

    public partial class ParametersPanel: UserControl, IParametersPanel {

        private readonly List<object> selectedItems = new List<object>();
        public List<object> SelectedItems {
            get => selectedItems;
            set {
                selectedItems.Clear();
                selectedItems.AddRange(value);
                for (int i = selectedItems.Count - 1; i >= 0; i--) {
                    var item = selectedItems[i];
                    if (item is Entity) {
                        SelectedEntity = item as Entity;
                        break;
                    }
                }
            }
        }

        [Inject]
        public ParameterManager ParameterManager { get; set; }

        private bool disposed = false;

        public ParametersPanel() {
            InitializeComponent();

            EditorKernel.Inject(this);

            propertyGrid.PropertyEditorFactory = new PropertyEditorFactory();

            SelectedEntity = null;
            propertyGrid.AddParameters(ParameterManager.Parameters, "ParameterManager");
        }

        ~ParametersPanel() {
            Dispose(false);
        }

        public void Dispose() {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing) {
            if (disposed)
                return;

            // don't dispose parameter manager - this panel doesn't own it

            disposed = true;
        }

        public ImageSource Icon { get; } = new BitmapImage(new Uri("pack://application:,,,/Resources/icons/properties32.png", UriKind.Absolute));
        public Control Control { get => this; }
        public Title Title { get; } = new Title("Parameters");

        private Entity selectedEntity;
        public Entity SelectedEntity {
            get => selectedEntity;
            set {
                if (selectedEntity == value)
                    return;

                value?.AddReference();
                selectedEntity?.Release();

                selectedEntity = value;
                propertyGrid.Properties.Clear();
                if (selectedEntity != null)
                    propertyGrid.AddParameters(selectedEntity.Parameters, "Selected object");

                propertyGrid.AddParameters(ParameterManager.Parameters, "ParameterManager");
            }
        }

    }
}
