using System;

namespace Ghurund.Controls.PropertyGrid {
    public interface IPropertyEditorFactory {

        Type GetEditorType(Type propertyType);
    }
}