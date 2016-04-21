using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Rasterizer
{
	struct Matrix
	{
		float[,] data;

		private Matrix(int size = 4)
		{
			data = new float[size, size];
		}

		public static Matrix identity()
		{
			Matrix m = new Matrix(4);
			m.data[0,0] = 1;
			m.data[1,1] = 1;
			m.data[2,2] = 1;
			m.data[3,3] = 1;
			return m;
		}

		public static Matrix perspective(float fovy, float aspect, float zNear, float zFar)
		{
            Matrix m = new Matrix(4);

            m.data[0, 0] = (float)((1 / Math.Tan(fovy / 2)) / aspect);
            m.data[1, 1] = (float)(1 / Math.Tan(fovy / 2));
            m.data[2, 2] = (float)(zFar/(zFar - zNear));
            m.data[2, 3] = -1;
            m.data[3, 2] = (float)((zNear * zFar) / (zFar - zNear) );

            return m;
        }

		public static Matrix rotation(float angle, Vector3 axis)
		{
            Matrix m = Matrix.identity();

            float c = (float) Math.Cos((double) angle);
            float s = (float) Math.Sin((double) angle);

            m.data[0, 0] = (float) Math.Pow(axis.x, 2) * (1 - c) + c;
            m.data[0, 1] = axis.x * axis.y * (1 - c) - axis.z * s;
            m.data[0, 2] = axis.x * axis.z * (1 - c) - axis.y * s;
            m.data[1, 0] = axis.x * axis.y * (1 - c) + axis.z * s;
            m.data[1, 1] = (float)Math.Pow(axis.y, 2) * (1 - c) + c;
            m.data[1, 2] = axis.y * axis.z * (1 - c) + axis.x * s;
            m.data[2, 0] = axis.x * axis.z * (1 - c) + axis.y * s;
            m.data[2, 1] = axis.y * axis.z * (1 - c) - axis.x * s;
            m.data[2, 2] = (float)Math.Pow(axis.z, 2) * (1 - c) + c;

            return m;
        }
		public static Matrix translate(Vector3 offset)
		{
            Matrix m = Matrix.identity();

            for(int i = 0; i < 3; i++)
            {
                m.data[i, 3] = offset.data[i];
            }

            return m;
        }

		public static Vector3 operator * (Matrix mat, Vector3 vec)
		{
            Vector3 v = new Vector3(0,0,0);

            for(int i = 0; i < 4; i++)
            {
                v.data[i] = 0;

                for(int p = 0; p < 4; p++)
                {
                    v.data[i] += mat.data[i, p] * vec.data[p];
                }
            }

            return v;
		}
		public static Matrix operator * (Matrix mat1, Matrix mat2)
		{
            Matrix m = Matrix.identity();

            for (int i = 0; i < 4; i++)
            {
                for (int p = 0; p < 4; p++)
                {
                    m.data[i, p] = 0;

                    for (int q = 0; q < 4; q++)
                    {
                        m.data[i, p] += mat1.data[i, q] * mat2.data[q, p];
                    }
                }
            }

            return m;
        }
	}
}
