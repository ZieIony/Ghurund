using Ninject;

namespace Ghurund.Editor {
    public partial class MainWindow {

        [Inject]
        public ColorPickerWindow ColorPicker { get; set; }

        private void ColorPickerCommand_Executed(object sender, System.Windows.Input.ExecutedRoutedEventArgs e) {
            ColorPicker.Show();
        }
    }
}
