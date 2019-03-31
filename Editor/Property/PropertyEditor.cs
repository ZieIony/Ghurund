using Ghurund.Controls.PropertyGrid;
using Ghurund.Managed;
using Ghurund.Managed.Script;
using System;
using System.Globalization;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace Ghurund.Editor.Property {

    public class BooleanPropertyEditor: IPropertyEditor {
        public FrameworkElement MakeControl(Value property) {
            CheckBox checkBox = new CheckBox {
                IsChecked = (bool)property.Getter()
            };
            checkBox.Checked += (object sender, RoutedEventArgs e) => {
                property.Setter(checkBox.IsChecked);
            };
            checkBox.Unchecked += (object sender, RoutedEventArgs e) => {
                property.Setter(checkBox.IsChecked);
            };
            return checkBox;
        }
    }

    public class IntPropertyEditor: IPropertyEditor {
        public FrameworkElement MakeControl(Value property) {
            TextBox textBox = new TextBox {
                Text = property.Getter().ToString()
            };
            textBox.KeyDown += (object sender, KeyEventArgs e) => {
                if (e.Key == Key.Enter)
                    property.Setter(int.TryParse(textBox.Text, out int val) ? val : property.Getter());
            };
            textBox.LostFocus += (object sender, RoutedEventArgs e) => {
                property.Setter(int.TryParse(textBox.Text, out int val) ? val : property.Getter());
            };
            return textBox;
        }
    }

    public class FloatPropertyEditor: IPropertyEditor {
        public FrameworkElement MakeControl(Value property) {
            TextBox textBox = new TextBox {
                Text = property.Getter().ToString()
            };
            textBox.KeyDown += (object sender, KeyEventArgs e) => {
                if (e.Key == Key.Enter) {
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
            };
            textBox.LostFocus += (object sender, RoutedEventArgs e) => {
                property.Setter(float.TryParse(textBox.Text, out float val) ? val : property.Getter());
            };
            return textBox;
        }
    }

    public class TextPropertyEditor: IPropertyEditor {
        public FrameworkElement MakeControl(Value property) {
            TextBox textBox = new TextBox {
                Text = property.Getter() as string
            };
            textBox.KeyDown += (object sender, KeyEventArgs e) => {
                if (e.Key == Key.Enter) {
                    property.Setter(textBox.Text);
                }
            };
            textBox.LostFocus += (object sender, RoutedEventArgs e) => {
                property.Setter(textBox.Text);
            };
            return textBox;
        }
    }

    public class EnumPropertyEditor: IPropertyEditor {
        public FrameworkElement MakeControl(Value property) {
            ComboBox comboBox = new ComboBox();
            foreach (var item in property.Type.GetEnumValues())
                comboBox.Items.Add(item);
            comboBox.SelectedItem = property.Getter();
            comboBox.SelectionChanged += (object sender, SelectionChangedEventArgs e) => {
                property.Setter(comboBox.SelectedItem);
            };
            return comboBox;
        }
    }

    public class ResourcePropertyEditor: IPropertyEditor {
        public FrameworkElement MakeControl(Value value) {
            TextBlock textBlock = new TextBlock {
                Text = value.Getter()?.ToString()
            };
            textBlock.MouseDown += (object sender, MouseButtonEventArgs e) => {
                textBlock.RaiseEvent(new RoutedValueEditedEventEventArgs(value, PropertyGrid.ValueEditedEvent));
            };
            return textBlock;
        }
    }

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

    public class ColorPropertyEditor: IPropertyEditor {
        public FrameworkElement MakeControl(Value property) {
            DockPanel dockPanel = new DockPanel();

            Border border = new Border();
            Managed.Color color = (Managed.Color)property.Getter();
            border.Background = new System.Windows.Media.SolidColorBrush(System.Windows.Media.Color.FromArgb((byte)(color.A * 255), (byte)(color.R * 255), (byte)(color.G * 255), (byte)(color.B * 255)));
            border.Width = 20;
            border.Height = 20;
            border.BorderThickness = new Thickness(1);
            border.Margin = new Thickness(0, 0, 2, 0);
            border.SetResourceReference(Border.BorderBrushProperty, "Ghurund.Border");
            DockPanel.SetDock(border, Dock.Left);
            dockPanel.Children.Add(border);

            TextBox textBox = new TextBox {
                Text = property.Getter().ToString()
            };
            textBox.KeyDown += (object sender, KeyEventArgs e) => {
                if (e.Key == Key.Enter) {
                    border.Background = new System.Windows.Media.SolidColorBrush((System.Windows.Media.Color)System.Windows.Media.ColorConverter.ConvertFromString(textBox.Text));
                    property.Setter(new Managed.Color(textBox.Text));
                }
            };
            textBox.LostFocus += (object sender, RoutedEventArgs e) => {
                border.Background = new System.Windows.Media.SolidColorBrush((System.Windows.Media.Color)System.Windows.Media.ColorConverter.ConvertFromString(textBox.Text));
                property.Setter(new Managed.Color(textBox.Text));
            };
            dockPanel.Children.Add(textBox);

            return dockPanel;
        }
    }

}
