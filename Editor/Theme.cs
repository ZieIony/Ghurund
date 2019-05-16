using System;
using System.Collections.Generic;
using System.Windows;

namespace Ghurund.Editor {
    public enum Theme {
        Light, Dark
    }

    public class ThemeResourceDictionary : ResourceDictionary{

        private static readonly Dictionary<Theme, Uri> themes = new Dictionary<Theme, Uri> {
            {Theme.Light, new Uri("pack://application:,,,/Themes/Theme.Light.xaml") },
            {Theme.Dark, new Uri("pack://application:,,,/Themes/Theme.Dark.xaml") }
        };

        public static void ApplyTheme(FrameworkElement targetElement, Theme theme) {
            try {
                IEnumerable<ResourceDictionary> dictionaries =
                    targetElement.Resources.MergedDictionaries.Filter(dictionary => dictionary is ThemeResourceDictionary);

                foreach (ResourceDictionary dictionary in dictionaries)
                    targetElement.Resources.MergedDictionaries.Remove(dictionary);

                ThemeResourceDictionary themeDictionary = new ThemeResourceDictionary {
                    Source = themes[theme]
                };

                targetElement.Resources.MergedDictionaries.Insert(0, themeDictionary);
            } finally { }
        }

    }
}
