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
using Ghurund.Managed.Game;
using Ninject;

namespace Ghurund.Editor {
    public interface IParametersPanel: IToolPanel {
        Entity SelectedEntity { get; set; }
    }

    public partial class ParametersPanel: UserControl, IParametersPanel {

        private List<object> selectedItems = new List<object>();
        public List<object> SelectedItems {
            get => selectedItems;
            set {
                selectedItems = value;
                if (selectedItems == null)
                    return;
                for (int i = selectedItems.Count - 1; i >= 0; i--) {
                    var item = selectedItems[i];
                    if (item is Entity) {
                        SelectedEntity = item as Entity;
                        break;
                    }
                }
            }
        }

        public static readonly RoutedEvent SelectionChangedEvent = EventManager.RegisterRoutedEvent("SelectionChanged", RoutingStrategy.Bubble, typeof(RoutedSelectionChangedEventHandler), typeof(IParametersPanel));

        public event RoutedSelectionChangedEventHandler SelectionChanged {
            add { AddHandler(SelectionChangedEvent, value); }
            remove { RemoveHandler(SelectionChangedEvent, value); }
        }


        [Inject]
        public ParameterManager ParameterManager { get; set; }

        private List<Property> managerParameters = new List<Property>();

        private bool disposed = false;

        public ParametersPanel() {
            InitializeComponent();

            EditorKernel.Instance.Inject(this);

            for (uint i = 0; i < ParameterManager.ParameterCount; i++) {
                Parameter p = ParameterManager.Get(i);
                var property = new Property(p) {
                    DisplayName = p.Name,
                    Category = "ParameterManager"
                };
                property.Value.Getter = () => p.Value;
                switch (p.Type) {
                    case (ParameterType.Float):
                        property.Value.Editor = new FloatPropertyEditor();
                        property.Value.Setter = v => p.Value = v;
                        break;
                    case (ParameterType.Float3):
                        property.Value.Editor = new Float3PropertyEditor();
                        property.Value.Setter = v => p.Value = v;
                        break;
                    case (ParameterType.Color):
                        property.Value.Editor = new ColorPropertyEditor();
                        property.Value.Setter = v => p.Value = v;
                        break;
                }
                managerParameters.Add(property);
            }

            foreach (Property p in managerParameters)
                propertyGrid.Properties.Add(p);
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

        public ImageSource Icon { get; } = new BitmapImage(new Uri("pack://application:,,,/Resources/properties32.png", UriKind.Absolute));
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
                if (selectedEntity != null) {
                    for (int i = 0; i < selectedEntity.Parameters.Count; i++) {
                        Parameter p = selectedEntity.Parameters[i];
                        if (p != null) {
                            var property = new Property(p) {
                                DisplayName = p.Name,
                                Category = "Selected object"
                            };
                            property.Value.Getter = () => p.Value;
                            propertyGrid.Properties.Add(property);
                        }
                    }
                }

                foreach (Property p in managerParameters)
                    propertyGrid.Properties.Add(p);
            }
        }
    }
}
