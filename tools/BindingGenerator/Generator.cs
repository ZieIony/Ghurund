using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using Utils;

namespace BindingGenerator {
    class Generator {
        public void generateBindings(FileInfo[] files, DirectoryInfo output) {
            Console.WriteLine("Generating bindings");
            foreach (FileInfo file in files) {
                string layoutClass = file.GetNameWithoutExtension().Substring(0, 1).ToUpper() + file.GetNameWithoutExtension().Substring(1);
                if (!output.Exists)
                    output.Create();
                var outputHeader = new FileInfo(Path.Combine(output.FullName, layoutClass + "Binding.h"));
                if (file.LastWriteTimeUtc.Ticks > outputHeader.LastWriteTimeUtc.Ticks) {
                    GenerateBinding(layoutClass, file, outputHeader);
                } else {
                    Console.WriteLine(outputHeader + " (no changes, skipped)");
                }
            }
            Console.WriteLine("Done");
        }

        private void GenerateBinding(string layoutClass, FileInfo input, FileInfo output) {
            Layout layout = new Layout();
            layout.Read(input);

            FileStream bindingStream = output.Create();
            StreamWriter streamWriter = new StreamWriter(bindingStream, Encoding.ASCII);

            // includes
            streamWriter.Write(@"#pragma once

#include ""ui/layout/LayoutLoader.h""
#include ""ui/widget/LayoutBinding.h""

");

            // forward declarations
            foreach (KeyValuePair<string, HashSet<string>> namespaceTypes in layout.Types) {
                streamWriter.Write($"namespace {namespaceTypes.Key} {{\r\n");
                foreach (string type in namespaceTypes.Value) {
                    streamWriter.Write($"    class {type};\r\n");
                }
                streamWriter.Write("}\r\n\r\n");
            }

            string baseClass = "LayoutBinding";

            streamWriter.Write($"namespace {layout.Namespace} {{\r\n");

            // layout class
            if (layout.HasBinding) {
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
        virtual Status loadContent(Ghurund::UI::LayoutLoader& loader, const tinyxml2::XMLElement& xml) override {{
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
        virtual Ghurund::UI::Control* find(const Ghurund::AString& name) override {
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
        virtual Ghurund::UI::Control* find(const Ghurund::Type& type) override {
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
            if (layout.HasBinding) {
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

    }
}