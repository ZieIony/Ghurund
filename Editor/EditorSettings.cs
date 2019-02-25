using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Windows;
using Ghurund.Controls.Workspace;

namespace Ghurund.Editor {
    [Serializable]
    public class EditorSettings {
        public static readonly string EDITOR_SETTINGS_FILE_NAME = "editor.xml";
        private static readonly int MAX_RECENT_FILES = 10;
        private static readonly int MAX_RECENT_PROJECTS = 10;

        [Browsable(false)]
        public Size WindowSize { get; set; }

        [Browsable(false)]
        public WorkspaceState WorkspaceState { get; set; }

        [Browsable(false)]
        public List<string> Libraries { get; } = new List<string>();

        [Browsable(false)]
        public List<string> RecentProjects { get; } = new List<string>();

        [Browsable(false)]
        public List<string> RecentFiles { get; } = new List<string>();

        public void AddRecentProject(string file) {
            RecentProjects.Remove(file);
            RecentProjects.Add(file);
            while (RecentProjects.Count > MAX_RECENT_PROJECTS)
                RecentProjects.RemoveAt(MAX_RECENT_PROJECTS);
        }

        public void AddRecentFile(string file) {
            RecentFiles.Remove(file);
            RecentFiles.Add(file);
            while (RecentFiles.Count > MAX_RECENT_FILES)
                RecentFiles.RemoveAt(MAX_RECENT_FILES);
        }

        [Editable(true)]
        [Category("Recents")]
        [Description("Next time GhurundEditor will start with the most recent project opened (if possible).")]
        public bool ReopenMostRecentProject { get; set; } = true;

        [Editable(true)]
        [Category("Recents")]
        [Description("Maximum number of recent projects shown on welcome screen.")]
        public int MaxRecentProjects { get; set; } = MAX_RECENT_PROJECTS;

        [Editable(true)]
        [Category("Recents")]
        [Description("Maximum number of recent files shown on welcome screen.")]
        public int MaxRecentFiles { get; set; } = MAX_RECENT_FILES;

        [Editable(true)]
        [Category("Look and feel")]
        [Description("Dark and light theme.")]
        public Theme Theme { get; set; } = Theme.Light;
    }
}
