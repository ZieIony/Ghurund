using System.Collections.Generic;

namespace BindingGenerator {
    internal class Layout {
        public List<BoundControl> Controls { get; internal set; }
        public List<BoundControl> Containers { get; internal set; }
        public Dictionary<string, HashSet<string>> Types { get; internal set; }
        public List<BoundValue> Values { get; internal set; }
        public List<BoundEvent> Events { get; internal set; }
        public string Namespace { get; internal set; } = "Bindings";
        public string Type { get; internal set; }
    }
}