using System.Collections.Generic;
using System;

namespace Ghurund.Editor11 {
    public interface Modification<Type> {
		String Name {
			get;
		}
		void undo(Type u);
		void redo(Type u);
        void merge(Modification<Type> m);
        Boolean canMerge(Modification<Type> m);
	}

	public class ModificationStack<Type> {
		private int depth;
		public int Depth {
			get { return depth; }
			set {
				depth = value;
				while (undoStack.Count > depth) {
					undoStack.RemoveAt(0);
				}
			}
		}

		private List<Modification<Type>> undoStack = new List<Modification<Type>>();	// here goes every done modification
		private List<Modification<Type>> redoStack = new List<Modification<Type>>();	// here goes every undone modification

		public Boolean CanUndo {
			get {
				return undoStack.Count > 0;
			}
		}

		public void undo(Type editor) {
			if (undoStack.Count == 0) {
				return;
			}
			Modification<Type> m = undoStack[undoStack.Count - 1];
			undoStack.Remove(m);
			m.undo(editor);
			redoStack.Add(m);
		}

		public Boolean CanRedo {
			get {
				return redoStack.Count > 0;
			}
		}

		public void redo(Type editor) {
			if (redoStack.Count == 0) {
				return;
			}
			Modification<Type> m = redoStack[redoStack.Count - 1];
			redoStack.Remove(m);
			m.redo(editor);
			undoStack.Add(m);
			if (undoStack.Count > depth) {
				undoStack.RemoveAt(0);
			}
		}

		public void add(Modification<Type> m) {
			redoStack.Clear();
            if (undoStack.Count != 0 && undoStack[undoStack.Count - 1].canMerge(m)) {
                undoStack[undoStack.Count - 1].merge(m);
            } else {
                undoStack.Add(m);
            }
			if (undoStack.Count > depth) {
				undoStack.RemoveAt(0);
			}
		}

		public void update(Modification<Type> m) {
			undoStack[undoStack.Count - 1] = m;
		}
	}

}