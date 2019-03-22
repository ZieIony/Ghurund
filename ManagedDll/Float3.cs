using System;
using System.Runtime.InteropServices;
using System.Windows.Media;

namespace Ghurund.Managed {
    [StructLayout(LayoutKind.Sequential)]
    public struct Color {
        private float x;
        private float y;
        private float z;
        private float w;

        public float R { get => x; set => x = value; }
        public float G { get => y; set => y = value; }
        public float B { get => z; set => z = value; }
        public float A { get => w; set => w = value; }

        public Color(float a, float r, float g, float b) {
            this.w = a;
            this.x = r;
            this.y = g;
            this.z = b;
        }

        public Color(string hexString) {
            System.Windows.Media.Color color2 = (System.Windows.Media.Color)ColorConverter.ConvertFromString(hexString);
            w = color2.A / 255.0f;
            x = color2.R / 255.0f;
            y = color2.G / 255.0f;
            z = color2.B / 255.0f;
        }

        public override string ToString() {
            return string.Format("#{0:X2}{1:X2}{2:X2}{3:X2}", (byte)(w * 255), (byte)(x * 255), (byte)(y * 255), (byte)(z * 255));
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct Float4 {
        private float x;
        private float y;
        private float z;
        private float w;

        public float X { get => x; set => x = value; }
        public float Y { get => y; set => y = value; }
        public float Z { get => z; set => z = value; }
        public float W { get => w; set => w = value; }

        public Float4(float x, float y, float z, float w) {
            this.x = x;
            this.y = y;
            this.z = z;
            this.w = w;
        }

        public override string ToString() {
            return ", " + x.ToString("0.##") + ", " + y.ToString("0.##") + ", " + z.ToString("0.##") + w.ToString("0.##");
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct Float3 {
        private float x;
        private float y;
        private float z;

        public float X { get => x; set => x = value; }
        public float Y { get => y; set => y = value; }
        public float Z { get => z; set => z = value; }

        public Float3(float x, float y, float z) {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public override string ToString() {
            return x.ToString("0.##") + ", " + y.ToString("0.##") + ", " + z.ToString("0.##");
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct Float2 {
        private float x;
        private float y;

        public float X { get => x; set => x = value; }
        public float Y { get => y; set => y = value; }

        public override string ToString() {
            return x.ToString("0.##") + ", " + y.ToString("0.##");
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct Int2 {
        private int x;
        private int y;

        public int X { get => x; set => x = value; }
        public int Y { get => y; set => y = value; }

        public override string ToString() {
            return x + ", " + y;
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct Matrix {
        public float a00;
        public float a01;
        public float a02;
        public float a03;

        public float a10;
        public float a11;
        public float a12;
        public float a13;

        public float a20;
        public float a21;
        public float a22;
        public float a23;

        public float a30;
        public float a31;
        public float a32;
        public float a33;

        public override string ToString() {
            return a00.ToString("0.##") + ", " + a01.ToString("0.##") + ", " + a02.ToString("0.##") + ", " + a03.ToString("0.##") + "\n" +
                a10.ToString("0.##") + ", " + a11.ToString("0.##") + ", " + a12.ToString("0.##") + ", " + a13.ToString("0.##") + "\n" +
                a20.ToString("0.##") + ", " + a21.ToString("0.##") + ", " + a22.ToString("0.##") + ", " + a23.ToString("0.##") + "\n" +
                a30.ToString("0.##") + ", " + a31.ToString("0.##") + ", " + a32.ToString("0.##") + ", " + a33.ToString("0.##");
        }
    }
}
