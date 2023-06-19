//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ExcelWait.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_excel_progress *Form_excel_progress;
//---------------------------------------------------------------------------
__fastcall TForm_excel_progress::TForm_excel_progress(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void TForm_excel_progress::StartShow(int max)
{
   this->ProgressBar_excel->Min = 0;
   this->ProgressBar_excel->Max = max;
   this->ProgressBar_excel->Position = 0;
   Show();
}

void TForm_excel_progress::StopShow()
{
   this->ProgressBar_excel->Position = this->ProgressBar_excel->Max;
   Sleep(10);
   this->ProgressBar_excel->Position = 0;
   Close();
}

void TForm_excel_progress::UpdateShow(int pos)
{
	this->ProgressBar_excel->Position = pos;
}
void __fastcall TForm_excel_progress::FormCreate(TObject *Sender)
{
	MACRO_FORM_MOVE_TO_THE_CENTER
}
//---------------------------------------------------------------------------
