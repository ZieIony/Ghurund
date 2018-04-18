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

        public override string ToString() {
            return x + ", " + y + ", " + z;
        }
    }
}
