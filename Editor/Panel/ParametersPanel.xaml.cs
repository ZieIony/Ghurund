using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Ghurund.Controls;
using Ghurund.Controls.PropertyGrid;
using Ghurund.Controls.Workspace;
using Ghurund.Managed.Game;
using Ninject;

namespace Ghurund.Editor {
    public interface IParametersPanel : IDockableControl {
        Entity SelectedEntity { get; set; }
    }

    public partial class ParametersPanel : UserControl, IParametersPanel {
        [Inject]
        public ParameterManager ParameterManager { get; set; }

        private List<Property> managerParameters = new List<Property>();

        private bool disposed = false;

        public ParametersPanel() {
            InitializeComponent();

            EditorKernel.Instance.Inject(this);

            for (uint i = 0; i < ParameterManager.ParameterCount; i++) {
                Parameter p = ParameterManager.Get(i);
                managerParameters.Add(new Property() {
                    DisplayName = p.Name,
                    Category = "ParameterManager",
                    ValueGetter = () => p.Value
                });
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
                value?.AddReference();
                if (selectedEntity != null) {
                    selectedEntity.Release();
                    if (selectedEntity is INotifyPropertyChanged) {
                        var notificationSource = selectedEntity as INotifyPropertyChanged;
                        notificationSource.PropertyChanged -= NotificationSource_PropertyChanged;
                    }
                }

                selectedEntity = value;
                propertyGrid.Properties.Clear();
                if (selectedEntity != null) {
                    for (int i = 0; i < selectedEntity.Parameters.Count; i++) {
                        Parameter p = selectedEntity.Parameters[i];
                        if (p.NativePtr != IntPtr.Zero) {
                            propertyGrid.Properties.Add(new Property() {
                                DisplayName = p.Name,
                                Category = "Selected object",
                                ValueGetter = () => p.Value
                            });
                        }
                    }

                    if (selectedEntity is INotifyPropertyChanged) {
                        var notificationSource = selectedEntity as INotifyPropertyChanged;
                        notificationSource.PropertyChanged += NotificationSource_PropertyChanged;
                    }
                }

                foreach (Property p in managerParameters)
                    propertyGrid.Properties.Add(p);
            }
        }

        private void NotificationSource_PropertyChanged(object sender, PropertyChangedEventArgs e) {
            propertyGrid.Refresh();
        }
    }
}
