using System;
using System.Collections.Specialized;
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
            AddHandler(TitleBar.WindowDraggedEvent, new WindowEventHandler(titleBar_WindowDragged));
            AddHandler(GotFocusEvent, new RoutedEventHandler(gotFocus));
            AddHandler(LostFocusEvent, new RoutedEventHandler(lostFocus));
        }

        private void gotFocus(object sender, RoutedEventArgs args) {
            TitleBar titleBar = Extensions.FindVisualChildByName<TitleBar>(this, "titleBar");
            if (titleBar != null)
                titleBar.IsParentFocused = true;
        }

        private void lostFocus(object sender, RoutedEventArgs args) {
            TitleBar titleBar = Extensions.FindVisualChildByName<TitleBar>(this, "titleBar");
            if (titleBar != null)
                titleBar.IsParentFocused = false;
        }

        private void titleBar_WindowDragged(object sender, WindowEventArgs args) {
            var controls = new IDockableControl[Items.Count];
            for (int i = 0; i < Items.Count; i++) {
                var tab = Items[i] as EditorTab;
                var panel = tab.Content as EditorPanel;
                controls[i] = new DockableControl(panel.Content as Control, panel.Title);
            }
        }

        public void Save(DockState state) {
            state.tabStates = new TabState[Items.Count];
            for (int i = 0; i < Items.Count; i++) {
                var tab = Items[i] as EditorTab;
                var panel = tab.Content as EditorPanel;
                state.tabStates[i] = new TabState {
                    className = panel.Content.GetType().AssemblyQualifiedName
                };
            }
        }

        public void Restore(DockState state, IDockableControlFactory factory) {
            foreach(TabState tabState in state.tabStates) {
                Type t = Type.GetType(tabState.className);
                IDockableControl control = factory.MakeControl(t);
                var tab = new EditorTab(control);
                Items.Add(tab);
            }
        }
    }
}
