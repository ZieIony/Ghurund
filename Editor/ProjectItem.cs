using System.Collections.ObjectModel;

namespace Ghurund.Editor {
    public class ProjectItem {
        public string Title { get; set; }

        public ObservableCollection<ProjectItem> Items { get; set; } = new ObservableCollection<ProjectItem>();
    }
}
