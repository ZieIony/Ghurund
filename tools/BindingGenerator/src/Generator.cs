using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

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

#include ""ui/control/Control.h""

");

            // forward declarations
            foreach (KeyValuePair<string, HashSet<string>> namespaceTypes in layout.Types) {
                streamWriter.Write($"namespace {namespaceTypes.Key} {{\r\n");
                foreach (string type in namespaceTypes.Value) {
                    streamWriter.Write($"    class {type};\r\n");
                }
                streamWriter.Write("}\r\n\r\n");
            }

            streamWriter.Write($"namespace {layout.Namespace} {{\r\n");

            // layout class
            streamWriter.Write($"    class {layoutClass}Binding {{\r\n");
            if (layout.Controls.Count > 0) {
                streamWriter.Write("    private:\r\n");
                foreach (BoundControl control in layout.Controls) {
                    streamWriter.Write($"        {control.Namespace}::{control.Type}* {control.Name} = nullptr;\r\n");
                }
                streamWriter.Write("\r\n");
            }

            // constructor
            streamWriter.Write($@"    public:
        void init(Ghurund::UI::Control& control) {{
");
            foreach (BoundControl control in layout.Controls) {
                streamWriter.Write($"            {control.Name} = ({control.Namespace}::{control.Type}*)control.find(\"{ control.Name }\");\r\n");
            }

            streamWriter.Write("        }\r\n");

            // control properties
            foreach (BoundControl control in layout.Controls) {
                string propertyName = control.Name.Substring(0, 1).ToUpper() + control.Name.Substring(1);
                streamWriter.Write($@"
        inline {control.Namespace}::{control.Type}& get{ propertyName }() {{
            return *{control.Name};
        }}

        __declspec(property(get = get{propertyName})) {control.Namespace}::{control.Type}& {propertyName};
");
            }

            streamWriter.Write($@"    }};
}}");
            streamWriter.Close();

            Console.WriteLine(output);
        }

    }
}