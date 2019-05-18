using Ninject;
using System.Diagnostics;
using System.Windows.Input;

namespace Ghurund.Editor {
    public partial class MainWindow {

        private void SettingsCommand_Executed(object sender, ExecutedRoutedEventArgs e) {
            var window = new SettingsWindow();
            window.Owner = this;
            window.Show();
        }


        private void ProjectExplorerCommand_Executed(object sender, ExecutedRoutedEventArgs e) => openPanel(sender, ProjectExplorer);

        private void SceneExplorerCommand_Executed(object sender, ExecutedRoutedEventArgs e) => openPanel(sender, SceneExplorer);

        private void PropertiesCommand_Executed(object sender, ExecutedRoutedEventArgs e) => openPanel(sender, PropertiesPanel);

        private void ParametersCommand_Executed(object sender, ExecutedRoutedEventArgs e) => openPanel(sender, ParametersPanel);

        private void LibrariesCommand_Executed(object sender, ExecutedRoutedEventArgs e) => openPanel(sender, LibrariesPanel);

        private void StatisticsCommand_Executed(object sender, ExecutedRoutedEventArgs e) => openPanel(sender, StatisticsPanel);

        private void LogsCommand_Executed(object sender, ExecutedRoutedEventArgs e) => openPanel(sender, LogPanel);


        [Inject]
        public ColorPickerWindow ColorPicker { get; set; }

        private void ColorPickerCommand_Executed(object sender, ExecutedRoutedEventArgs e) {
            ColorPicker.Show();
        }


        private void HelpCommand_Executed(object sender, ExecutedRoutedEventArgs e) {
            Process.Start("https://github.com/ZieIony/Ghurund/blob/master/README.md");
        }

        private void RaiseIssueCommand_Executed(object sender, ExecutedRoutedEventArgs e) {
            Process.Start("https://github.com/ZieIony/Ghurund/issues");
        }

        private void AboutCommand_Executed(object sender, ExecutedRoutedEventArgs e) {
            var window = new AboutWindow();
            window.Owner = this;
            window.Show();
        }
    }
}
