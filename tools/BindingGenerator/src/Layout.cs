using System.Collections.Generic;
using System.IO;
using System.Xml;

namespace BindingGenerator {
    internal class Layout {
        public List<BoundControl> Controls { get; internal set; }
        public List<BoundControl> Containers { get; internal set; }
        public Dictionary<string, HashSet<string>> Types { get; internal set; }
        public List<BoundValue> Values { get; internal set; }
        public List<BoundEvent> Events { get; internal set; }
        public bool HasBinding {
            get {
                return Values.Count + Events.Count > 0;
            }
        }
        public string Namespace { get; internal set; } = "Bindings";
        public string Type { get; internal set; }

        public void Read(FileInfo path) {
            Controls = new List<BoundControl>();
            Containers = new List<BoundControl>();
            Values = new List<BoundValue>();
            Events = new List<BoundEvent>();
            Types = new Dictionary<string, HashSet<string>>();

            XmlReader xReader = XmlReader.Create(new StreamReader(path.OpenRead()));

            while (xReader.Read()) {
                switch (xReader.NodeType) {
                    case XmlNodeType.Element:
                        if (xReader.Name == "layout") {
                            string attr3 = xReader.GetAttribute("namespace");
                            if (attr3 != null)
                                Namespace = attr3;
                        } else {
                            string attr = xReader.GetAttribute("name");
                            if (attr != null) {
                                BoundControl boundControl = new BoundControl {
                                    Type = xReader.Name,
                                    Name = attr
                                };
                                string namespaceAttr = xReader.GetAttribute("namespace");
                                if (namespaceAttr != null)
                                    boundControl.Namespace = namespaceAttr;
                                if (boundControl.Type == "ControlContainer") {
                                    Containers.Add(boundControl);
                                } else {
                                    Controls.Add(boundControl);
                                }
                                if (!Types.ContainsKey(boundControl.Namespace))
                                    Types.Add(boundControl.Namespace, new HashSet<string>());
                                Types[boundControl.Namespace].Add(boundControl.Type);
                                for (int i = 0; i < xReader.AttributeCount; i++) {
                                    xReader.MoveToAttribute(i);
                                    if (xReader.Value.StartsWith(".")) {
                                        Values.Add(new BoundValue {
                                            Control = boundControl.Name,
                                            Property = xReader.Name.Substring(0, 1).ToUpper() + xReader.Name.Substring(1),
                                            Value = xReader.Value.Substring(1)
                                        });
                                    } else if (xReader.Value.StartsWith("+")) {
                                        Events.Add(new BoundEvent {
                                            Control = boundControl.Name,
                                            Event = xReader.Name.Substring(0, 1).ToUpper() + xReader.Name.Substring(1),
                                            Handler = xReader.Value.Substring(1)
                                        });
                                    }
                                }
                            }
                        }
                        break;
                    case XmlNodeType.Attribute:
                        if (xReader.Value.StartsWith(".")) {
                        }
                        break;
                }
            }
        }

    }
}