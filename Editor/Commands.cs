using System.Windows.Input;

namespace Ghurund.Editor {
    public static class Commands {
        public static readonly RoutedUICommand ProjectExplorer = new RoutedUICommand(
                "Project E_xplorer",
                "ProjectExplorer",
                typeof(Commands),
                new InputGestureCollection(){
                    new KeyGesture(Key.E, ModifierKeys.Control|ModifierKeys.Alt)
                }
            );

        public static readonly RoutedUICommand SceneExplorer = new RoutedUICommand(
                "_Scene Explorer",
                "SceneExplorer",
                typeof(Commands),
                new InputGestureCollection(){
                    new KeyGesture(Key.S, ModifierKeys.Control|ModifierKeys.Alt)
                }
            );

        public static readonly RoutedUICommand Properties = new RoutedUICommand(
                "_Properties",
                "Properties",
                typeof(Commands),
                new InputGestureCollection(){
                    new KeyGesture(Key.P, ModifierKeys.Control|ModifierKeys.Alt)
                }
            );

        public static readonly RoutedUICommand Parameters= new RoutedUICommand(
                "P_arameters",
                "Parameters",
                typeof(Commands),
                new InputGestureCollection(){
                    new KeyGesture(Key.A, ModifierKeys.Control|ModifierKeys.Alt)
                }
            );

        public static readonly RoutedUICommand Libraries = new RoutedUICommand(
                "_Libraries",
                "Libraries",
                typeof(Commands),
                new InputGestureCollection(){
                    new KeyGesture(Key.L, ModifierKeys.Control|ModifierKeys.Alt)
                }
            );

        public static readonly RoutedUICommand Statistics = new RoutedUICommand(
                "S_tatistics",
                "Statistics",
                typeof(Commands),
                new InputGestureCollection(){
                    new KeyGesture(Key.T, ModifierKeys.Control|ModifierKeys.Alt)
                }
            );

        public static readonly RoutedUICommand Logs= new RoutedUICommand(
                "L_ogs",
                "Logs",
                typeof(Commands),
                new InputGestureCollection(){
                    new KeyGesture(Key.O, ModifierKeys.Control|ModifierKeys.Alt)
                }
            );

        public static readonly RoutedUICommand ColorPicker = new RoutedUICommand(
                "_Color Picker",
                "ColorPicker",
                typeof(Commands),
                new InputGestureCollection(){
                    new KeyGesture(Key.C, ModifierKeys.Control|ModifierKeys.Alt)
                }
            );

    }
}
