using System;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Ghurund.Controls.Workspace;

namespace Ghurund.Editor {
    public interface IWelcomePage : IDockableControl {
    }

    public partial class WelcomePage : UserControl, IWelcomePage {
        public WelcomePage() {
            InitializeComponent();
        }

        public ImageSource Icon { get; } = new BitmapImage(new Uri("pack://application:,,,/Resources/welcomePage32.png", UriKind.Absolute));
        public Control Control { get => this; }
        public string Title { get => "Welcome Page"; }
    }
}
