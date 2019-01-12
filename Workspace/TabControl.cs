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
            //AddHandler(GotFocusEvent, new RoutedEventHandler(gotFocus));
            AddHandler(LostFocusEvent, new RoutedEventHandler(lostFocus));
            AddHandler(MouseDownEvent, new RoutedEventHandler(gotFocus));
            AddHandler(TitleBar.WindowActionEvent, new WindowActionEventHandler(titleBar_WindowAction));
        }

        private void titleBar_WindowAction(object sender, WindowActionEventArgs args) {
            if (args.Action == WindowAction.Close) {
                if (args.DockableControls != null) {    // close on a single tab
                    foreach (object item in Items) {
                        if (((item as EditorTab).Content as EditorPanel).Content == args.DockableControls.Controls[0].Control) {
                            Items.Remove(item);
                            args.Handled = true;
                            return;
                        }
                    }
                }
            }else if(args.Action==WindowAction.Undock){
                
            }
        }

        private void gotFocus(object sender, RoutedEventArgs args) {
            TitleBar titleBar = Extensions.FindVisualChildByName<TitleBar>(this, "titleBar");
            if (titleBar != null)
                titleBar.IsParentFocused = true;
            Focus();
        }

        private void lostFocus(object sender, RoutedEventArgs args) {
            TitleBar titleBar = Extensions.FindVisualChildByName<TitleBar>(this, "titleBar");
            if (titleBar != null)
                titleBar.IsParentFocused = false;
        }

        public void Save(DockState state) {
            state.tabStates = new TabState[Items.Count];
            for (int i = 0; i < Items.Count; i++) {
                var tab = Items[i] as EditorTab;
                var panel = tab.Content as EditorPanel;
                state.tabStates[i] = new TabState {
                    className = panel.Content.GetType().AssemblyQualifiedName
                };
                if (panel.Content is IStateControl)
                    state.tabStates[i].controlState = (panel.Content as IStateControl).Save();
            }
        }

        public void Restore(DockState state, IDockableControlFactory factory) {
            foreach (TabState tabState in state.tabStates) {
                Type t = Type.GetType(tabState.className);
                IDockableControl control = factory.MakeControl(t);
                if (control is IStateControl)
                    (control as IStateControl).Restore(tabState.controlState);
                var tab = new EditorTab(control);
                Items.Add(tab);
            }
        }
    }
}
