using System;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Graphics {
    public class RenderingStatistics: NativeClass, INotifyPropertyChanged {

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void ObjectChangedListener();

        private readonly ObjectChangedListener objectChangedCallback;

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ObservableObject_setOnChangedListener(IntPtr _this, [MarshalAs(UnmanagedType.FunctionPtr)] ObjectChangedListener listener);


        public event PropertyChangedEventHandler PropertyChanged;

        // This method is called by the Set accessor of each property.
        // The CallerMemberName attribute that is applied to the optional propertyName
        // parameter causes the property name of the caller to be substituted as an argument.
        protected void NotifyPropertyChanged([CallerMemberName] string propertyName = "") {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Value"));
        }


        public RenderingStatistics(IntPtr ptr) : base(ptr) {
            objectChangedCallback = new ObjectChangedListener(() => NotifyPropertyChanged());
            ObservableObject_setOnChangedListener(NativePtr, objectChangedCallback);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern float RenderingStatistics_getRenderingTime(IntPtr _this);

        [Browsable(false)]
        [Category("Rendering")]
        public float RenderingTime { get => RenderingStatistics_getRenderingTime(NativePtr); }

        [Browsable(true)]
        [Category("Rendering")]
        public string RenderingTimeMs { get => "" + RenderingStatistics_getRenderingTime(NativePtr) * 1000 + "ms"; }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern uint RenderingStatistics_getModelsCulled(IntPtr _this);

        [Browsable(true)]
        [Category("Rendering")]
        public uint ModelsCulled { get => RenderingStatistics_getModelsCulled(NativePtr); }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern uint RenderingStatistics_getModelsRendered(IntPtr _this);

        [Browsable(true)]
        [Category("Rendering")]
        public uint ModelsRendered { get => RenderingStatistics_getModelsRendered(NativePtr); }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern uint RenderingStatistics_getTrianglesRendered(IntPtr _this);

        [Browsable(true)]
        [Category("Rendering")]
        public uint TrianglesRendered { get => RenderingStatistics_getTrianglesRendered(NativePtr); }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern uint RenderingStatistics_getMaterialChanges(IntPtr _this);

        [Browsable(true)]
        [Category("Rendering")]
        public uint MaterialChanges { get => RenderingStatistics_getMaterialChanges(NativePtr); }
    }
}
