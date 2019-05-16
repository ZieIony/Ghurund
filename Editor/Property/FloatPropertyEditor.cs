using Ghurund.Controls.PropertyGrid;
using Ghurund.Managed;
using Ghurund.Managed.Script;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace Ghurund.Editor.Property {
    public class FloatPropertyEditor: IPropertyEditor {
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
            bool result = float.TryParse(textBox.Text, out float val);
            if (result) {
                property.Setter(val);
            } else {
                ScriptEngine engine = EditorKernel.GetService(typeof(ScriptEngine)) as ScriptEngine;
                Script script = new Script {
                    SourceCode = "float main(){return " + textBox.Text + ";}",
                    EntryPoint = "float main()"
                };
                if (script.Build(engine) == Status.OK && script.Execute() == Status.OK) {
                    property.Setter(script.GetFloatResult());
                    script.Release();
                } else {
                    property.Setter(property.Getter());
                }
            }
        }
    }

}
