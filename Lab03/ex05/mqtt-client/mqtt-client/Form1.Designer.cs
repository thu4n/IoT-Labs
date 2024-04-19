namespace mqtt_client
{
    partial class MainForm
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
            this.connectBtn = new System.Windows.Forms.Button();
            this.subscribeTB = new System.Windows.Forms.TextBox();
            this.subscribeLabel = new System.Windows.Forms.Label();
            this.publishLabel = new System.Windows.Forms.Label();
            this.publishTB = new System.Windows.Forms.TextBox();
            this.brokerTB = new System.Windows.Forms.TextBox();
            this.brokerLabel = new System.Windows.Forms.Label();
            this.subRcvTB = new System.Windows.Forms.TextBox();
            this.pubNotiTB = new System.Windows.Forms.TextBox();
            this.subRcvLabel = new System.Windows.Forms.Label();
            this.pubNotiLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // connectBtn
            // 
            this.connectBtn.Location = new System.Drawing.Point(35, 150);
            this.connectBtn.Name = "connectBtn";
            this.connectBtn.Size = new System.Drawing.Size(322, 30);
            this.connectBtn.TabIndex = 0;
            this.connectBtn.Text = "Connect to Broker with the above options";
            this.connectBtn.UseVisualStyleBackColor = true;
            this.connectBtn.Click += new System.EventHandler(this.connectBtn_Click);
            // 
            // subscribeTB
            // 
            this.subscribeTB.Location = new System.Drawing.Point(213, 66);
            this.subscribeTB.Name = "subscribeTB";
            this.subscribeTB.Size = new System.Drawing.Size(144, 22);
            this.subscribeTB.TabIndex = 1;
            // 
            // subscribeLabel
            // 
            this.subscribeLabel.AutoSize = true;
            this.subscribeLabel.Location = new System.Drawing.Point(32, 66);
            this.subscribeLabel.Name = "subscribeLabel";
            this.subscribeLabel.Size = new System.Drawing.Size(121, 16);
            this.subscribeLabel.TabIndex = 2;
            this.subscribeLabel.Text = "Topic to subscribe:";
            // 
            // publishLabel
            // 
            this.publishLabel.AutoSize = true;
            this.publishLabel.Location = new System.Drawing.Point(32, 109);
            this.publishLabel.Name = "publishLabel";
            this.publishLabel.Size = new System.Drawing.Size(105, 16);
            this.publishLabel.TabIndex = 3;
            this.publishLabel.Text = "Topic to publish:";
            // 
            // publishTB
            // 
            this.publishTB.Location = new System.Drawing.Point(213, 109);
            this.publishTB.Name = "publishTB";
            this.publishTB.Size = new System.Drawing.Size(144, 22);
            this.publishTB.TabIndex = 4;
            // 
            // brokerTB
            // 
            this.brokerTB.Location = new System.Drawing.Point(213, 29);
            this.brokerTB.Name = "brokerTB";
            this.brokerTB.Size = new System.Drawing.Size(144, 22);
            this.brokerTB.TabIndex = 5;
            this.brokerTB.TextChanged += new System.EventHandler(this.brokerTB_TextChanged);
            // 
            // brokerLabel
            // 
            this.brokerLabel.AutoSize = true;
            this.brokerLabel.Location = new System.Drawing.Point(32, 26);
            this.brokerLabel.Name = "brokerLabel";
            this.brokerLabel.Size = new System.Drawing.Size(136, 16);
            this.brokerLabel.TabIndex = 6;
            this.brokerLabel.Text = "URL of MQTT Broker:";
            // 
            // subRcvTB
            // 
            this.subRcvTB.AcceptsReturn = true;
            this.subRcvTB.Location = new System.Drawing.Point(35, 235);
            this.subRcvTB.Multiline = true;
            this.subRcvTB.Name = "subRcvTB";
            this.subRcvTB.ReadOnly = true;
            this.subRcvTB.Size = new System.Drawing.Size(322, 226);
            this.subRcvTB.TabIndex = 7;
            // 
            // pubNotiTB
            // 
            this.pubNotiTB.AcceptsReturn = true;
            this.pubNotiTB.Location = new System.Drawing.Point(398, 235);
            this.pubNotiTB.Multiline = true;
            this.pubNotiTB.Name = "pubNotiTB";
            this.pubNotiTB.ReadOnly = true;
            this.pubNotiTB.Size = new System.Drawing.Size(322, 226);
            this.pubNotiTB.TabIndex = 8;
            // 
            // subRcvLabel
            // 
            this.subRcvLabel.AutoSize = true;
            this.subRcvLabel.Location = new System.Drawing.Point(32, 206);
            this.subRcvLabel.Name = "subRcvLabel";
            this.subRcvLabel.Size = new System.Drawing.Size(126, 16);
            this.subRcvLabel.TabIndex = 9;
            this.subRcvLabel.Text = "<Topic subscribed>";
            // 
            // pubNotiLabel
            // 
            this.pubNotiLabel.AutoSize = true;
            this.pubNotiLabel.Location = new System.Drawing.Point(395, 206);
            this.pubNotiLabel.Name = "pubNotiLabel";
            this.pubNotiLabel.Size = new System.Drawing.Size(120, 16);
            this.pubNotiLabel.TabIndex = 10;
            this.pubNotiLabel.Text = "<Topic publishing>";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(741, 473);
            this.Controls.Add(this.pubNotiLabel);
            this.Controls.Add(this.subRcvLabel);
            this.Controls.Add(this.pubNotiTB);
            this.Controls.Add(this.subRcvTB);
            this.Controls.Add(this.brokerLabel);
            this.Controls.Add(this.brokerTB);
            this.Controls.Add(this.publishTB);
            this.Controls.Add(this.publishLabel);
            this.Controls.Add(this.subscribeLabel);
            this.Controls.Add(this.subscribeTB);
            this.Controls.Add(this.connectBtn);
            this.Name = "MainForm";
            this.Text = "MainForm";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button connectBtn;
        private System.Windows.Forms.TextBox subscribeTB;
        private System.Windows.Forms.Label subscribeLabel;
        private System.Windows.Forms.Label publishLabel;
        private System.Windows.Forms.TextBox publishTB;
        private System.Windows.Forms.TextBox brokerTB;
        private System.Windows.Forms.Label brokerLabel;
        private System.Windows.Forms.TextBox subRcvTB;
        private System.Windows.Forms.TextBox pubNotiTB;
        private System.Windows.Forms.Label subRcvLabel;
        private System.Windows.Forms.Label pubNotiLabel;
    }
}

