using System;
using System.IO;
using System.Windows;
using System.Windows.Controls;

namespace Ghurund.Controls.Workspace {

    public interface IStateControl {
        void SaveState(Stream stream);

        void RestoreState(Stream stream);
    }

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
        public string ClassName;
        public string ControlState;
    }

    [Serializable]
    public class DockState {
        public SplitState SplitState;
        public TabState[] tabStates;
    }
}