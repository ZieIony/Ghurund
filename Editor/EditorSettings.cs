using System;
using System.Collections.Generic;
using System.Windows;
using Ghurund.Controls.Workspace;

namespace Ghurund.Editor {
    [Serializable]
    public class EditorSettings {
        public static readonly string EDITOR_SETTINGS_FILE_NAME = "editor.xml";
        private static readonly int MAX_RECENT_FILES = 10;
        private static readonly int MAX_RECENT_PROJECTS = 10;

        public Point WindowSize { get; set; }
        public WorkspaceState WorkspaceState { get; set; }

        public List<string> Libraries { get; } = new List<string>();

        public List<string> RecentProjects { get; } = new List<string>();
        public List<string> RecentFiles { get; } = new List<string>();

        public void AddRecentProject(string file) {
            RecentProjects.Remove(file);
            RecentProjects.Add(file);
            if (RecentProjects.Count > MAX_RECENT_PROJECTS)
                RecentProjects.RemoveAt(MAX_RECENT_PROJECTS);
        }

        public void AddRecentFile(string file) {
            RecentFiles.Remove(file);
            RecentFiles.Add(file);
            if (RecentFiles.Count > MAX_RECENT_FILES)
                RecentFiles.RemoveAt(MAX_RECENT_FILES);
        }

        public bool ReopenMostRecentProject { get; set; } = true;
    }
}
