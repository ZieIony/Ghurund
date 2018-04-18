namespace Ghurund.Editor.Docking {
    partial class CollapsedPagesContainer {
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
            this.rootDockPanel1 = new Ghurund.Editor.Docking.RootDockPanel();
            this.SuspendLayout();
            // 
            // rootDockPanel1
            // 
            this.rootDockPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.rootDockPanel1.DockSpots = null;
            this.rootDockPanel1.Location = new System.Drawing.Point(0, 0);
            this.rootDockPanel1.Name = "rootDockPanel1";
            this.rootDockPanel1.Size = new System.Drawing.Size(569, 405);
            this.rootDockPanel1.TabIndex = 6;
            // 
            // CollapsedPagesContainer
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.rootDockPanel1);
            this.Name = "CollapsedPagesContainer";
            this.Size = new System.Drawing.Size(569, 405);
            this.ResumeLayout(false);

        }

        #endregion
        private Ghurund.Editor.Docking.RootDockPanel rootDockPanel1;
    }
}
