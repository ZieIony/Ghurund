using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System;

namespace Ghurund.Controls.Workspace {
    public class DockPanel: ContentControl {

        protected TabControl tabControl;
        protected SplitPanel splitContainer;
        private DockSide? side = null;

        public bool IsEmpty {
            get {
                return (tabControl == null && splitContainer == null) || (tabControl != null && tabControl.Items.Count == 0);
            }
        }

        public virtual List<DockSpot> DockSpots {
            get {
                List<DockSpot> list = new List<DockSpot>();
                if (splitContainer == null) {
                    Point p = PointToScreen(new Point());
                    list.Add(new DockSpot(new Rect(p.X, p.Y, ActualWidth / 3, ActualHeight),
                        new Rect(p.X, p.Y, ActualWidth, ActualHeight), DockSide.Left, this));
                    list.Add(new DockSpot(new Rect(p.X + ActualWidth * 2 / 3, p.Y, ActualWidth / 3, ActualHeight),
                        new Rect(p.X, p.Y, ActualWidth, ActualHeight), DockSide.Right, this));
                    list.Add(new DockSpot(new Rect(p.X, p.Y, ActualWidth, ActualHeight / 3),
                        new Rect(p.X, p.Y, ActualWidth, ActualHeight), DockSide.Top, this));
                    list.Add(new DockSpot(new Rect(p.X, p.Y + ActualHeight * 2 / 3, ActualWidth, ActualHeight / 3),
                        new Rect(p.X, p.Y, ActualWidth, ActualHeight), DockSide.Bottom, this));
                    list.Add(new DockSpot(new Rect(p.X, p.Y, ActualWidth, ActualHeight),
                        new Rect(p.X, p.Y, ActualWidth, ActualHeight), DockSide.Center, this));
                } else {
                    DockPanel child1 = splitContainer.Panel1 as DockPanel;
                    DockPanel child2 = splitContainer.Panel2 as DockPanel;
                    list.AddRange(child1.DockSpots);
                    list.AddRange(child2.DockSpots);
                }
                return list;
            }
        }

        public DockPanel() {
            AddHandler(TitleBar.WindowActionEvent, new WindowActionEventHandler(titleBar_WindowAction));
        }

        private void titleBar_WindowAction(object sender, WindowActionEventArgs args) {
            if (!args.ActionHandled) {
                if (args.DockableControls == null) {
                    var controls = new IDockablePanel[tabControl.Items.Count];
                    for (int i = 0; i < tabControl.Items.Count; i++) {
                        var tab = tabControl.Items[i] as EditorTab;
                        var panel = tab.Content as EditorPanel;
                        controls[i] = panel.Content as IDockablePanel;
                    }
                    args.DockableControls = new DockableGroup(controls, new Size(tabControl.ActualWidth, tabControl.ActualHeight));
                    undockAll();
                } else {
                    undock(args.DockableControls.Panels);
                }
                args.ActionHandled = true;
            }
        }

        internal void Save(DockState state) {
            if (splitContainer != null) {
                DockState statePanel1 = new DockState();
                var panel1 = splitContainer.Panel1 as DockPanel;
                panel1.Save(statePanel1);

                DockState statePanel2 = new DockState();
                var panel2 = splitContainer.Panel2 as DockPanel;
                panel2.Save(statePanel2);

                GridLengthConverter converter = new GridLengthConverter();
                string panel1Size, panel2Size;
                if (splitContainer.Panel1Size.GridUnitType == GridUnitType.Star) {
                    panel1Size = converter.ConvertToString(splitContainer.Panel1Size);
                    panel2Size = (splitContainer.Orientation == Orientation.Vertical ? splitContainer.Panel2.ActualHeight : splitContainer.Panel2.ActualWidth).ToString();
                } else {
                    panel1Size = (splitContainer.Orientation == Orientation.Vertical ? splitContainer.Panel1.ActualHeight : splitContainer.Panel1.ActualWidth).ToString();
                    panel2Size = converter.ConvertToString(splitContainer.Panel2Size);
                }

                state.SplitState = new SplitState {
                    panel1 = statePanel1,
                    panel2 = statePanel2,
                    orientation = splitContainer.Orientation,
                    panel1Size = panel1Size,
                    panel2Size = panel2Size
                };
            } else if (tabControl != null) {
                tabControl.Save(state);
            }
        }

        public void Clear() {
            if (splitContainer != null) {
                if (splitContainer.Panel1 != null) {
                    (splitContainer.Panel1 as DockPanel).Clear();
                    splitContainer.Panel1 = null;
                }
                if (splitContainer.Panel2 != null) {
                    (splitContainer.Panel2 as DockPanel).Clear();
                    splitContainer.Panel2 = null;
                }
                splitContainer = null;
            }
            if (tabControl != null) {
                tabControl.Items.Clear();
                tabControl = null;
            }
            Content = null;
            side = null;
        }

        public void Restore(DockState state, IDockablePanelFactory factory) {
            Clear();
            if (state.SplitState != null) {
                var panel1 = new DockPanel();
                panel1.Restore(state.SplitState.panel1, factory);

                var panel2 = new DockPanel();
                panel2.Restore(state.SplitState.panel2, factory);

                GridLengthConverter converter = new GridLengthConverter();

                splitContainer = new SplitPanel {
                    Panel1 = panel1,
                    Panel2 = panel2,
                    Orientation = state.SplitState.orientation,
                    Panel1Size = (GridLength)converter.ConvertFromString(state.SplitState.panel1Size),
                    Panel2Size = (GridLength)converter.ConvertFromString(state.SplitState.panel2Size),
                };

                Content = splitContainer;
            } else if (state.tabStates != null) {
                tabControl = new TabControl();
                tabControl.Restore(state, factory);
                Content = tabControl;
            }
        }

        public void Dock(DockableGroup controls, DockSide side) {
            if (this.side == null) {
                if (side == DockSide.Center) {
                    dockCenter(controls);
                } else {
                    dockSide(controls, side);
                }
            } else if (this.side == DockSide.Center) {
                if (side == DockSide.Center) {
                    dockCenter(controls);
                } else {
                    dockSide(controls, side);
                }
            } else {
                if (this.side == side && !(this is RootDockPanel)) {
                    if (this.side == DockSide.Top || this.side == DockSide.Left) {
                        (splitContainer.Panel1 as DockPanel).Dock(controls, DockSide.Center);
                    } else {
                        (splitContainer.Panel2 as DockPanel).Dock(controls, DockSide.Center);
                    }
                } else if (side == DockSide.Center) {
                    if (this.side == DockSide.Top || this.side == DockSide.Left) {
                        (splitContainer.Panel2 as DockPanel).Dock(controls, DockSide.Center);
                    } else {
                        (splitContainer.Panel1 as DockPanel).Dock(controls, DockSide.Center);
                    }
                } else {
                    dockSide(controls, side);
                }
            }
        }

        private void dockCenter(DockableGroup controls) {
            if (tabControl == null) {
                tabControl = new TabControl();
                Content = tabControl;
                splitContainer = null;
            }

            foreach (IDockablePanel control in controls.Panels)
                tabControl.Items.Add(new EditorTab(control));
            side = DockSide.Center;
        }

        private void move(DockPanel dockPanel) {
            side = dockPanel.side;
            splitContainer = dockPanel.splitContainer;
            tabControl = dockPanel.tabControl;
            Content = dockPanel.Content;
        }

        private void dockSide(DockableGroup controls, DockSide side) {
            SplitPanel splitContainer = this.splitContainer;
            if (splitContainer == null || this.side != side || this is RootDockPanel) {
                splitContainer = new SplitPanel();
            }

            DockPanel child1 = new DockPanel();
            DockPanel child2 = new DockPanel();
            splitContainer.Panel1 = child1;
            splitContainer.Panel2 = child2;

            double size;
            if (side == DockSide.Left || side == DockSide.Right) {
                size = Math.Min(controls.SuggestedSize.Width, ActualWidth * 0.8);
            } else {
                splitContainer.Orientation = Orientation.Vertical;
                size = Math.Min(controls.SuggestedSize.Height, ActualHeight * 0.8);
            }

            if (side == DockSide.Left || side == DockSide.Top) {
                splitContainer.Panel1Size = new GridLength(size);
                child1.Dock(controls, DockSide.Center);
                child2.move(this);
            } else {
                splitContainer.Panel2Size = new GridLength(size);
                child2.Dock(controls, DockSide.Center);
                child1.move(this);
            }

            Content = splitContainer;
            this.splitContainer = splitContainer;
            tabControl = null;
            this.side = side;
        }

        private void undock(IDockablePanel[] controls) {
            if (tabControl.Items.Count == 0)
                return;

            List<EditorTab> tabsToRemove = new List<EditorTab>();

            foreach (IDockablePanel control in controls) {
                foreach (EditorTab tab in tabControl.Items) {
                    var panel = tab.Content as EditorPanel;
                    if (panel.Content == control.Control)
                        tabsToRemove.Add(tab);
                }
            }

            foreach (EditorTab tab in tabsToRemove)
                tabControl.Items.Remove(tab);

            if (tabControl.Items.Count == 0) {
                Content = null;
                tabControl = null;
            }
        }

        private void undockAll() {
            List<EditorTab> tabsToRemove = new List<EditorTab>();

            foreach (EditorTab tab in tabControl.Items)
                tabsToRemove.Add(tab);

            foreach (EditorTab tab in tabsToRemove)
                tabControl.Items.Remove(tab);

            Content = null;
            tabControl = null;
        }

        internal void flatten() {
            if (Content == tabControl)
                return;

            DockPanel child1 = splitContainer.Panel1 as DockPanel;
            child1.flatten();
            DockPanel child2 = splitContainer.Panel2 as DockPanel;
            child2.flatten();

            if (child1.IsEmpty) {
                move(child2);
            } else if (child2.IsEmpty) {
                move(child1);
            }
        }

    }
}
