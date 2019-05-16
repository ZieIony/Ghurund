using System;
using System.Collections.Specialized;
using System.IO;
using System.Text;
using System.Windows;
using System.Windows.Controls;

namespace Ghurund.Controls.Workspace {
    public class TabControl : System.Windows.Controls.TabControl {

        protected override void OnItemsChanged(NotifyCollectionChangedEventArgs e) {
            base.OnItemsChanged(e);
            if (Items.Count == 1) {
                (Items[0] as TabItem).Visibility = Visibility.Collapsed;
            } else {
                foreach (object item in Items) {
                    (item as TabItem).Visibility = Visibility.Visible;
                }
            }
        }

        static TabControl() {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(TabControl), new FrameworkPropertyMetadata(typeof(TabControl)));
        }

        public TabControl() {
            Style = FindResource("Workspace.TabControl") as Style;
            AddHandler(TitleBar.WindowActionEvent, new WindowActionEventHandler(titleBar_WindowAction));
        }

        private void titleBar_WindowAction(object sender, WindowActionEventArgs args) {
            if (args.Action == WindowAction.Close) {
                if (args.DockableControls != null) {    // close on a single tab
                    foreach (object item in Items) {
                        if (((item as EditorTab).Content as EditorPanel).Content == args.DockableControls.Panels[0].Control) {
                            Items.Remove(item);
                            args.Handled = true;
                            return;
                        }
                    }
                }
            } else if (args.Action == WindowAction.Undock) {

            }
        }

        protected override void OnSelectionChanged(SelectionChangedEventArgs e) {
            base.OnSelectionChanged(e);
            if (SelectedItem != null)
                RaiseEvent(new PanelActionEventArgs((SelectedItem as EditorTab).Content as EditorPanel, this, WorkspacePanel.PanelFocusedEvent));
        }

        public void Save(DockState state) {
            state.tabStates = new TabState[Items.Count];
            for (int i = 0; i < Items.Count; i++) {
                var tab = Items[i] as EditorTab;
                var panel = tab.Content as EditorPanel;
                state.tabStates[i] = new TabState {
                    ClassName = panel.Content.GetType().AssemblyQualifiedName
                };
                if (panel.Content is IStateControl) {
                    using (MemoryStream stream = new MemoryStream()) {
                        (panel.Content as IStateControl).SaveState(stream);
                        state.tabStates[i].ControlState = Encoding.UTF8.GetString(stream.ToArray());
                    }
                }
            }
        }

        public void Restore(DockState state, IDockablePanelFactory factory) {
            foreach (TabState tabState in state.tabStates) {
                Type t = Type.GetType(tabState.ClassName);
                IDockablePanel control = factory.MakePanel(t);
                if (control is IStateControl) {
                    using (MemoryStream stream = new MemoryStream(Encoding.UTF8.GetBytes(tabState.ControlState)))
                        (control as IStateControl).RestoreState(stream);
                }
                var tab = new EditorTab(control);
                Items.Add(tab);
            }
        }
    }
}
