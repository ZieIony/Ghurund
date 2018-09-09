using System;
using System.Windows;
using System.Windows.Controls;

namespace Ghurund.Controls.Workspace {
    [Serializable]
    public class WorkspaceState {
        public PeekState peekState = new PeekState();
        public DockState dockState = new DockState();
    }

    [Serializable]
    public class PeekPanelState {
        public string className;
        public PeekSide side;
        internal Size size;
    }

    [Serializable]
    public class PeekState {
        public PeekPanelState[] peekPanelStates ;
    }

    [Serializable]
    public class SplitState {
        public DockState panel1, panel2;
        public string panel1Size, panel2Size;
        public Orientation orientation;
    }

    [Serializable]
    public class TabState {
        public string className;
        public object controlState;
    }

    [Serializable]
    public class DockState {
        public SplitState splitState;
        public TabState[] tabStates;
    }
}