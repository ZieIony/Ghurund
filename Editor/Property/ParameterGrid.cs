using Ghurund.Controls.PropertyGrid;
using Ghurund.Managed.Game;
using System.Collections.Generic;

namespace Ghurund.Editor.Property {
    public class ParameterGrid: PropertyGrid {
        public void AddParameters(IEnumerable<Parameter> parameters, string category) {
            foreach (Parameter p in parameters) {
                if (p != null) {
                    var property = makeProperty(p);
                    property.Category = category;
                    Properties.Add(property);
                }
            }
        }

        private Controls.PropertyGrid.Property makeProperty(Parameter p) {
            var property = new Controls.PropertyGrid.Property(p) {
                DisplayName = p.Name
            };
            property.Value.Getter = () => p.Value;
            switch (p.Type) {
                case (ParameterType.Float):
                    property.Value.Editor = new FloatPropertyEditor();
                    property.Value.Setter = v => p.Value = v;
                    break;
                case (ParameterType.Float3):
                    property.Value.Editor = new Float3PropertyEditor();
                    property.Value.Setter = v => p.Value = v;
                    break;
                case (ParameterType.Color):
                    property.Value.Editor = new ColorPropertyEditor();
                    property.Value.Setter = v => p.Value = v;
                    break;
                case (ParameterType.Texture):
                    property.Value.Editor = new TexturePropertyEditor();
                    property.Value.Setter = v => p.Value = v;
                    break;
            }
            return property;
        }
    }
}
