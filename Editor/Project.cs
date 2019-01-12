using System;

namespace Ghurund.Editor {
    [Serializable]
    public class Project {

        public string Name { get; set; }

        [NonSerialized]
        private string path;
        public string Path { get => path; set => path = value; }

        public Project() {
        }

        public Project(string name) {
            Name = name;
        }
    }
}