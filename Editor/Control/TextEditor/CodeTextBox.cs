using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text.RegularExpressions;

namespace Ghurund.Editor11 {
    public partial class CodeTextBox : MultiUndoRichTextBox {
		public CodeTextBox() {
			InitializeComponent();
			WordWrap = false;
			tokenClasses = new List<TokenClass>();
		}

		Boolean frozen = false;
		private List<TokenClass> tokenClasses;
		[Browsable(false)]
		public List<TokenClass> TokenClasses {
			get { return tokenClasses; }
		}

#region "Avoid flickering"

		private const int WM_SETREDRAW = 0xB;

		[System.Runtime.InteropServices.DllImport("User32")]
		private static extern bool SendMessage(IntPtr hWnd, int msg, int wParam, int lParam);

		private void FreezeDraw() { //Disable drawing
			SendMessage(Handle, WM_SETREDRAW, 0, 0);
			frozen = true;
		}

		private void UnfreezeDraw() { //Enable drawing and do a redraw. 
			frozen = false;
			SendMessage(Handle, WM_SETREDRAW, 1, 0);
			Invalidate(true);
		}

#endregion

		public override string Text {
			get {
				return base.Text;
			}
			set {
				base.Text = value;
				colorCode();
			}
		}

		public void colorCode() {
			FreezeDraw();
			int selectionStart = SelectionStart;
			int selectionLength = SelectionLength;
			for (int i = 0; i < Lines.Length; i++) {
				colorLine(i);
			}
			SelectionStart = selectionStart;
			SelectionLength = selectionLength;
			UnfreezeDraw();
		}

		protected override void OnTextChanged(EventArgs e) {
			if (frozen)
				return;
			base.OnTextChanged(e);
			FreezeDraw();
			int selectionStart = SelectionStart;
			int selectionLength = SelectionLength;
			int line = GetLineFromCharIndex(SelectionStart);
			colorLine(line);
			SelectionStart = selectionStart;
			SelectionLength = selectionLength;
			UnfreezeDraw();
		}

		private void colorLine(int line) {
			int index = GetFirstCharIndexFromLine(line);
			if (line < Lines.Length && line >= 0) {
				Regex r = new Regex("([ \\\t,\\.<>=!\\+\\-\\*%\\?/{}\\(\\);\\[\\]])");
				string[] tokens = r.Split(Lines[line]);
				foreach (String token in tokens) {
					SelectionStart = index;
					SelectionLength = token.Length;
					SelectionColor = ForeColor;
					SelectionFont = Font;

					foreach (TokenClass tokenClass in TokenClasses) {
						String token2 = tokenClass.CaseSensitive ? token : token.ToLower();
						foreach (String i in tokenClass.TokenList) {
							if ((tokenClass.CaseSensitive ? i : i.ToLower()) == token) {
								SelectionColor = tokenClass.Color;
								SelectionFont = tokenClass.Font;
								goto found;
							}
						}
					}
				found:
					index += token.Length;
				}
			}

		}
	}
}
