namespace Editor.Docking {
    partial class TitleBar {
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
            this.systemButton1 = new Ghurund.Editor.Control.SystemButton();
            this.SuspendLayout();
            // 
            // systemButton1
            // 
            this.systemButton1.Caption = System.Windows.Forms.CaptionButton.Help;
            this.systemButton1.Location = new System.Drawing.Point(39, 72);
            this.systemButton1.Name = "systemButton1";
            this.systemButton1.Size = new System.Drawing.Size(26, 23);
            this.systemButton1.TabIndex = 0;
            this.systemButton1.Text = "systemButton1";
            this.systemButton1.UseVisualStyleBackColor = true;
            // 
            // TitleBar
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.systemButton1);
            this.Name = "TitleBar";
            this.ResumeLayout(false);

        }

        #endregion

        private Ghurund.Editor.Control.SystemButton systemButton1;
    }
}
