//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MeasAdjust.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_MeasAdjust *Form_MeasAdjust;
//---------------------------------------------------------------------------
__fastcall TForm_MeasAdjust::TForm_MeasAdjust(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_MeasAdjust::Button_applyClick(TObject *Sender)
{
	meas->mark = Edit_mark->Text;
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm_MeasAdjust::FormCreate(TObject *Sender)
{
	MACRO_FORM_MOVE_TO_THE_CENTER
}
//---------------------------------------------------------------------------
void __fastcall TForm_MeasAdjust::Button_cancelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void TForm_MeasAdjust::StartShow()
{
	this->Caption = meas->name;
	this->StaticText_place->Caption = meas->name_place;
	this->StaticText_drill->Caption = meas->name_drill;
	this->Edit_mark->Text = meas->mark;

	ShowModal();
}

