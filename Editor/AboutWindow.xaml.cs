using System.Diagnostics;
using System.Reflection;
using System.Windows;

namespace Ghurund.Editor {
    /// <summary>
    /// Interaction logic for AboutWindow.xaml
    /// </summary>
    public partial class AboutWindow: Window {
        public AboutWindow() {
            InitializeComponent();

            string version = Assembly.GetExecutingAssembly().GetName().Version.ToString();
            info.Text = "Editor version: " + version+ "\nEngine version: 0.0";
        }

        private void Hyperlink_RequestNavigate(object sender, System.Windows.Navigation.RequestNavigateEventArgs e) {
            Process.Start("https://github.com/ZieIony/Ghurund");
        }
    }
}
