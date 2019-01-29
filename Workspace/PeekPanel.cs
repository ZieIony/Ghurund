using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;

namespace Ghurund.Controls.Workspace {
    public class PeekablePanel {
        public IDockablePanel DockableControl { get; private set; }

        public PeekSide Side { get; private set; }

        public Size Size { get; }

        public PeekablePanel(IDockablePanel control, PeekSide side, Size suggestedSize) {
            DockableControl = control;
            Side = side;
            Size = suggestedSize;
        }
    }

    public class PeekPanel : ContentControl {

        private Dictionary<PeekSide, StackPanel> panels = new Dictionary<PeekSide, StackPanel>();
        private SplitPanel peekedContent;
        private Dictionary<Button, PeekablePanel> peekablePanels = new Dictionary<Button, PeekablePanel>();
        private Button peekedControlButton;
        private Label contentHider;

        static PeekPanel() {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(PeekPanel), new FrameworkPropertyMetadata(typeof(PeekPanel)));
        }

        public PeekPanel() {
        }

        public void Add(DockableGroup controls, PeekSide side) {
            foreach (IDockablePanel control in controls.Panels)
                Add(control, controls.SuggestedSize, side);
        }

        public void Add(IDockablePanel control, Size suggestedSize, PeekSide side) {
            StackPanel panel = panels[side];
            var button = new PeekButton {
                Text = control.Title.Short,
                Icon = control.Icon,
                Orientation = side == PeekSide.Left || side == PeekSide.Right ? Orientation.Vertical : Orientation.Horizontal
            };
            peekablePanels.Add(button, new PeekablePanel(control, side, suggestedSize));
            button.Click += Button_Click;
            panel.Children.Add(button);
        }

        private void Button_Click(object sender, RoutedEventArgs e) {
            if (peekedControlButton == sender) {
                HideContent();
                return;
            }

            peekedControlButton = sender as Button;
            var peekedPanel = peekablePanels[peekedControlButton];
            var side = peekedPanel.Side;
            peekedContent.Orientation = side == PeekSide.Bottom || side == PeekSide.Top ? Orientation.Vertical : Orientation.Horizontal;
            if (side == PeekSide.Top || side == PeekSide.Left) {
                peekedContent.Panel1 = new EditorPanel(peekedPanel.DockableControl);
                peekedContent.Panel1.BorderThickness = new Thickness(1);
                peekedContent.Panel1.BorderBrush = BorderBrush;
                peekedContent.Panel1Size = new GridLength(side == PeekSide.Top ? peekedPanel.Size.Height : peekedPanel.Size.Width);
                peekedContent.Panel2 = contentHider;
            } else {
                peekedContent.Panel1 = contentHider;
                peekedContent.Panel2 = new EditorPanel(peekedPanel.DockableControl);
                peekedContent.Panel2.BorderThickness = new Thickness(1);
                peekedContent.Panel2.BorderBrush = BorderBrush;
                peekedContent.Panel2Size = new GridLength(side == PeekSide.Bottom ? peekedPanel.Size.Height : peekedPanel.Size.Width);
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
            var control = peekablePanels[peekedControlButton];
            peekablePanels.Remove(peekedControlButton);
            panels[control.Side].Children.Remove(peekedControlButton);
            // TODO: close panel properly
            HideContent();
        }

        public void Save(PeekState peekState) {
            peekState.peekPanelStates = new PeekPanelState[peekablePanels.Count];
            int i = 0;
            foreach (PeekablePanel control in peekablePanels.Values) {
                peekState.peekPanelStates[i].className = control.DockableControl.GetType().AssemblyQualifiedName;
                peekState.peekPanelStates[i].side = control.Side;
                peekState.peekPanelStates[i].size = control.Size;
                i++;
            }
        }

        public void Clear() {
            foreach (StackPanel panel in panels.Values)
                panel.Children.Clear();
            peekablePanels.Clear();
            HideContent();
        }

        public void Restore(PeekState peekState, IDockablePanelFactory factory) {
            Clear();
            foreach (PeekPanelState state in peekState.peekPanelStates) {
                Type t = Type.GetType(state.className);
                IDockablePanel control = factory.MakePanel(t);
                Add(control, state.size, state.side);
            }
        }
    }
}
