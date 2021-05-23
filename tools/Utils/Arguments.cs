using System.Collections.Generic;

namespace Utils {
    public class Arguments {
        Dictionary<string, string> arguments = new Dictionary<string, string>();

        public Arguments(Dictionary<string, string> arguments) {
            this.arguments = arguments;
        }

        public string this[string key] {
            get {
                try {
                    return arguments[key];
                } catch (KeyNotFoundException) {
                    return null;
                }
            }
        }
    }
}