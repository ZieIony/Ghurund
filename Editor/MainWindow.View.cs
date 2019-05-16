using System.Windows.Input;

namespace Ghurund.Editor {
    public partial class MainWindow {

        private void ProjectExplorerCommand_Executed(object sender, ExecutedRoutedEventArgs e) => openPanel(sender, ProjectExplorer);

        private void SceneExplorerCommand_Executed(object sender, ExecutedRoutedEventArgs e) => openPanel(sender, SceneExplorer);

        private void PropertiesCommand_Executed(object sender, ExecutedRoutedEventArgs e) => openPanel(sender, PropertiesPanel);

        private void ParametersCommand_Executed(object sender, ExecutedRoutedEventArgs e) => openPanel(sender, ParametersPanel);

        private void LibrariesCommand_Executed(object sender, ExecutedRoutedEventArgs e) => openPanel(sender, LibrariesPanel);

        private void StatisticsCommand_Executed(object sender, ExecutedRoutedEventArgs e) => openPanel(sender, StatisticsPanel);

        private void LogsCommand_Executed(object sender, ExecutedRoutedEventArgs e) => openPanel(sender, LogPanel);
    }
}
