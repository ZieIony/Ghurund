using System.Windows.Forms;
using Ghurund.Managed.Graphics;

namespace Ghurund.Editor {
    public partial class GraphicsSettings : Form {
        private readonly Graphics graphics;

        public GraphicsSettings() {
            InitializeComponent();
        }

        public GraphicsSettings(Graphics graphics) {
            InitializeComponent();

            this.graphics = graphics;

            graphics.Adapters.ForEach(delegate (Adapter adapter) {
                comboBox1.Items.Add(adapter);
            });

            comboBox1.SelectedIndexChanged += ComboBox1_SelectedIndexChanged;
            comboBox2.SelectedIndexChanged += ComboBox2_SelectedIndexChanged;
        }

        private void ComboBox1_SelectedIndexChanged(object sender, System.EventArgs e) {
            comboBox2.Items.Clear();
            graphics.Adapters[comboBox1.SelectedIndex].AdapterOutputs.ForEach(delegate (AdapterOutput output) {
                comboBox2.Items.Add(output);
            });
        }

        private void ComboBox2_SelectedIndexChanged(object sender, System.EventArgs e) {
            comboBox3.Items.Clear();
            graphics.Adapters[comboBox1.SelectedIndex].AdapterOutputs[comboBox2.SelectedIndex].DisplayModes.ForEach(delegate (DisplayMode displayMode) {
                comboBox3.Items.Add(displayMode);
            });
        }
    }
}
