namespace WebcamDrumsInvoker
{
    partial class Invoker
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.bAddMusic = new System.Windows.Forms.Button();
            this.bStart = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.cbLevel = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            this.openFileDialog1.Multiselect = true;
            // 
            // bAddMusic
            // 
            this.bAddMusic.Location = new System.Drawing.Point(23, 197);
            this.bAddMusic.Name = "bAddMusic";
            this.bAddMusic.Size = new System.Drawing.Size(100, 25);
            this.bAddMusic.TabIndex = 0;
            this.bAddMusic.Text = "Add New Songs";
            this.bAddMusic.UseVisualStyleBackColor = true;
            this.bAddMusic.Click += new System.EventHandler(this.bAddMusic_Click);
            // 
            // bStart
            // 
            this.bStart.Location = new System.Drawing.Point(296, 197);
            this.bStart.Name = "bStart";
            this.bStart.Size = new System.Drawing.Size(100, 25);
            this.bStart.TabIndex = 2;
            this.bStart.Text = "Play Game";
            this.bStart.UseVisualStyleBackColor = true;
            this.bStart.Click += new System.EventHandler(this.bStart_Click);
            // 
            // label1
            // 
            this.label1.Font = new System.Drawing.Font("Jivetalk", 48F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(56, 8);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(309, 174);
            this.label1.TabIndex = 2;
            this.label1.Text = "Webcam Drummer";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // cbLevel
            // 
            this.cbLevel.FormattingEnabled = true;
            this.cbLevel.Items.AddRange(new object[] {
            "Standard",
            "Expert",
            "Insane"});
            this.cbLevel.Location = new System.Drawing.Point(154, 200);
            this.cbLevel.Name = "cbLevel";
            this.cbLevel.Size = new System.Drawing.Size(110, 21);
            this.cbLevel.TabIndex = 1;
            this.cbLevel.Text = "Select Difficulty:";
            // 
            // Invoker
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(420, 264);
            this.Controls.Add(this.cbLevel);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.bStart);
            this.Controls.Add(this.bAddMusic);
            this.Name = "Invoker";
            this.Text = "Webcam Drummer";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.Button bAddMusic;
        private System.Windows.Forms.Button bStart;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cbLevel;
    }
}

