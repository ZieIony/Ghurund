using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Xml;

namespace BindingGenerator {
    class Generator {
        public void generateBindings(List<string> files, string input, string output) {
            Console.WriteLine("Generating bindings");
            foreach (string file in files) {
                string layoutClass = Path.GetFileNameWithoutExtension(file).Substring(0, 1).ToUpper() + Path.GetFileNameWithoutExtension(file).Substring(1);
                string inputLayout = Path.Combine(input, file);
                if (!Directory.Exists(output))
                    Directory.CreateDirectory(output);
                string outputHeader = Path.Combine(output, layoutClass + "Binding.h");
                if (new FileInfo(inputLayout).LastWriteTimeUtc.Ticks > new FileInfo(outputHeader).LastWriteTimeUtc.Ticks) {
                    generateBinding(layoutClass, inputLayout, outputHeader);
                } else {
                    Console.WriteLine(outputHeader + " (no changes, skipped)");
                }
            }
            Console.WriteLine("Done");
        }

        private void generateBinding(string layoutClass, string input, string output) {
            Layout layout = readLayout(input);
            bool hasBinding = layout.Values.Count + layout.Events.Count > 0;

            FileStream bindingStream = File.Create(output);
            StreamWriter streamWriter = new StreamWriter(bindingStream, Encoding.ASCII);

            // includes
            streamWriter.Write(@"#pragma once

#include ""ui/LayoutLoader.h""
#include ""ui/widget/Layout.h""

");

            // forward declarations
            foreach (KeyValuePair<string, HashSet<string>> namespaceTypes in layout.Types) {
                streamWriter.Write($"namespace {namespaceTypes.Key} {{\r\n");
                foreach (string type in namespaceTypes.Value) {
                    streamWriter.Write($"    class {type};\r\n");
                }
                streamWriter.Write("}\r\n\r\n");
            }

            string baseClass = hasBinding ? $"BindingLayout<Data>" : "WidgetLayout";

            streamWriter.Write($"namespace {layout.Namespace} {{\r\n");

            // layout class
            if (hasBinding) {
                streamWriter.Write($@"    template<class Data>
    class {layoutClass}Binding:public Ghurund::UI::{baseClass} {{
");
            } else {
                streamWriter.Write($"    class {layoutClass}Binding:public Ghurund::UI::{baseClass} {{\r\n");
            }
            if (layout.Controls.Count > 0) {
                streamWriter.Write("    private:\r\n");
                foreach (BoundControl control in layout.Controls) {
                    streamWriter.Write($"        {control.Namespace}::{control.Type}* {control.Name} = nullptr;\r\n");
                }
                foreach (BoundControl control in layout.Containers) {
                    streamWriter.Write($"        {control.Namespace}::{control.Type}* {control.Name} = nullptr;\r\n");
                }
                streamWriter.Write("\r\n");
            }

            // constructor
            streamWriter.Write($@"    public:
        {layoutClass}Binding(Ghurund::UI::Control* control):{baseClass}(control) {{
");
            foreach (BoundControl control in layout.Controls) {
                streamWriter.Write($"            {control.Name} = ({control.Namespace}::{control.Type}*)control->find(\"{ control.Name }\");\r\n");
            }
            foreach (BoundControl control in layout.Containers) {
                streamWriter.Write($"            {control.Name} = ({control.Namespace}::{control.Type}*)control->find(\"{ control.Name }\");\r\n");
            }

            streamWriter.Write("        }\r\n");

            // control properties
            foreach (BoundControl control in layout.Controls) {
                string propertyName = control.Name.Substring(0, 1).ToUpper() + control.Name.Substring(1);
                streamWriter.Write($@"
        inline {control.Namespace}::{control.Type}* get{ propertyName }() {{
            return {control.Name};
        }}

        __declspec(property(get = get{propertyName})) {control.Namespace}::{control.Type}* {propertyName};
");
            }

            // content properties
            if (layout.Containers.Count > 0) {
                foreach (BoundControl control in layout.Containers) {
                    string propertyName = control.Name.Substring(0, 1).ToUpper() + control.Name.Substring(1);
                    streamWriter.Write($@"
        inline Ghurund::UI::Control* get{ propertyName }() {{
            return {control.Name}->Child;
        }}

        inline void set{ propertyName }(Ghurund::UI::Control* value) {{
            {control.Name}->Child = value;
        }}

        __declspec(property(get = get{propertyName}, put = set{propertyName})) Ghurund::UI::Control* {propertyName};
");
                }

                // load content
                streamWriter.Write($@"
        virtual Status loadContent(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override {{
            auto childElement = xml.FirstChildElement();
            while (childElement) {{
");
                string elseIf = "";
                string contentProperty = layout.Containers[0].Name.Substring(0, 1).ToUpper() + layout.Containers[0].Name.Substring(1);
                foreach (BoundControl control in layout.Containers) {
                    string propertyName = control.Name.Substring(0, 1).ToUpper() + control.Name.Substring(1);
                    if (control.Name == "content")
                        contentProperty = "Content";
                    streamWriter.Write($@"                {elseIf}if (strcmp(childElement->Name(), ""{layoutClass}.{propertyName}"") == 0) {{
                    auto controls = loader.loadControls(*childElement);
                    if (!controls.Empty)
                        {propertyName} = controls[0];
");
                    elseIf = "} else ";
                }
                streamWriter.Write($@"                }} else if (!{contentProperty}) {{
                    auto control = loader.loadControl(*childElement);
                    if (control) {{
                        { contentProperty } = control;
                        control->release();
                    }}
                }}
                childElement = childElement->NextSiblingElement();
            }}
            return Status::OK;
        }}
");


                streamWriter.Write(@"
        virtual Control* find(const AString& name) override {
");
                for (int i = 0; i < layout.Containers.Count - 1; i++) {
                    BoundControl control = layout.Containers[i];
                    streamWriter.Write($@"            if ({control.Name}->Child) {{
                Control* {control.Name}Find = {control.Name}->Child->find(name);
                if ({control.Name}Find)
                    return {control.Name}Find;
            }}
");
                }
                {
                    BoundControl control = layout.Containers[layout.Containers.Count - 1];
                    streamWriter.Write($@"            if ({control.Name}->Child)
                return {control.Name}->Child->find(name);
");
                }
                streamWriter.Write($@"            return nullptr;
        }}
");

                streamWriter.Write(@"
        virtual Control* find(const Ghurund::Type& type) override {
");
                for (int i = 0; i < layout.Containers.Count - 1; i++) {
                    BoundControl control = layout.Containers[i];
                    streamWriter.Write($@"            if ({control.Name}->Child) {{
                Control* {control.Name}Find = {control.Name}->Child->find(type);
                if ({control.Name}Find)
                    return {control.Name}Find;
            }}
");
                }
                {
                    BoundControl control = layout.Containers[layout.Containers.Count - 1];
                    streamWriter.Write($@"            if ({control.Name}->Child)
                return {control.Name}->Child->find(type);
");
                }
                streamWriter.Write($@"            return nullptr;
        }}
");

            }

            // binding
            if (hasBinding) {
                streamWriter.Write($@"
        inline void bind(Data& data) {{
");
                foreach (BoundValue value in layout.Values) {
                    streamWriter.Write($"            {value.Control}->{value.Property} = data.{value.Value};\r\n");
                }
                foreach (BoundEvent value in layout.Events) {
                    streamWriter.Write($@"            {value.Control}->{value.Event}.clear();
            {value.Control}->{value.Event}.add(data.{value.Handler});
");
                }
                streamWriter.Write("        }\r\n");
            }
            streamWriter.Write($@"    }};
}}
");
            streamWriter.Close();

            Console.WriteLine(output);
        }

        private Layout readLayout(string path) {
            var layout = new Layout {
                Controls = new List<BoundControl>(),
                Containers = new List<BoundControl>(),
                Values = new List<BoundValue>(),
                Events = new List<BoundEvent>(),
                Types = new Dictionary<string, HashSet<string>>()
            };
            XmlReader xReader = XmlReader.Create(new StreamReader(File.OpenRead(path)));

            while (xReader.Read()) {
                switch (xReader.NodeType) {
                    case XmlNodeType.Element:
                        if (xReader.Name == "layout") {
                            string attr3 = xReader.GetAttribute("namespace");
                            if (attr3 != null) {
                                layout.Namespace = attr3;
                            }
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
                                    layout.Containers.Add(boundControl);
                                } else {
                                    layout.Controls.Add(boundControl);
                                }
                                if (!layout.Types.ContainsKey(boundControl.Namespace))
                                    layout.Types.Add(boundControl.Namespace, new HashSet<string>());
                                layout.Types[boundControl.Namespace].Add(boundControl.Type);
                                for (int i = 0; i < xReader.AttributeCount; i++) {
                                    xReader.MoveToAttribute(i);
                                    if (xReader.Value.StartsWith(".")) {
                                        layout.Values.Add(new BoundValue {
                                            Control = boundControl.Name,
                                            Property = xReader.Name.Substring(0, 1).ToUpper() + xReader.Name.Substring(1),
                                            Value = xReader.Value.Substring(1)
                                        });
                                    } else if (xReader.Value.StartsWith("+")) {
                                        layout.Events.Add(new BoundEvent {
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
            return layout;
        }
    }
}