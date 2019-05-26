using Ghurund.Managed.Graphics;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Editor {
    public static class CameraUtils {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float3 CameraUtils_screenVectorTo3D(
            Float2 screenVector,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Camera camera);

        public static Float3 ScreenVectorTo3D(Float2 screenVector, Camera camera) {
            return CameraUtils_screenVectorTo3D(screenVector, camera);
        }
    }
}
