using Ghurund.Controls.Workspace;
using Ghurund.Managed;
using Ghurund.Managed.Core;
using Ghurund.Managed.Resource;
using Ghurund.Managed.Script;
using ICSharpCode.AvalonEdit.CodeCompletion;
using ICSharpCode.AvalonEdit.Document;
using ICSharpCode.AvalonEdit.Editing;
using ICSharpCode.AvalonEdit.Folding;
using Microsoft.Win32;
using Ninject;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Resources;
using System.Xml;
using System.Xml.Serialization;

namespace Ghurund.Editor.ResourceEditor {
    public interface IScriptEditor: IDocumentPanel {
        Script Script { get; set; }
    }

    public class MyCompletionData: ICompletionData {
        public MyCompletionData(string text) {
            this.Text = text;
        }

        public System.Windows.Media.ImageSource Image {
            get { return null; }
        }

        public string Text { get; private set; }

        // Use this property if you want to show a fancy UIElement in the list.
        public object Content {
            get { return this.Text; }
        }

        public object Description {
            get { return "Description for " + this.Text; }
        }

        public double Priority => 1;

        public void Complete(TextArea textArea, ISegment completionSegment,
            EventArgs insertionRequestEventArgs) {
            textArea.Document.Replace(completionSegment, this.Text);
        }
    }

    public partial class ScriptEditorPanel: UserControl, IScriptEditor, IStateControl {

        public System.Collections.Generic.List<object> SelectedItems {
            get => null;
            set {
                // nothing, this editor doesn't support selection change
            }
        }

        public event RoutedSelectionChangedEventHandler SelectionChanged;

        [Inject]
        public ResourceManager ResourceManager { get; set; }

        [Inject]
        public ResourceContext ResourceContext { get; set; }

        [Inject]
        public ScriptEngine ScriptEngine { get; set; }

        private Script script;
        public Script Script {
            get => script;
            set {
                if (script == value)
                    return;

                script?.Release();
                script = value;
                if (script != null) {
                    script.AddReference();
                    Title = new Title(script.ToString().Substring(script.ToString().LastIndexOfAny(new char[] { '\\', '/' }) + 1), script.ToString());
                    shaderCode.Text = script.SourceCode;
                }
            }
        }

        public ImageSource Icon { get; }
        public Control Control { get => this; }
        public Title Title { get; private set; }
        public bool NeedsSaving => false;

        public ScriptEditorPanel() {
            InitializeComponent();

            EditorKernel.Instance.Inject(this);

            shaderCode.TextArea.TextEntering += textEditor_TextArea_TextEntering;
            shaderCode.TextArea.TextEntered += textEditor_TextArea_TextEntered;

            var foldingManager = FoldingManager.Install(shaderCode.TextArea);
            var foldingStrategy = new XmlFoldingStrategy();
            foldingStrategy.UpdateFoldings(foldingManager, shaderCode.Document);

            Uri uri = new Uri("pack://application:,,,/Resources/AngelScript.xshd", UriKind.Absolute);
            StreamResourceInfo info = Application.GetResourceStream(uri);
            Stream xshd_stream = info.Stream;
            XmlTextReader xshd_reader = new XmlTextReader(xshd_stream);
            shaderCode.SyntaxHighlighting = ICSharpCode.AvalonEdit.Highlighting.Xshd.HighlightingLoader.Load(xshd_reader, ICSharpCode.AvalonEdit.Highlighting.HighlightingManager.Instance);
            xshd_reader.Close();
            xshd_stream.Close();
        }

        CompletionWindow completionWindow;

        void textEditor_TextArea_TextEntered(object sender, TextCompositionEventArgs e) {
            if (e.Text == ".") {
                // Open code completion after the user has pressed dot:
                completionWindow = new CompletionWindow(shaderCode.TextArea);
                IList<ICompletionData> data = completionWindow.CompletionList.CompletionData;
                data.Add(new MyCompletionData("Item1"));
                data.Add(new MyCompletionData("Item2"));
                data.Add(new MyCompletionData("Item3"));
                completionWindow.Show();
                completionWindow.Closed += delegate {
                    completionWindow = null;
                };
            }
        }

        void textEditor_TextArea_TextEntering(object sender, TextCompositionEventArgs e) {
            if (e.Text.Length > 0 && completionWindow != null) {
                if (!char.IsLetterOrDigit(e.Text[0])) {
                    // Whenever a non-letter is typed while the completion window is open,
                    // insert the currently selected element.
                    completionWindow.CompletionList.RequestInsertion(e);
                }
            }
            // Do not set e.Handled=true.
            // We still want to insert the character that was typed.
        }

        public bool Save(string fileName = null) {
            if (fileName == null && script.FileName == null) {
                SaveFileDialog saveFileDialog = new SaveFileDialog();
                var result = saveFileDialog.ShowDialog();
                if (!result.GetValueOrDefault(false))
                    return false;
                fileName = saveFileDialog.FileName;
            }
            return script.Save(ResourceManager, fileName) == Status.OK;
        }

        public bool Load(string fileName) {
            var material = new Script();
            if (material.Load(ResourceManager, ResourceContext, fileName) != Status.OK) {
                material.Release();
                return false;
            }
            Script = material;
            material.Release();
            return true;
        }

        public void SaveState(Stream stream) {
            XmlSerializer serializer = new XmlSerializer(typeof(string));
            serializer.Serialize(stream, script.FileName);
        }

        public void RestoreState(Stream stream) {
            XmlSerializer serializer = new XmlSerializer(typeof(string));
            string fileName = serializer.Deserialize(stream) as string;
            if (!File.Exists(fileName))
                return; // TODO: error handling
            Load(fileName);
        }

        #region IDisposable Support
        private bool disposedValue = false; // To detect redundant calls

        protected virtual void Dispose(bool disposing) {
            if (!disposedValue) {
                if (disposing) {
                    if (Script != null)
                        Script.Release();
                }

                // TODO: free unmanaged resources (unmanaged objects) and override a finalizer below.
                // TODO: set large fields to null.

                disposedValue = true;
            }
        }

        // TODO: override a finalizer only if Dispose(bool disposing) above has code to free unmanaged resources.
        // ~MaterialEditorPanel() {
        //   // Do not change this code. Put cleanup code in Dispose(bool disposing) above.
        //   Dispose(false);
        // }

        // This code added to correctly implement the disposable pattern.
        public void Dispose() {
            // Do not change this code. Put cleanup code in Dispose(bool disposing) above.
            Dispose(true);
            // TODO: uncomment the following line if the finalizer is overridden above.
            // GC.SuppressFinalize(this);
        }
        #endregion

        private void ShaderCode_GotFocus(object sender, RoutedEventArgs e) {
        }

        private void Build_Click(object sender, RoutedEventArgs e) {
            script.SourceCode = shaderCode.Text;
            script.Build(ScriptEngine);
            /*string output = script.Build(ScriptEngine);
            if (output != null) {
                foreach (string line in output.Split('\n'))
                    Logger.Log(LogType.ERROR, line);
            }*/
        }

        private void ShaderCode_SelectionChanged(object sender, RoutedEventArgs e) {
            /*shaderCode.CaretPosition.GetLineStartPosition(-int.MaxValue, out int lineNumber);
            int columnNumber = shaderCode.CaretPosition.GetLineStartPosition(0).GetOffsetToPosition(shaderCode.CaretPosition);

            status.Text = "[" + (-lineNumber + 1) + ":" + (columnNumber + 1) + "]";*/
        }
    }
}
