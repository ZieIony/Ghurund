using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace Ghurund.Controls.Workspace {

    public enum DockSide {
        Top = 1, Bottom = 2, Left = 4, Right = 8, Center = 16
    }

    public enum PeekSide {
        Top = 1, Bottom = 2, Left = 4, Right = 8
    }

    public class DockSpot {

        public Rect Rect { get; set; }
        public Rect ParentRect { get; set; }
        public DockSide Side { get; private set; }
        public DockPanel DockPanel { get; private set; }
        public bool RootDock { get; internal set; }

        public DockSpot(Rect spotRect, Rect parentRect, DockSide dockSide, DockPanel dockPanel) {
            Rect = spotRect;
            ParentRect = parentRect;
            Side = dockSide;
            DockPanel = dockPanel;
            RootDock = dockPanel.GetType() == typeof(RootDockPanel);
        }
    }

    public class PeekableControl {
        public ImageSource Icon { get; private set; }

        public Control Control { get; private set; }

        public string Title { get; private set; }

        public PeekSide Side { get; private set; }

        public Size Size { get; }

        public PeekableControl(IDockableControl control, PeekSide side, Size suggestedSize) {
            Control = control.Control;
            Title = control.Title;
            Icon = control.Icon;
            Side = side;
            Size = suggestedSize;
        }
    }

    public interface IDockableControl {
        ImageSource Icon { get; }
        Control Control { get; }
        string Title { get; }
    }

    public class DockableControl : IDockableControl {
        public ImageSource Icon { get; private set; }

        public Control Control { get; private set; }

        public string Title { get; private set; }

        public DockableControl(Control control, string title, ImageSource icon = null) {
            Control = control;
            Title = title;
            Icon = icon;
        }
    }

    public class DockableControls {
        public IDockableControl[] Controls { get; }
        public Size SuggestedSize { get; }

        public DockableControls(IDockableControl control, Size? suggestedSize = null):this(new IDockableControl[] { control }, suggestedSize) {
        }

        public DockableControls(IDockableControl[] controls, Size? suggestedSize = null) {
            Controls = controls;
            SuggestedSize = suggestedSize??new Size(200, 400);
        }

        public DockableControls(DockableControl control) {
            Controls = new IDockableControl[] { control };
            SuggestedSize = new Size(control.Control.ActualWidth, control.Control.ActualHeight);
        }

        public DockableControls(EditorPanel panel) {
            var control = new DockableControl(panel.Content as Control, panel.Title, panel.Icon);
            Controls = new IDockableControl[] { control };
            SuggestedSize = new Size(panel.ActualWidth, panel.ActualHeight);
        }
    }
}
