using System;
using System.ComponentModel;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using Ghurund.Managed.Graphics;
using Ghurund.Managed.Resource;

namespace Ghurund.Managed.Game {

    public abstract class Entity : Resource.Resource, INotifyPropertyChanged {

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void PropertyChangedListener();

        private PropertyChangedListener propertyChangedCallback;

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Entity_setPropertyChangedListener(IntPtr _this, [MarshalAs(UnmanagedType.FunctionPtr)] PropertyChangedListener listener);


        public event PropertyChangedEventHandler PropertyChanged;

        // This method is called by the Set accessor of each property.
        // The CallerMemberName attribute that is applied to the optional propertyName
        // parameter causes the property name of the caller to be substituted as an argument.
        protected void NotifyPropertyChanged([CallerMemberName] string propertyName = "") {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Property"));
        }


        public Entity() {
            Parameters = new Array<Parameter>(Entity_getParameters(NativePtr), p => new Parameter(p));
            propertyChangedCallback = new PropertyChangedListener(() => NotifyPropertyChanged());
            Entity_setPropertyChangedListener(NativePtr, propertyChangedCallback);
        }

        public Entity(IntPtr ptr) : base(ptr) {
            Parameters = new Array<Parameter>(Entity_getParameters(NativePtr), p => new Parameter(p));
            propertyChangedCallback = new PropertyChangedListener(() => NotifyPropertyChanged());
            Entity_setPropertyChangedListener(NativePtr, propertyChangedCallback);
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
        public string Name {
            get => Entity_getName(NativePtr);
            set {
                Entity_setName(NativePtr, value);
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
            var type = new Core.Type(Entity_getType(ptr));
            switch (type.Name.ToLower()) {
                case "camera":
                    return new Camera(ptr);
                case "light":
                    return new Light(ptr);
                case "model":
                    return new Model(ptr);
                case "transformed entity":
                    return new TransformedEntity(ptr);
            }
            return null;    // TODO: should Entity be abstract?
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Entity_getType(IntPtr _this);
    }

    public class TransformedEntity : Entity {

        public TransformedEntity() {
        }

        public TransformedEntity(IntPtr ptr) : base(ptr) {
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float3 TransformedEntity_getPosition(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void TransformedEntity_setPosition(IntPtr _this, Float3 position);

        [Category("Transformation")]
        [Editor(typeof(Float3UITypeEditor), typeof(System.Drawing.Design.UITypeEditor))]
        public Float3 Position {
            get => TransformedEntity_getPosition(NativePtr);
            set => TransformedEntity_setPosition(NativePtr, value);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float3 TransformedEntity_getRotation(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void TransformedEntity_setRotation(IntPtr _this, Float3 rotation);

        [Category("Transformation")]
        [Description("Euler angles in radians. Maybe I should use degrees instead?")]
        [Editor(typeof(Float3UITypeEditor), typeof(System.Drawing.Design.UITypeEditor))]
        public Float3 Rotation {
            get => TransformedEntity_getRotation(NativePtr);
            set => TransformedEntity_setRotation(NativePtr, value);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float3 TransformedEntity_getScale(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void TransformedEntity_setScale(IntPtr _this, Float3 scale);

        [Category("Transformation")]
        [Description("Each value has to be > 0. For 100% scale use value = 1.0.")]
        [Editor(typeof(Float3UITypeEditor), typeof(System.Drawing.Design.UITypeEditor))]
        public Float3 Scale {
            get => TransformedEntity_getScale(NativePtr);
            set => TransformedEntity_setScale(NativePtr, value);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr TransformedEntity_getEntity(IntPtr _this);

        [Category("General")]
        [Description("Underlying, untransformed entity.")]
        public Entity Entity => Entities.MakeEntity(TransformedEntity_getEntity(NativePtr));


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr TransformedEntity_getFormats();

        [Browsable(false)]
        public static Array<ResourceFormat> Formats { get; } = new Array<ResourceFormat>(TransformedEntity_getFormats(), ptr => new ResourceFormat(ptr));

    }
}
