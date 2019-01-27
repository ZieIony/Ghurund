using System;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Game {

    public enum ParameterType {
        Int, Int2, Float, Float2, Float3, Matrix
    }

    public class Parameter : NativeClass, INotifyPropertyChanged {

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void PropertyChangedListener();

        private PropertyChangedListener propertyChangedCallback;

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ObservableObject_setOnChangedListener(IntPtr _this, [MarshalAs(UnmanagedType.FunctionPtr)] PropertyChangedListener listener);


        public event PropertyChangedEventHandler PropertyChanged;

        // This method is called by the Set accessor of each property.
        // The CallerMemberName attribute that is applied to the optional propertyName
        // parameter causes the property name of the caller to be substituted as an argument.
        protected void NotifyPropertyChanged([CallerMemberName] string propertyName = "") {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Value"));
        }


        public Parameter(IntPtr ptr) : base(ptr) {
            propertyChangedCallback = new PropertyChangedListener(() => NotifyPropertyChanged());
            ObservableObject_setOnChangedListener(NativePtr, propertyChangedCallback);
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(WCharStrMarshaler))]
        private static extern string Parameter_getName(IntPtr _this);

        [Category("Common")]
        [Description("This name will appear in shaders.")]
        public string Name => Parameter_getName(NativePtr);


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern ParameterType Parameter_getType(IntPtr _this);

        public ParameterType Type { get => Parameter_getType(NativePtr); }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int Parameter_getIntValue(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Int2 Parameter_getInt2Value(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern float Parameter_getFloatValue(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float2 Parameter_getFloat2Value(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float3 Parameter_getFloat3Value(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Matrix Parameter_getMatrixValue(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Parameter_setIntValue(IntPtr _this, int value);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Parameter_setInt2Value(IntPtr _this, Int2 value);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Parameter_setFloatValue(IntPtr _this, float value);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Parameter_setFloat2Value(IntPtr _this, Float2 value);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Parameter_setFloat3Value(IntPtr _this, Float3 value);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Parameter_setMatrixValue(IntPtr _this, Matrix value);

        [Category("Common")]
        [Description("This value will be set in shaders.")]
        public object Value {
            get {
                switch (Parameter_getType(NativePtr)) {
                    case ParameterType.Int:
                        return Parameter_getIntValue(NativePtr);
                    case ParameterType.Int2:
                        return Parameter_getInt2Value(NativePtr);
                    case ParameterType.Float:
                        return Parameter_getFloatValue(NativePtr);
                    case ParameterType.Float2:
                        return Parameter_getFloat2Value(NativePtr);
                    case ParameterType.Float3:
                        return Parameter_getFloat3Value(NativePtr);
                    case ParameterType.Matrix:
                        return Parameter_getMatrixValue(NativePtr);
                }
                return null;
            }
            set {
                switch (Parameter_getType(NativePtr)) {
                    case ParameterType.Int:
                        Parameter_setIntValue(NativePtr, (int)value);
                        break;
                    case ParameterType.Int2:
                        Parameter_setInt2Value(NativePtr, (Int2)value);
                        break;
                    case ParameterType.Float:
                        Parameter_setFloatValue(NativePtr, (float)value);
                        break;
                    case ParameterType.Float2:
                        Parameter_setFloat2Value(NativePtr, (Float2)value);
                        break;
                    case ParameterType.Float3:
                        Parameter_setFloat3Value(NativePtr, (Float3)value);
                        break;
                    case ParameterType.Matrix:
                        Parameter_setMatrixValue(NativePtr, (Matrix)value);
                        break;
                }
            }
        }
    }
}
