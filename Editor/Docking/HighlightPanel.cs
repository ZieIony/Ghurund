using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace Ghurund.Editor.Docking {
    public partial class DockHighlightPanel : Form {
		public DockHighlightPanel() {
			InitializeComponent();

			TransparencyKey = Color.White;
			BackColor = Color.White;
		}

		protected override CreateParams CreateParams {
			get {
				CreateParams cp = base.CreateParams;
				cp.ExStyle |= 0x00000020; //WS_EX_TRANSPARENT  
				return cp;
			}
		}

        [Browsable(false)]
        public DockSpot SelectedDock { get; set; } = null;

		protected override void OnMouseMove(MouseEventArgs e) {
			base.OnMouseMove(e);
			DockSpot prevSide = SelectedDock;
			Point mousePos = PointToClient(e.Location);

			SelectedDock = null;
			foreach (DockSpot spot in DockSpots) {
				Rectangle r = spot.hitRect;
				if (mousePos.X > r.Left && mousePos.X < r.Right && mousePos.Y > r.Top && mousePos.Y < r.Bottom) {
					SelectedDock = spot;
					break;
				}
			}
			if (prevSide != SelectedDock) {
				Refresh();
			}
		}

		protected override void OnPaint(PaintEventArgs e) {
			base.OnPaint(e);
			//e.Graphics.Clear(Color.Transparent);
			Color color = Color.FromArgb(127, ForeColor.R, ForeColor.G, ForeColor.B);

			if(SelectedDock!=null)
				e.Graphics.FillRectangle(new SolidBrush(color), SelectedDock.drawRect);
		}

		internal void dockingMsg(ref Message m) {
			OnMouseMove(new MouseEventArgs(MouseButtons, 1, MousePosition.X, MousePosition.Y, 0));
		}

		/*
				internal void dockMsg(ref Message m) {
					if (SelectedDock != DockSide.None) {
					}
				}
		*/



		public List<DockSpot> DockSpots { get; set; }
	}
}
