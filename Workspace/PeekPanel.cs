using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;

namespace Ghurund.Controls.Workspace {
    public class PeekPanel : ContentControl {

        private Dictionary<PeekSide, StackPanel> panels = new Dictionary<PeekSide, StackPanel>();
        private SplitPanel peekedContent;
        private Dictionary<Button, PeekableControl> dockedControls = new Dictionary<Button, PeekableControl>();
        private Button peekedControlButton;
        private Label contentHider;

        static PeekPanel() {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(PeekPanel), new FrameworkPropertyMetadata(typeof(PeekPanel)));
        }

        public PeekPanel() {
        }

        public void Add(DockableControls controls, PeekSide side) {
            foreach (IDockableControl control in controls.Controls)
                Add(control, controls.SuggestedSize, side);
        }

        public void Add(IDockableControl control, Size suggestedSize, PeekSide side) {
            StackPanel panel = panels[side];
            var button = new PeekButton {
                Text = control.Title.Short,
                Icon = control.Icon,
                Orientation = side == PeekSide.Left || side == PeekSide.Right ? Orientation.Vertical : Orientation.Horizontal
            };
            dockedControls.Add(button, new PeekableControl(control, side, suggestedSize));
            button.Click += Button_Click;
            panel.Children.Add(button);
        }

        private void Button_Click(object sender, RoutedEventArgs e) {
            if (peekedControlButton == sender) {
                HideContent();
                return;
            }

            peekedControlButton = sender as Button;
            var peekedControl = dockedControls[peekedControlButton];
            var side = peekedControl.Side;
            peekedContent.Orientation = side == PeekSide.Bottom || side == PeekSide.Top ? Orientation.Vertical : Orientation.Horizontal;
            if (side == PeekSide.Top || side == PeekSide.Left) {
                peekedContent.Panel1 = new EditorPanel(peekedControl);
                peekedContent.Panel1.BorderThickness = new Thickness(1);
                peekedContent.Panel1.BorderBrush = BorderBrush;
                peekedContent.Panel1Size = new GridLength(side == PeekSide.Top ? peekedControl.Size.Height : peekedControl.Size.Width);
                peekedContent.Panel2 = contentHider;
            } else {
                peekedContent.Panel1 = contentHider;
                peekedContent.Panel2 = new EditorPanel(peekedControl);
                peekedContent.Panel2.BorderThickness = new Thickness(1);
                peekedContent.Panel2.BorderBrush = BorderBrush;
                peekedContent.Panel2Size = new GridLength(side == PeekSide.Bottom ? peekedControl.Size.Height : peekedControl.Size.Width);
            }
            peekedContent.Visibility = Visibility.Visible;
        }

        public override void OnApplyTemplate() {
            base.OnApplyTemplate();
            panels.Add(PeekSide.Left, GetTemplateChild("leftPanel") as StackPanel);
            panels.Add(PeekSide.Right, GetTemplateChild("rightPanel") as StackPanel);
            panels.Add(PeekSide.Top, GetTemplateChild("topPanel") as StackPanel);
            panels.Add(PeekSide.Bottom, GetTemplateChild("bottomPanel") as StackPanel);
            peekedContent = GetTemplateChild("peekedContent") as SplitPanel;
            contentHider = new Label();
            contentHider.PreviewMouseDown += contentHider_PreviewMouseDown;
        }

        private void contentHider_PreviewMouseDown(object sender, RoutedEventArgs e) {
            HideContent();
        }

        public void HideContent() {
            peekedContent.Visibility = Visibility.Collapsed;
            peekedContent.Panel1 = null;
            peekedContent.Panel2 = null;
            peekedControlButton = null;
        }

        public bool IsOpen { get => peekedContent.Visibility != Visibility.Collapsed; }

        public void ClosePeeked() {
            var control = dockedControls[peekedControlButton];
            dockedControls.Remove(peekedControlButton);
            panels[control.Side].Children.Remove(peekedControlButton);
            // TODO: close panel properly
            HideContent();
        }

        public void Save(PeekState peekState) {
            peekState.peekPanelStates = new PeekPanelState[dockedControls.Count];
            int i = 0;
            foreach (PeekableControl control in dockedControls.Values) {
                peekState.peekPanelStates[i].className = control.DockableControl.GetType().AssemblyQualifiedName;
                peekState.peekPanelStates[i].side = control.Side;
                peekState.peekPanelStates[i].size = control.Size;
                i++;
            }
        }

        public void Clear() {
            foreach (StackPanel panel in panels.Values)
                panel.Children.Clear();
            dockedControls.Clear();
            HideContent();
        }

        public void Restore(PeekState peekState, IDockableControlFactory factory) {
            Clear();
            foreach (PeekPanelState state in peekState.peekPanelStates) {
                Type t = Type.GetType(state.className);
                IDockableControl control = factory.MakeControl(t);
                Add(control, state.size, state.side);
            }
        }
    }
}
