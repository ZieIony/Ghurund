using System;

namespace Ghurund.Editor.Control.Outline {
    public class SelectionChangedEventArgs<Type> : EventArgs {
        public Type Value { get; set; }

        public SelectionChangedEventArgs() {
        }

        public SelectionChangedEventArgs(Type _value) {
            Value = _value;
        }
    }

}
