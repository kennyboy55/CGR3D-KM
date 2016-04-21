using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Rasterizer
{
	struct Vector3
	{
		public float[] data;
		public float x { get { return data[0]; } set { data[0] = value; } }
		public float y { get { return data[1]; } set { data[1] = value; } }
		public float z { get { return data[2]; } set { data[2] = value; } }

		public float length { get { return (float)Math.Sqrt(x * x + y * y + z * z); } }

		public Vector3(float x, float y, float z)
		{
			data = new float[4];
			this.x = x;
			this.y = y;
			this.z = z;
            data[3] = 1;
		}

		public Vector3 normalize()
		{
            Vector3 v = new Vector3(0,0,0);

            if (length != 0)
            {
                v.x = this.x / length;
                v.y = this.y / length;
                v.z = this.z / length;
            }

            return v;
        }

		public static Vector3 operator *(Vector3 vec, float f)
		{
            Vector3 v = new Vector3(0,0,0);



            return v;
		}
		public static Vector3 operator *(float f, Vector3 vec)
		{
            Vector3 v = new Vector3(0,0,0);

            return v;
        }
		public static Vector3 operator -(Vector3 a, Vector3 b)
		{
            Vector3 v = new Vector3(0,0,0);

            return v;
        }
		public static Vector3 operator +(Vector3 a, Vector3 b)
		{
            Vector3 v = new Vector3(0,0,0);

            return v;
        }

		public Vector3 cross(Vector3 other)
		{
			throw new NotImplementedException();
		}
		public float dot(Vector3 other)
		{
			throw new NotImplementedException();
		}

	}
}
