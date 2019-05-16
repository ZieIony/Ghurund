using Ghurund.Controls.PropertyGrid;
using Ghurund.Managed;
using Ghurund.Managed.Script;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace Ghurund.Editor.Property {
    public class Float3PropertyEditor: IPropertyEditor {
        public FrameworkElement MakeControl(Value property) {
            TextBox textBox = new TextBox {
                Text = property.Getter().ToString()
            };
            textBox.KeyDown += (object sender, KeyEventArgs e) => {
                if (e.Key == Key.Enter)
                    setValue(property, textBox);
            };
            textBox.LostFocus += (object sender, RoutedEventArgs e) => {
                setValue(property, textBox);
            };
            return textBox;
        }

        private static void setValue(Value property, TextBox textBox) {
            var values = textBox.Text.Split(',');
            if (values.Length == 3 &&
                float.TryParse(textBox.Text, out float x) &&
                float.TryParse(textBox.Text, out float y) &&
                float.TryParse(textBox.Text, out float z)) {
                property.Setter(new Float3(x, y, z));
            } else {
                ScriptEngine engine = EditorKernel.GetService(typeof(ScriptEngine)) as ScriptEngine;
                Script script = new Script {
                    SourceCode = "float3 main(){return float3(" + textBox.Text + ");}",
                    EntryPoint = "float3 main()"
                };
                if (script.Build(engine) == Status.OK && script.Execute() == Status.OK) {
                    property.Setter(script.GetFloat3Result());
                    script.Release();
                } else {
                    property.Setter(property.Getter());
                }
            }
            textBox.Text = property.Getter().ToString();
        }
    }

}
