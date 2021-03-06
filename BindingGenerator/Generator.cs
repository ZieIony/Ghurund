using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;

namespace BindingGenerator
{
    class Generator
    {
        public void generateBindings(List<string> files, string input, string output)
        {
            foreach (string file in files)
            {
                string layoutClass = Path.GetFileNameWithoutExtension(file).Substring(0, 1).ToUpper() + Path.GetFileNameWithoutExtension(file).Substring(1) + "Binding";
                string inputLayout = Path.Combine(input, file);
                if (!Directory.Exists(output))
                    Directory.CreateDirectory(output);
                string outputHeader = Path.Combine(output, layoutClass + ".h");
                if (new FileInfo(inputLayout).LastWriteTimeUtc.Ticks > new FileInfo(outputHeader).LastWriteTimeUtc.Ticks)
                    generateBinding(layoutClass, inputLayout, outputHeader);
            }
        }

        private void generateBinding(string layoutClass, string input, string output)
        {
            Layout layout = readLayout(input);

            FileStream bindingStream = File.Create(output);
            StreamWriter streamWriter = new StreamWriter(bindingStream, Encoding.ASCII);
            BoundControl controlContainer = layout.Controls.Find(it => it.Name == "container");
            string baseType = "WidgetLayout";
            if (controlContainer != null)
            {
                if (controlContainer.Type == "ControlContainer")
                {
                    baseType = "ContainerLayout";
                }
                else
                {
                    baseType = "GroupLayout";
                }
            }
            layout.Controls.Remove(controlContainer);
            streamWriter.Write("#pragma once\r\n\r\n");
            if (layout.Source != null && layout.Type != null && layout.Values.Count > 0)
                streamWriter.Write($"#include \"{layout.Source}\"\r\n");
            streamWriter.Write("#include \"ui/widget/Layout.h\"\r\n\r\n");
            foreach (KeyValuePair<string, HashSet<string>> namespaceTypes in layout.Types)
            {
                streamWriter.Write($"namespace {namespaceTypes.Key} {{\r\n");
                foreach (string type in namespaceTypes.Value)
                {
                    streamWriter.Write($"    class {type};\r\n");
                }
                streamWriter.Write("}\r\n\r\n");
            }

            streamWriter.Write($@"namespace {layout.Namespace} {{
    class {layoutClass}:public Ghurund::UI::{baseType} {{
");
            if (layout.Controls.Count > 0)
            {
                streamWriter.Write("    private:\r\n");
                foreach (BoundControl control in layout.Controls)
                {
                    streamWriter.Write($"        {control.Namespace}::{control.Type}* {control.Name} = nullptr;\r\n");
                }
                streamWriter.Write("\r\n");
            }
            streamWriter.Write($@"    public:
        {layoutClass}(Ghurund::UI::Control* control):{baseType}(control) {{
");

            foreach (BoundControl control in layout.Controls)
            {
                streamWriter.Write($"            {control.Name} = ({control.Namespace}::{control.Type}*)control->find(\"{ control.Name }\");\r\n");
            }

            streamWriter.Write("        }\r\n");

            foreach (BoundControl control in layout.Controls)
            {
                string propertyName = control.Name.Substring(0, 1).ToUpper() + control.Name.Substring(1);
                streamWriter.Write($@"
        inline {control.Namespace}::{control.Type}* get{ propertyName }() {{
            return {control.Name};
        }}

        __declspec(property(get = get{propertyName})) {control.Namespace}::{control.Type}* {propertyName};
");
            }

            if (layout.Source != null && layout.Type != null && layout.Values.Count > 0)
            {
                streamWriter.Write($@"
        inline void bind(const {layout.Type}* data) {{
");
                foreach (BoundValue value in layout.Values)
                {
                    streamWriter.Write($"            {value.Control}->{value.Property} = data->{value.Value};\r\n");
                }
                streamWriter.Write("        }\r\n");
            }
            streamWriter.Write($@"    }};
}}
");
            streamWriter.Close();
        }

        private Layout readLayout(string path)
        {
            List<BoundControl> controls = new List<BoundControl>();
            List<BoundValue> values = new List<BoundValue>();
            var layout = new Layout
            {
                Controls = controls,
                Values = values,
                Types = new Dictionary<string, HashSet<string>>()
            };
            XmlReader xReader = XmlReader.Create(new StreamReader(File.OpenRead(path)));
            while (xReader.Read())
            {
                switch (xReader.NodeType)
                {
                    case XmlNodeType.Element:
                        if (xReader.Name == "layout")
                        {
                            string attr = xReader.GetAttribute("data");
                            if (attr != null)
                            {
                                layout.Type = attr;
                            }
                            string attr2 = xReader.GetAttribute("source");
                            if (attr2 != null)
                            {
                                layout.Source = attr2;
                            }
                            string attr3 = xReader.GetAttribute("namespace");
                            if (attr3 != null)
                            {
                                layout.Namespace = attr3;
                            }
                        }
                        else
                        {
                            string attr = xReader.GetAttribute("name");
                            if (attr != null)
                            {
                                BoundControl boundControl = new BoundControl
                                {
                                    Type = xReader.Name,
                                    Name = attr
                                };
                                string namespaceAttr = xReader.GetAttribute("namespace");
                                if (namespaceAttr != null)
                                    boundControl.Namespace = namespaceAttr;
                                controls.Add(boundControl);
                                if (!layout.Types.ContainsKey(boundControl.Namespace))
                                    layout.Types.Add(boundControl.Namespace, new HashSet<string>());
                                layout.Types[boundControl.Namespace].Add(boundControl.Type);
                                for (int i = 0; i < xReader.AttributeCount; i++)
                                {
                                    xReader.MoveToAttribute(i);
                                    if (xReader.Value.StartsWith("."))
                                    {
                                        layout.Values.Add(new BoundValue
                                        {
                                            Control = boundControl.Name,
                                            Property = xReader.Name.Substring(0, 1).ToUpper() + xReader.Name.Substring(1),
                                            Value = xReader.Value.Substring(1)
                                        });
                                    }
                                }
                            }
                        }
                        break;
                    case XmlNodeType.Attribute:
                        if (xReader.Value.StartsWith("."))
                        {
                        }
                        break;
                }
            }
            return layout;
        }
    }
}