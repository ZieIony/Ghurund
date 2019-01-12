using System.IO;
using System.Windows;
using Microsoft.Win32;

namespace Ghurund.Editor {
    public partial class MainWindow {

        private void ProjectNew_Click(object sender, RoutedEventArgs e) {
            newProject();
        }

        private void ProjectOpen_Click(object sender, RoutedEventArgs e) {
            openFile(true); // TODO: make default filter parameter more readable than just 'true'
        }

        private void ProjectClose_Click(object sender, RoutedEventArgs e) {
            closeProject();
        }

        private void closeProject() {
            if (ProjectExplorer.Project != null) {
                Controls.Workspace.Extensions.WriteToBinaryFile(ProjectExplorer.Project, ProjectExplorer.Project.Path);
                ProjectExplorer.Project = null;
            }
        }

        private void newProject() {
            closeProject();

            SaveFileDialog saveFileDialog = new SaveFileDialog {
                Filter = "Projects (*.project)|*.project"
            };
            if (saveFileDialog.ShowDialog() == true) {
                openProject(saveFileDialog.FileName);
                Controls.Workspace.Extensions.WriteToBinaryFile(ProjectExplorer.Project, saveFileDialog.FileName);
            }
        }

        private void openProject(string fileName) {
            Project project = new Project(new FileInfo(fileName).Name);
            project.Path = fileName;
            ProjectExplorer.Project = project;

            // TODO: show project explorer, if not visible
        }
    }
}
