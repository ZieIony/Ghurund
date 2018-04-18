namespace Ghurund.Editor.Docking {
	partial class RootDockPanel {
		/// <summary> 
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary> 
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing) {
			if (disposing && (components != null)) {
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Component Designer generated code

		/// <summary> 
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent() {
            this.childDockPanel = new Ghurund.Editor.Docking.ChildDockPanel();
            this.SuspendLayout();
            // 
            // childDockPanel
            // 
            this.childDockPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.childDockPanel.Location = new System.Drawing.Point(0, 0);
            this.childDockPanel.Name = "childDockPanel";
            this.childDockPanel.Size = new System.Drawing.Size(540, 398);
            this.childDockPanel.SplitContainer = null;
            this.childDockPanel.TabIndex = 1;
            // 
            // RootDockPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.childDockPanel);
            this.Name = "RootDockPanel";
            this.Size = new System.Drawing.Size(540, 398);
            this.ResumeLayout(false);

		}

		#endregion

		private ChildDockPanel childDockPanel;
    }
}
