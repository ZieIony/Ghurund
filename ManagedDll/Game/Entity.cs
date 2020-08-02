using System;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using Ghurund.Managed.Graphics;

namespace Ghurund.Managed.Game {

    public abstract class Entity: Resource.Resource, INotifyPropertyChanged {

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void PropertyChangedListener();

        private readonly PropertyChangedListener propertyChangedCallback;

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Entity_setPropertyChangedListener(IntPtr _this, [MarshalAs(UnmanagedType.FunctionPtr)] PropertyChangedListener listener);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.FunctionPtr)]
        private static extern PropertyChangedListener Entity_getPropertyChangedListener(IntPtr _this);


        public event PropertyChangedEventHandler PropertyChanged;

        // This method is called by the Set accessor of each property.
        // The CallerMemberName attribute that is applied to the optional propertyName
        // parameter causes the property name of the caller to be substituted as an argument.
        protected void NotifyPropertyChanged([CallerMemberName] string propertyName = "") {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }


        public Entity() {
            Parameters = new Array<Parameter>(Entity_getParameters(NativePtr), p => new Parameter(p));
            propertyChangedCallback = Entity_getPropertyChangedListener(NativePtr);
            if (propertyChangedCallback == null) {
                propertyChangedCallback = new PropertyChangedListener(() => NotifyPropertyChanged());
                Entity_setPropertyChangedListener(NativePtr, propertyChangedCallback);
            }
        }

        public Entity(IntPtr ptr) : base(ptr) {
            Parameters = new Array<Parameter>(Entity_getParameters(NativePtr), p => new Parameter(p));
            propertyChangedCallback = Entity_getPropertyChangedListener(NativePtr);
            if (propertyChangedCallback == null) {
                propertyChangedCallback = new PropertyChangedListener(() => NotifyPropertyChanged());
                Entity_setPropertyChangedListener(NativePtr, propertyChangedCallback);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Entity_getType(IntPtr _this);

        [Category("Common")]
        [Description("Different types have different functions and can contain different children.")]
        public Core.Type Type => new Core.Type(Entity_getType(NativePtr));


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(WCharStrMarshaler))]
        private static extern string Entity_getName(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Entity_setName(IntPtr _this, [MarshalAs(UnmanagedType.LPWStr)] string name);

        [Category("Common")]
        [Description("This name will appear in scene explorer and in shaders.")]
        [Editable(true)]
        public string Name {
            get => Entity_getName(NativePtr);
            set {
                Entity_setName(NativePtr, value);
                NotifyPropertyChanged();
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern bool Entity_isSelectable(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Entity_setSelectable(IntPtr _this, bool selectable);

        [Category("Common")]
        [Description("Can this entity be selected by clicking on it.")]
        [Editable(true)]
        public bool Selectable {
            get => Entity_isSelectable(NativePtr);
            set {
                Entity_setSelectable(NativePtr, value);
                NotifyPropertyChanged();
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern bool Entity_isVisible(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Entity_setVisible(IntPtr _this, bool selectable);

        [Category("Common")]
        [Description("Visible in the scene.")]
        [Editable(true)]
        public bool Visible {
            get => Entity_isVisible(NativePtr);
            set {
                Entity_setVisible(NativePtr, value);
                NotifyPropertyChanged();
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Entity_getParent(IntPtr _this);

        [Browsable(false)]
        public Entity Parent { get => Entities.MakeEntity(Entity_getParent(NativePtr)); }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Entity_getScript(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Entity_setScript(IntPtr _this,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Script.Script script);

        [Description("This script will be executed with this resource as a parameter.")]
        [Editable(true)]
        public Script.Script Script {
            get {
                IntPtr scriptPtr = Entity_getScript(NativePtr);
                if (scriptPtr == IntPtr.Zero)
                    return null;
                return new Script.Script(scriptPtr);
            }
            set {
                Entity_setScript(NativePtr, value);
                NotifyPropertyChanged();
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Entity_getParameters(IntPtr _this);

        [Browsable(false)]
        public Array<Parameter> Parameters { get; }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Entity_initParameters(IntPtr _this, IntPtr parameterManager);

        public void InitParameters(ParameterManager manager) {
            Entity_initParameters(NativePtr, manager.NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Entity_updateParameters(IntPtr _this);

        public void UpdateParameters() => Entity_updateParameters(NativePtr);
    }

    public static class Entities {

        public static Entity MakeEntity(IntPtr ptr) {
            if (ptr == IntPtr.Zero)
                return null;

            var type = new Core.Type(Entity_getType(ptr));
            switch (type.Name.ToLower()) {
                case "camera":
                    return new Camera(ptr);
                case "light":
                    return new Light(ptr);
                case "scene":
                    return new Scene(ptr);
            }
            return null;
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Entity_getType(IntPtr _this);
    }
}
