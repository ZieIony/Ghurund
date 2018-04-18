using System;
using System.ComponentModel;
using System.Drawing.Design;
using System.Windows.Forms.Design;

namespace Ghurund.Managed {
    internal class Float3UITypeEditor : UITypeEditor {
        private IWindowsFormsEditorService editorService;

        public override UITypeEditorEditStyle GetEditStyle(ITypeDescriptorContext context) {
            return UITypeEditorEditStyle.DropDown;
        }

        public override object EditValue(ITypeDescriptorContext context, IServiceProvider provider, object value) {
            if (provider != null) {
                editorService = provider.GetService(typeof(IWindowsFormsEditorService)) as IWindowsFormsEditorService;
            }

            if (editorService != null) {
                Float3UITypeEditorControl selectionControl = new Float3UITypeEditorControl((Float3)value, editorService);

                editorService.DropDownControl(selectionControl);

                value = selectionControl.Value;
            }

            return value;
        }

        // This method indicates to the design environment that 
        // the type editor will paint additional content in the 
        // LightShape entry in the PropertyGrid. 
        public override bool GetPaintValueSupported(ITypeDescriptorContext context) {
            return false;
        }
    }
}
