using System;
using System.Windows.Forms;

namespace Ghurund.Editor11 {
    public partial class MultiUndoRichTextBox : RichTextBox {

        public MultiUndoRichTextBox() {
            InitializeComponent();
        }

        ModificationStack<MultiUndoRichTextBox> stack = new ModificationStack<MultiUndoRichTextBox>();

		int pos = 0;

        protected override void OnKeyPress(KeyPressEventArgs e) {
            base.OnKeyPress(e);
            if (char.IsControl(e.KeyChar))
                return;
            stack.add(new InsertWordModification(""+e.KeyChar, pos));
		}

        protected override void OnKeyDown(KeyEventArgs e) {
            base.OnKeyDown(e);
            if (e.KeyCode == Keys.Back&&SelectionStart!=0) {
                stack.add(new DeleteWordModification(Text.Substring(SelectionStart - 1, 1), pos-1));
            } else if (e.KeyCode == Keys.Delete&&SelectionStart!=Text.Length) {
                stack.add(new DeleteWordModification(Text.Substring(SelectionStart, 1), pos));
            }
        }

        protected override void OnSelectionChanged(EventArgs e){
            pos = SelectionStart;
        }

        protected override void OnMouseDown(MouseEventArgs e){
            base.OnMouseDown(e);
            stack.add(new CaretMoveModification(pos, SelectionStart));
            pos = SelectionStart;
        }

		public int CurrentColumn {
			get { return SelectionStart - GetFirstCharIndexOfCurrentLine() + 1; }
		}

		public int CurrentLine {
			get { return GetLineFromCharIndex(SelectionStart + 1); }
		}

		public new Boolean CanUndo {
			get {
				return stack.CanUndo;
			}
		}

		public new Boolean CanRedo {
			get {
				return stack.CanRedo;
			}
		}

		public int Depth {
			get {
				return stack.Depth;
			}
			set {
				stack.Depth = value;
			}
		}

		public void undo() {
			stack.undo(this);
		}
		public void redo() {
			stack.redo(this);
		}
    }
}
