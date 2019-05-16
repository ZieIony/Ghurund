using Ghurund.Controls.Workspace;
using System.Windows;

namespace Ghurund.Editor {
    public partial class ColorPickerWindow: Window {
        public ColorPicker ColorPicker { get => colorPicker; }

        public ColorPickerWindow() {
            InitializeComponent();

            AddHandler(TitleBar.WindowActionEvent, new WindowActionEventHandler(titleBar_WindowAction));
        }

        private void titleBar_WindowAction(object sender, WindowActionEventArgs args) {
            if (args.Action == WindowAction.Close)
                Hide();
            args.Handled = true;
        }
    }
}
