using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace WebcamDrumsInvoker
{
    public partial class Invoker : Form
    {
        const String levelGeneratorFilepath = "Example.py";
        const String songListFilename = "MUSIC_FILE.txt";
        String gameModulePath = "WEBCAM_DRUMS.exe";

        public Invoker()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private void bAddMusic_Click(object sender, EventArgs e)
        {
            // Add locations of song files to master list.
            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                StreamWriter w = new StreamWriter(songListFilename, true);
                foreach (String file in openFileDialog1.FileNames)
                {
                    w.WriteLine(">" + file);
                }
                w.Close();
            }

            // Run Nikhil's MATLAB code to generate new levels.
            System.Diagnostics.Process.Start(levelGeneratorFilepath);

            MessageBox.Show("New levels were successfully created.");
        }

        private void bStart_Click(object sender, EventArgs e)
        {
            // Start Pat's game module.

            int difficulty = cbLevel.SelectedIndex;
            if (difficulty != 0 && difficulty != 1 && difficulty != 2)
            {
                difficulty = 0;
            }
            String args = songListFilename + " " + difficulty;
            System.Diagnostics.Process.Start(gameModulePath, args);
        }
    }
}
