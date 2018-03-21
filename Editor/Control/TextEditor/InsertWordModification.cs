using System;

namespace Ghurund.Editor11 {
    public class InsertWordModification : Modification<MultiUndoRichTextBox> {
        int pos;
        public int Pos {
            get { return pos; }
            set { pos = value; }
        }

        String text;

        public System.String Text {
            get { return text; }
            set { text = value; }
        }

        public InsertWordModification(String t, int p) {
            pos = p;
            text = t;
        }

        #region Modification<CodeEditor> Members

        public string Name {
            get { return text + " inserted"; }
        }

        public void undo(MultiUndoRichTextBox u) {
            u.Text = u.Text.Remove(pos, text.Length);
            u.SelectionStart = pos;
        }

        public void redo(MultiUndoRichTextBox u) {
            u.Text = u.Text.Insert(pos, text);
            u.SelectionStart = pos + text.Length;
        }

        public void merge(Modification<MultiUndoRichTextBox> m) {
            text += ((InsertWordModification)m).Text;
        }

        public Boolean canMerge(Modification<MultiUndoRichTextBox> m) {
            return GetType() == m.GetType()
                && ((InsertWordModification)m).Text != " "
                && ((InsertWordModification)m).Text != "\t"
                && ((InsertWordModification)m).Text != "\n";
        }

        #endregion
    }

}
