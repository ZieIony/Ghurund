using System;
using System.Collections.Generic;
using System.IO;
using Ghurund.Controls.Workspace;

namespace Ghurund.Editor {
    [Serializable]
    public class EditorSettings {
        public static readonly string EDITOR_SETTINGS_FILE_NAME = "editor.xml";

        public WorkspaceState WorkspaceState { get; set; }

        public List<string> Libraries { get; } = new List<string>();

        public List<ResourceFile> RecentProjects { get; } = new List<ResourceFile>();
        public List<ResourceFile> RecentFiles { get; } = new List<ResourceFile>();
    }
}
