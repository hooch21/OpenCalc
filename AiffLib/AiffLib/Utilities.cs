using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AiffLib
{
    class Utilities
    {
        public static void NormalizeToOne(float[] data)
        {
            int npts = data.Length;

            float max = 0.0f;

            float val = 0.0f;

            for (int i = 0; i < npts; i++)
            {
                val = Math.Abs(data[i]);
                if (val > max)
                {
                    max = val;
                }
            }

            for (int i = 0; i < npts; i++)
                data[i] /= max;
        }

        public static void NormalizeToOne(double[] data)
        {
            int npts = data.Length;

            double max = 0.0;

            double val = 0.0;

            for (int i = 0; i < npts; i++)
            {
                val = Math.Abs(data[i]);
                if (val > max)
                {
                    max = val;
                }
            }

            for (int i = 0; i < npts; i++)
                data[i] /= max;
        }
    }
}
