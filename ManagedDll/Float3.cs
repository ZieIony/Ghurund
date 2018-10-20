using System.Runtime.InteropServices;

namespace Ghurund.Managed {
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
            return x + ", " + y + ", " + z;
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct Float2 {
        private float x;
        private float y;

        public float X { get => x; set => x = value; }
        public float Y { get => y; set => y = value; }

        public override string ToString() {
            return x + ", " + y;
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct Matrix {
        private float a00;
        private float a01;
        private float a02;
        private float a03;

        private float a10;
        private float a11;
        private float a12;
        private float a13;

        private float a20;
        private float a21;
        private float a22;
        private float a23;

        private float a30;
        private float a31;
        private float a32;
        private float a33;

        public override string ToString() {
            return a00 + ", " + a01 + ", " + a02 + ", " + a03 + "\n"+
                a10 + ", " + a11 + ", " + a12 + ", " + a13 + "\n"+
                a20 + ", " + a21 + ", " + a22 + ", " + a23 + "\n"+
                a30 + ", " + a31 + ", " + a32 + ", " + a33;
        }
    }
}
