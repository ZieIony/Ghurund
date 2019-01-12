using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Media;

namespace Ghurund.Controls {
    public class CodeTextBox : RichTextBox {

        public CodeTextBox() {
            tags = new List<string>(new string[]{
               "float", "float2", "float3", "float4","float4x4",
                "int", "int2", "int3", "int4",
                "struct", "cbuffer", "register","row_major",
                "return", "for", "while", "if"
            });

            specials = new List<char>(new char[]{
                '.',')','(','[',']','>','<',':',';','\n','\t'
            });

            FontFamily = new FontFamily("Courier New");
            TextChanged += textChanged;
        }

        static List<string> tags = new List<string>();
        static List<char> specials = new List<char>();

        public static bool IsKnownTag(string tag) {
            return tags.Exists(delegate (string s) { return s.ToLower().Equals(tag.ToLower()); });
        }

        public static List<string> GetJSProvider(string tag) {
            return tags.FindAll(delegate (string s) { return s.ToLower().StartsWith(tag.ToLower()); });
        }

        new struct Tag {
            public TextPointer StartPosition;
            public TextPointer EndPosition;
            public string Word;

        }

        public string Text {
            get {
                return new TextRange(Document.ContentStart, Document.ContentEnd).Text;
            }
            set {
                Document.Blocks.Clear();
                Document.Blocks.Add(new Paragraph(new Run(value)));
            }
        }

        private void textChanged(object sender, TextChangedEventArgs e) {
            if (Document == null)
                return;

            TextRange documentRange = new TextRange(Document.ContentStart, Document.ContentEnd);
            documentRange.ClearAllProperties();

            TextPointer navigator = Document.ContentStart;
            while (navigator.CompareTo(Document.ContentEnd) < 0) {
                TextPointerContext context = navigator.GetPointerContext(LogicalDirection.Backward);
                if (context == TextPointerContext.ElementStart && navigator.Parent is Run) {
                    CheckWordsInRun((Run)navigator.Parent);

                }
                navigator = navigator.GetNextContextPosition(LogicalDirection.Forward);
            }
        }


        void CheckWordsInRun(Run run) {
            string text = run.Text;
            List<Tag> tags = new List<Tag>();

            int sIndex = 0;
            int eIndex = 0;
            for (int i = 0; i < text.Length; i++) {
                if (Char.IsWhiteSpace(text[i]) | specials.Contains(text[i])) {
                    if (i > 0 && !(Char.IsWhiteSpace(text[i - 1]) | specials.Contains(text[i - 1]))) {
                        eIndex = i - 1;
                        string word = text.Substring(sIndex, eIndex - sIndex + 1);

                        if (IsKnownTag(word)) {
                            Tag t = new Tag {
                                StartPosition = run.ContentStart.GetPositionAtOffset(sIndex, LogicalDirection.Forward),
                                EndPosition = run.ContentStart.GetPositionAtOffset(eIndex + 1, LogicalDirection.Backward),
                                Word = word
                            };
                            tags.Add(t);
                        }
                    }
                    sIndex = i + 1;
                }
            }

            string lastWord = text.Substring(sIndex, text.Length - sIndex);
            if (IsKnownTag(lastWord)) {
                Tag t = new Tag {
                    StartPosition = run.ContentStart.GetPositionAtOffset(sIndex, LogicalDirection.Forward),
                    EndPosition = run.ContentStart.GetPositionAtOffset(eIndex + 1, LogicalDirection.Backward),
                    Word = lastWord
                };
                tags.Add(t);
            }

            TextChanged -= textChanged;

            for (int i = 0; i < tags.Count; i++) {
                TextRange range = new TextRange(tags[i].StartPosition, tags[i].EndPosition);
                range.ApplyPropertyValue(TextElement.ForegroundProperty, new SolidColorBrush(Colors.Blue));
                range.ApplyPropertyValue(TextElement.FontWeightProperty, FontWeights.Bold);
            }
            tags.Clear();

            TextChanged += textChanged;
        }

    }
}
