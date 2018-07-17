using System;
using System.ComponentModel;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Game {

    public enum ParameterType {
        Float, Float2, Float3, Matrix
    }

    public class Parameter : NativeClass {
        public Parameter(IntPtr ptr) : base(ptr) {
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(WCharStrMarshaler))]
        private static extern String Parameter_getName(IntPtr _this);

        [Category("Common")]
        [Description("This name will appear in shaders.")]
        public String Name {
            get {
                return Parameter_getName(NativePtr);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern ParameterType Parameter_getType(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern float Parameter_getFloatValue(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float2 Parameter_getFloat2Value(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float3 Parameter_getFloat3Value(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Matrix Parameter_getMatrixValue(IntPtr _this);

        [Category("Common")]
        [Description("This value will be set in shaders.")]
        public String Value {
            get {
                switch (Parameter_getType(NativePtr)) {
                    case ParameterType.Float:
                        return Parameter_getFloatValue(NativePtr).ToString();
                    case ParameterType.Float2:
                        return Parameter_getFloat2Value(NativePtr).ToString();
                    case ParameterType.Float3:
                        return Parameter_getFloat3Value(NativePtr).ToString();
                    case ParameterType.Matrix:
                        return Parameter_getMatrixValue(NativePtr).ToString();
                }
                return "";
            }
        }
    }

    public class ParameterList : NativeList<Parameter> {

        public ParameterList(IntPtr ptr) : base(ptr) {
        }

        protected override Parameter MakeItem(IntPtr p) {
            return new Parameter(p);
        }
    }
}
