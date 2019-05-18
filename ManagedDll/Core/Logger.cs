using System.Runtime.InteropServices;

namespace Ghurund.Managed.Core {
    public enum LogType {
        INFO, WARNING, ERROR
    }

    public static class Logger {

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void LogCallback([MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(WCharStrMarshaler))] string log);

        public delegate void LogEventHandler(string log);

        private static LogCallback logCallback;


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Logger_init([MarshalAs(UnmanagedType.FunctionPtr)] LogCallback callback);

        public static void Init() {
            logCallback = new LogCallback(log);
            Logger_init(logCallback);
        }

        public static event LogEventHandler OnLog;

        private static void log(string log) {
            OnLog?.Invoke(log);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Logger_uninit();

        public static void Uninit() => Logger_uninit();


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Logger_log(LogType type, [MarshalAs(UnmanagedType.LPWStr)] string log);

        public static void Log(LogType type, string log) => Logger_log(type, log);
    }
}
