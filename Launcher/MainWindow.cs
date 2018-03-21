using Ghurund.Managed;
using System.Diagnostics;
using System.Windows.Forms;

namespace Ghurund.Launcher {
    public partial class MainWindow : Form {
        LauncherSettings settings = new LauncherSettings();

        public MainWindow() {
            InitializeComponent();

            settings.load(null, "launcher." + settings.DefaultExtension);

            windowedCheckBox.Checked = settings.Data.DefaultWindowed;

            Text = settings.Data.Name;

            comboBox1.Items.AddRange(settings.Data.WindowSizes.ToArray());

            saveButton.Click += SaveButton_Click;
            launchButton.Click += LaunchButton_Click;
        }

        private void LaunchButton_Click(object sender, System.EventArgs e) {
            Process.Start(settings.Data.PathToExe);
            Application.Exit();
        }

        private void SaveButton_Click(object sender, System.EventArgs e) {
            Application.Exit();
        }
    }
}
