//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PlaceAdjust.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_PlaceAdjust *Form_PlaceAdjust;
//---------------------------------------------------------------------------
__fastcall TForm_PlaceAdjust::TForm_PlaceAdjust(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_PlaceAdjust::Button_canceClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm_PlaceAdjust::Button_applyClick(TObject *Sender)
{
	if (mode ==0) {

		place->name =  Edit_name->Text;
	}
	else
	{
		place->name =  Edit_name->Text;
	}

    OK = true;

	Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm_PlaceAdjust::FormCreate(TObject *Sender)
{
	MACRO_FORM_MOVE_TO_THE_CENTER

	if (mode == 1) {

		Caption=L"Редактирование места";
		this->Button_apply->Caption = L"Применить";
	}
	else
	{
		Caption=L"Добавить место";
		this->Button_apply->Caption = L"Добавить";
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm_PlaceAdjust::Timer_startTimer(TObject *Sender)
{
	Timer_start->Enabled=false;

	if (mode == 1) {

		Caption=L"Редактирование места";
		this->Button_apply->Caption = L"Применить";
		this->Edit_name->Text= place->GetName();
	}
	else
	{
		Caption=L"Добавить место";
		this->Edit_name->Text= L"Площадка";
		this->Button_apply->Caption =L"Добавить";
	}

}

void TForm_PlaceAdjust::Start()
{
	Timer_start->Enabled=true;
}

//---------------------------------------------------------------------------

