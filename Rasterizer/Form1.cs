using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Rasterizer
{
    
    public partial class Form1 : Form
    {
        TextureBrush myBrush;
        int dots = 48;
        int buttonPressed = 0;


        public Form1()
        {
            InitializeComponent();
            this.DoubleBuffered = true;


        }
        List<Vector3> vertices = new List<Vector3>();
        List<Tuple<List<int>, Color>> polygons = new List<Tuple<List<int>, Color>>();
        float rotation;

        private void Form1_Load(object sender, EventArgs e)
        {
            //Create_Cube();
            //myBrush = new TextureBrush(new Bitmap(@"C: \Users\kenny\Downloads\MTIwNjA4NjMzOTU5NTgxMTk2.bmp"), System.Drawing.Drawing2D.WrapMode.Tile);
        }

        private void Create_Cube()
        {
            vertices.Clear();
            polygons.Clear();
            vertices.Add(new Vector3(-1, -1, -1));
            vertices.Add(new Vector3(1, -1, -1));
            vertices.Add(new Vector3(1, 1, -1));
            vertices.Add(new Vector3(-1, 1, -1));
            vertices.Add(new Vector3(-1, -1, 1));
            vertices.Add(new Vector3(1, -1, 1));
            vertices.Add(new Vector3(1, 1, 1));
            vertices.Add(new Vector3(-1, 1, 1));

            polygons.Add(new Tuple<List<int>, Color>(new List<int>() { 0, 1, 2, 3 }, Color.Green));
            polygons.Add(new Tuple<List<int>, Color>(new List<int>() { 4, 5, 6, 7 }, Color.Green));
            polygons.Add(new Tuple<List<int>, Color>(new List<int>() { 0, 4, 5, 1 }, Color.Green));
            polygons.Add(new Tuple<List<int>, Color>(new List<int>() { 2, 6, 7, 3 }, Color.Green));
        }

        //private void Create_Kegel()
        //{
        //    //vertices.Clear();
        //    vertices.Add(new Vector3(-1, 0, -1));
        //    vertices.Add(new Vector3(0, 2, 0));
        //    vertices.Add(new Vector3(1, 0, -1));
        //    vertices.Add(new Vector3(-1, 0, 1));
        //    vertices.Add(new Vector3(0, 2, 0));
        //    vertices.Add(new Vector3(1, 0, 1));

        //    vertices.Add(new Vector3(-1, 0, 1));
        //    vertices.Add(new Vector3(0, 2, 0));
        //    vertices.Add(new Vector3(1, 0, 1));

        //    //vertices.Add(new Vector3(-1, 1, -1));
        //    //vertices.Add(new Vector3(-1, -1, 1));
        //    //vertices.Add(new Vector3(1, -1, 1));
        //    //vertices.Add(new Vector3(1, 1, 1));
        //    //vertices.Add(new Vector3(-1, 1, 1));

        //    polygons.Add(new List<int>() { 0, 1, 2 });
        //    polygons.Add(new List<int>() { 3, 4, 5 });
        //    polygons.Add(new List<int>() { 0, 3, 5, 2 });
        //    //polygons.Add(new List<int>() { 2, 6, 7, 3 });
        //}

        private void Create_Pin()
        {
            vertices.Clear();
            polygons.Clear();
            for (int i = 0; i < dots; i++)
                {
                    vertices.Add(new Vector3((float)Math.Cos(i * ((360.0f / dots)/180 * Math.PI)), (float)Math.Sin(i * ((360.0f / dots)/180 * Math.PI)), (float)0));
                polygons.Add(new Tuple<List<int>, Color>(new List<int>() { i,(i+1) % dots }, Color.Blue));
            }
            vertices.Add(new Vector3(0, 0, 2));
            for(int t =0; t<dots;t++)
            {
                polygons.Add(new Tuple<List<int>, Color>(new List<int>() { t, dots}, Color.Blue));
            }
        }

        private void Create_Buis()
        {
            vertices.Clear();
            polygons.Clear();
            for (int k = 0; k < 2; k++)
            {
                for (int i = 0; i < dots ; i++)
                {
                    vertices.Add(new Vector3((float)Math.Cos(i * ((360.0f/ dots) / 180 * Math.PI)), (float)Math.Sin(i * ((360.0f/ dots) / 180 * Math.PI)), (float)k));
                    polygons.Add(new Tuple<List<int>, Color>(new List<int>() { i, (i + 1)% dots }, Color.Blue));
                    polygons.Add(new Tuple<List<int>, Color>(new List<int>() { i+dots, (i + 1) % dots +dots }, Color.Blue));
                }
            }
            for (int t = 0; t < dots; t++)
            {
                polygons.Add(new Tuple<List<int>, Color>(new List<int>() { t, t+dots }, Color.Blue));
            }
        }

        private void Create_Bol()
        {
            vertices.Clear();
            polygons.Clear();
            int slices = dots;
            int stacks = dots;
            for(int stack = 0; stack < stacks; ++stack)
            {
                for(int slice = 0; slice < slices; ++slice)
                {
                    double y = 2.0 * stack / stacks - 1.0;
                    double r = Math.Sqrt(1 - Math.Pow(y, 2));
                    double x = r * Math.Sin(2.0 * Math.PI * slice / slices);
                    double z = r * Math.Cos(2.0 * Math.PI * slice / slices);
                    vertices.Add(new Vector3((float)x, (float)y, (float)z));
                }
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
		{
            rotation += 0.01f;
			Invalidate();
		}

		private void Form1_Paint(object sender, PaintEventArgs e)
		{
			var g = e.Graphics;
			g.Clear(Color.Black);
			g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            Pen pen = new Pen(Color.PaleVioletRed, 1);

            Matrix m = Matrix.identity();

            m = m * Matrix.perspective((float)(Math.PI / 2), (float)Width/Height, 0.1f, 20f); 

            m = m * Matrix.translate(new Vector3(0, 0, -3 + (float)Math.Cos(rotation*8)));
    
            m = m * Matrix.rotation(rotation, new Vector3(0, 1, 0));
           m = m * Matrix.rotation((float)Math.Sin(rotation*4)*2, new Vector3(1, 0, 0));

            foreach (Vector3 v in vertices)
            {
                Vector3 vect = new Vector3();
                vect = m * v;

                vect.x = Width / 2 + vect.x / vect.z * Width / 2;
                vect.y = Height / 2 + vect.y / vect.z * Height / 2;

                g.DrawRectangle(pen, vect.x - 5, vect.y - 5, 10, 10);
            }

            pen = new Pen(Color.Aquamarine, 5);

            foreach (var _polygon in polygons)
            {
                var polygon = _polygon.Item1;

                Point[] points = new Point[polygon.Count];
                for (int p = 0; p < polygon.Count; p++)
                {
                    int curr = polygon[p];
                    int next = polygon[(p + 1) % polygon.Count];

                    Vector3 vect1 = m * vertices[curr];
                    vect1.x = Width / 2 + vect1.x / vect1.z * Width / 2;
                    vect1.y = Height / 2 + vect1.y / vect1.z * Height / 2;

                    Vector3 vect2 = m * vertices[next];
                    vect2.x = Width / 2 + vect2.x / vect2.z * Width / 2;
                    vect2.y = Height / 2 + vect2.y / vect2.z * Height / 2;

                    points[p] = new Point((int)vect1.x, (int)vect1.y);
                    g.DrawLine(new Pen(_polygon.Item2,5), vect1.x, vect1.y, vect2.x, vect2.y);
                }
                
               // g.FillPolygon(myBrush, points);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Create_Cube();
            buttonPressed = 0;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Create_Pin();
            buttonPressed = 1;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Create_Buis();
            buttonPressed = 2;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Create_Bol();
            buttonPressed = 3;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            dots = (int) numericUpDown1.Value;
            if(buttonPressed==0)
            {
                Create_Cube();
            }
            else if (buttonPressed == 1)
            {
                Create_Pin();
            }
            else if (buttonPressed == 2)
            {
                Create_Buis();
            }
            else if (buttonPressed == 3)
            {
                Create_Bol();
            }
        }
        
        
    }
}
