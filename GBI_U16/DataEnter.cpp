//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DataEnter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_data_enter *Form_data_enter;
//---------------------------------------------------------------------------
__fastcall TForm_data_enter::TForm_data_enter(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_data_enter::Button_cancelClick(TObject *Sender)
{
			Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm_data_enter::Button_applyClick(TObject *Sender)
{
			wcscpy(s, Edit_data->Text.c_str());
			Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm_data_enter::FormCreate(TObject *Sender)
{
		MACRO_FORM_MOVE_TO_THE_CENTER
        Edit_data->Text = "0.0";
}
//---------------------------------------------------------------------------
