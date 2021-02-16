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
                string layoutClass = Path.GetFileNameWithoutExtension(file);
                string inputLayout = Path.Combine(input, file);
                string outputHeader = Path.Combine(output, layoutClass + ".h");
                if (new FileInfo(inputLayout).LastWriteTimeUtc.Ticks > new FileInfo(outputHeader).LastWriteTimeUtc.Ticks)
                    generateBinding(layoutClass, inputLayout, outputHeader);
            }
        }

        private void generateBinding(string layoutClass, string input, string output)
        {
            List<BoundField> fields = readLayout(input);

            FileStream bindingStream = File.Create(output);
            StreamWriter streamWriter = new StreamWriter(bindingStream, Encoding.ASCII);
            string layoutNamespace = "Ghurund::UI";
            BoundField controlContainer = fields.Find(it => it.Name == "container" && it.Type == "ControlContainer");
            fields.Remove(controlContainer);
            streamWriter.Write($@"#pragma once

#include ""ui/widget/Layout.h""

namespace {layoutNamespace} {{
");
            foreach (BoundField field in fields)
            {
                streamWriter.Write($"    class {field.Type};\r\n");
            }

            streamWriter.Write($@"
    class {layoutClass}:public {(controlContainer != null ? "ContainerLayout" : "WidgetLayout")} {{
");
            if (fields.Count > 0)
            {
                streamWriter.Write($@"    private:
");
                foreach (BoundField field in fields)
                {
                    streamWriter.Write($"        {field.Type}* {field.Name} = nullptr;\r\n");
                }
                streamWriter.Write("\r\n");
            }
            streamWriter.Write($@"    public:
        {layoutClass}(Control* control):{(controlContainer != null ? "ContainerLayout" : "WidgetLayout")}(control) {{
");

            foreach (BoundField field in fields)
            {
                streamWriter.Write($"            {field.Name} = ({layoutNamespace}::{field.Type}*)control->find(\"{ field.Name }\");\r\n");
            }

            streamWriter.Write("        }\r\n");

            foreach (BoundField field in fields)
            {
                string propertyName = field.Name.Substring(0, 1).ToUpper() + field.Name.Substring(1);
                streamWriter.Write($@"
        inline {field.Type}* get{ propertyName }() {{
            return {field.Name};
        }}

        __declspec(property(get = get{propertyName})) {field.Type}* {propertyName};
");
            }

            streamWriter.Write($@"    }};
}}
");
            streamWriter.Close();
        }

        private List<BoundField> readLayout(string path)
        {
            List<BoundField> fields = new List<BoundField>();
            XmlReader xReader = XmlReader.Create(new StreamReader(File.OpenRead(path)));
            while (xReader.Read())
            {
                switch (xReader.NodeType)
                {
                    case XmlNodeType.Element:
                        string attr = xReader.GetAttribute("name");
                        if (attr != null)
                        {
                            fields.Add(new BoundField
                            {
                                Type = xReader.Name,
                                Name = attr
                            });
                        }
                        break;
                }
            }
            return fields;
        }
    }
}