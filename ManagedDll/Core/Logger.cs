using System.Runtime.InteropServices;

namespace Ghurund.Managed.Core {
    public static class Logger {

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void LogCallback([MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(WCharStrMarshaler))] string log);


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Logger_init([MarshalAs(UnmanagedType.FunctionPtr)] LogCallback callback);

        public static void Init(LogCallback callback) {
            Logger_init(callback);
        }
    }
}
