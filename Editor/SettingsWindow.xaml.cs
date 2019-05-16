using System.Windows;
using Ghurund.Controls.Workspace;
using Ghurund.Editor.Property;
using Ninject;

namespace Ghurund.Editor {
    public partial class SettingsWindow : Window {

        [Inject]
        public EditorSettings Settings { get; set; }

        public SettingsWindow() {
            InitializeComponent();

            EditorKernel.Inject(this);

            propertyGrid.PropertyEditorFactory = new PropertyEditorFactory();
            propertyGrid.SelectedObject = Settings;

            ThemeResourceDictionary.ApplyTheme(this, Settings.Theme);
        }
    }
}
