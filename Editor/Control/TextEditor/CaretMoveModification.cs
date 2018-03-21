using System;

namespace Ghurund.Editor11 {
    public class CaretMoveModification : Modification<MultiUndoRichTextBox> {
        int pos;
        public int Pos {
            get { return pos; }
            set { pos = value; }
        }

        int prevPos;
        public int PrevPos {
            get { return prevPos; }
            set { prevPos = value; }
        }

        public CaretMoveModification(int p,int p2) {
            pos = p;
            prevPos = p2;
        }

        #region Modification<CodeEditor> Members

        public string Name {
            get { return "Caret moved"; }
        }

        public void undo(MultiUndoRichTextBox u) {
            u.SelectionStart = prevPos;
        }

        public void redo(MultiUndoRichTextBox u) {
            u.SelectionStart = pos;
        }

        public void merge(Modification<MultiUndoRichTextBox> m) {
            pos=((CaretMoveModification)m).Pos;
        }

        public Boolean canMerge(Modification<MultiUndoRichTextBox> m) {
            return GetType() == m.GetType();
        }

        #endregion
    }
}
