namespace Ghurund.Editor.Docking {
    public interface IDockContainer {
		void dock(DockableTabPage page, DockSide dockSide = DockSide.Center);

		void dock(System.Windows.Forms.Control control, DockSide dockSide = DockSide.Center);

		void flatten();

		void undock(DockableTabPage page);
	}
}
