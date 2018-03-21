namespace Ghurund.Editor.Utils {
    public static class Extensions {
        public static bool IsInDesignMode(this System.Windows.Forms.Control control) {
            return ResolveDesignMode(control);
        }

        private static bool ResolveDesignMode(System.Windows.Forms.Control control) {
            System.Reflection.PropertyInfo designModeProperty = control.GetType().GetProperty(
                "DesignMode",
                System.Reflection.BindingFlags.Instance
                | System.Reflection.BindingFlags.NonPublic);

            bool designMode = (bool)designModeProperty.GetValue(control, null);

            if (control.Parent != null)
                designMode |= ResolveDesignMode(control.Parent);

            return designMode;
        }
    }
}
