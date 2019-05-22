using Ghurund.Controls.PropertyGrid;
using Ghurund.Managed.Graphics.Texture;
using System.Windows;
using System.Windows.Controls;

namespace Ghurund.Editor.Property {
    public class TexturePropertyEditor: IPropertyEditor {
        public FrameworkElement MakeControl(Value property) {
            DockPanel dockPanel = new DockPanel();

            Texture texture = (Texture)property.Getter();
            System.Windows.Controls.Image image = new System.Windows.Controls.Image {
                Source = texture?.Image.ToBitmap(),
                Effect = new BgraEffect()
            };

            Border border = new Border {
                Child = image,
                Width = 20,
                Height = 20,
                BorderThickness = new Thickness(1),
                Margin = new Thickness(0, 0, 2, 0)
            };
            border.SetResourceReference(Border.BorderBrushProperty, "Ghurund.Border");
            DockPanel.SetDock(border, Dock.Left);
            dockPanel.Children.Add(border);

            ComboBox comboBox = new ComboBox();
            object val = property.Getter();
            if (val != null)
                comboBox.Items.Add(val);
            comboBox.SelectedItem = property.Getter();
            comboBox.SelectionChanged += (object sender, SelectionChangedEventArgs e) => {
                property.Setter(comboBox.SelectedItem);
            };
            dockPanel.Children.Add(comboBox);

            return dockPanel;
        }
    }

}
