//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PortAdjust.h"

#include <iostream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


TForm_PortAdjust *Form_PortAdjust;
//---------------------------------------------------------------------------
__fastcall TForm_PortAdjust::TForm_PortAdjust(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_PortAdjust::Button_exitClick(TObject *Sender)
{
	MACRO_FORM_CLOSE
}
//---------------------------------------------------------------------------

void __fastcall TForm_PortAdjust::FormCreate(TObject *Sender)
{
	MACRO_FORM_MOVE_TO_THE_CENTER

	//Fill port number values
	this->ComboBox_port_number->Clear();
	for (int i = 1; i < 255; i++) {

		this->ComboBox_port_number->Items->Add(utils_int_to_str(i,0));
		this->ComboBox_port_number->ItemIndex = 0;
	}

	//Fill baud rate values
	this->ComboBox_baud_rate->Clear();
	this->ComboBox_baud_rate->Items->Add(utils_int_to_str(115200,0));
	this->ComboBox_baud_rate->Items->Add(utils_int_to_str(9600,0));
	this->ComboBox_baud_rate->Items->Add(utils_int_to_str(2400,0));
	this->ComboBox_baud_rate->Items->Add(utils_int_to_str(4800,0));
	this->ComboBox_baud_rate->Items->Add(utils_int_to_str(19200,0));
	this->ComboBox_baud_rate->Items->Add(utils_int_to_str(38400,0));
	this->ComboBox_baud_rate->Items->Add(utils_int_to_str(57600,0));
	this->ComboBox_baud_rate->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm_PortAdjust::Button_saveClick(TObject *Sender)
{
	MACRO_IF_OPERATION_SAVE_PARAM_CONFIRMED
	PortSet();
	//MessageBox(NULL,"Настройки сохранены","Порт",0);
	Button_exitClick(NULL);
}
//---------------------------------------------------------------------------


void TForm_PortAdjust::Setup(TGBISystem* s)
{
	system = s;
	port = system->GetPort();
}

void TForm_PortAdjust::PortView()
{

	 this->ComboBox_port_number->Text = utils_int_to_str(port->port,0);
	 this->ComboBox_baud_rate->Text = utils_int_to_str(port->baud,0);
	 this->Edit_port_name->Text = port->mark;

}

void TForm_PortAdjust::Start()
{
	PortView();
}

void TForm_PortAdjust::StartTimer()
{
	this->Timer_start->Enabled = true;
}

void __fastcall TForm_PortAdjust::Timer_startTimer(TObject *Sender)
{
	this->Timer_start->Enabled = false;

	Start();

}


void TForm_PortAdjust::PortSet()
{
	port->Close();

	DWORD com = 0;
	EBaudrate baud = EBaud9600;
	AnsiString s("");

	com  = (DWORD) StrToInt(this->ComboBox_port_number->Text);
	baud = (EBaudrate) StrToInt(this->ComboBox_baud_rate->Text);
	s  = this->Edit_port_name->Text;

	port->mark = s;
	port->Setup(CHAN_TYPE_COM_PORT, com, baud);
	port->Open();
}


//---------------------------------------------------------------------------


