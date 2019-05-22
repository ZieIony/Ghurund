using System.Diagnostics;
using System.Globalization;
using System.Windows;

namespace Ghurund.Editor {
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App: Application {
        public App() {
            if (Debugger.IsAttached)
                CultureInfo.DefaultThreadCurrentUICulture = CultureInfo.GetCultureInfo("en-US");
        }
    }
}
