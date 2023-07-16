//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DepthAdjust.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_DepthAdjust *Form_DepthAdjust;
//---------------------------------------------------------------------------
__fastcall TForm_DepthAdjust::TForm_DepthAdjust(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_DepthAdjust::Button2Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm_DepthAdjust::FormCreate(TObject *Sender)
{
	str = NULL;
	str1 = NULL;

	MACRO_FORM_MOVE_TO_THE_CENTER
}
//---------------------------------------------------------------------------
void __fastcall TForm_DepthAdjust::Button_enterClick(TObject *Sender)
{
	AnsiString s("");
	double d = 0;

	try {

		s = this->Edit_depth->Text;
		d = s.ToDouble();

		s = this->Edit_trerr->Text;
		d = s.ToDouble();

	} catch (...) {

		utils_ShowMessage(L"Неправильный формат ввода!");
		return;
	}

	if (str) wcscpy(str, this->Edit_depth->Text.c_str());
	if (str1) wcscpy(str1, this->Edit_trerr->Text.c_str());

    Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm_DepthAdjust::FormShow(TObject *Sender)
{
    this->Edit_depth->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm_DepthAdjust::Edit_depthKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN) {

		Button_enterClick(NULL);
	}

}
//---------------------------------------------------------------------------

