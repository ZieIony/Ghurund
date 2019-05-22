using System;
using System.Collections.Generic;
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

    public class Title {
        public string Short { get; set; }
        public string Long { get; set; }

        public Title(string both) {
            Short = both;
            Long = both;
        }

        public Title(string shortTitle, string longTitle) {
            Short = shortTitle;
            Long = longTitle;
        }
    }

    public interface IDockablePanel: IDisposable {
        ImageSource Icon { get; }
        Control Control { get; }
        Title Title { get; }
    }

    public class RoutedSelectionChangedEventArgs: RoutedEventArgs {
        public List<object> Items { get; set; }

        public RoutedSelectionChangedEventArgs(List<object> items, RoutedEvent routedEvent) : base(routedEvent) {
            Items = items;
        }
    }

    public delegate void RoutedSelectionChangedEventHandler(object sender, RoutedSelectionChangedEventArgs e);

    public interface IToolPanel: IDockablePanel {
        List<object> SelectedItems { get; set; }
    }

    public interface IDocumentPanel: IToolPanel {
        bool NeedsSaving { get; }
        bool Save(string fileName = null);
        bool Load(string fileName);
    }

    public interface IDockablePanelFactory {
        IDockablePanel MakePanel(Type type);
    }

    public class DockableGroup {
        public IDockablePanel[] Panels { get; }
        public Size SuggestedSize { get; }

        public DockableGroup(IDockablePanel panel, Size? suggestedSize = null) : this(new IDockablePanel[] { panel }, suggestedSize) {
        }

        public DockableGroup(IDockablePanel[] panels, Size? suggestedSize = null) {
            Panels = panels;
            SuggestedSize = suggestedSize ?? new Size(200, 400);
        }

        public DockableGroup(IDockablePanel panel) {
            Panels = new IDockablePanel[] { panel };
            SuggestedSize = new Size(panel.Control.ActualWidth, panel.Control.ActualHeight);
        }

        public DockableGroup(EditorPanel panel) {
            Panels = new IDockablePanel[] { panel.Content as IDockablePanel };
            SuggestedSize = new Size(panel.ActualWidth, panel.ActualHeight);
        }
    }

}
