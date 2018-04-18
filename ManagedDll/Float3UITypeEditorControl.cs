using System.Windows.Forms;
using System.Windows.Forms.Design;

namespace Ghurund.Managed {
    public partial class Float3UITypeEditorControl : UserControl {
        private Float3 value;
        public Float3 Value {
            get {
                value.X = (float)numericUpDown1.Value;
                value.Y = (float)numericUpDown2.Value;
                value.Z = (float)numericUpDown3.Value;
                return value;
            }
            set {
                this.value = value;
                numericUpDown1.Value = (decimal)value.X;
                numericUpDown2.Value = (decimal)value.Y;
                numericUpDown3.Value = (decimal)value.Z;
            }
        }

        private readonly IWindowsFormsEditorService editorService;

        public Float3UITypeEditorControl(Float3 value, IWindowsFormsEditorService editorService) {
            InitializeComponent();
            Value = value;
            this.editorService = editorService;
        }

    }
}
