//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SystemAdjust.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_SystemAdjust *Form_SystemAdjust;
//---------------------------------------------------------------------------
__fastcall TForm_SystemAdjust::TForm_SystemAdjust(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_SystemAdjust::FormCreate(TObject *Sender)
{
	MACRO_FORM_MOVE_TO_THE_CENTER

	this->ComboBox_backup->Clear();
	this->ComboBox_backup->Items->Add("1");
	this->ComboBox_backup->Items->Add("3");
	this->ComboBox_backup->Items->Add("7");
	this->ComboBox_backup->Items->Add("10");
	this->ComboBox_backup->Items->Add("30");

}
//---------------------------------------------------------------------------
void __fastcall TForm_SystemAdjust::Button3Click(TObject *Sender)
{
   Form_SensorAdjust->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TForm_SystemAdjust::Button_exitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void TForm_SystemAdjust::Start()
{
    this->Timer_start->Enabled = true;
}


void __fastcall TForm_SystemAdjust::Timer_startTimer(TObject *Sender)
{
	this->Timer_start->Enabled = false;

	this->Edit_name->Text = system->name;

	AnsiString s("");

	for (int i = 100; i <= 1000; i+=100) {

		s.printf("%d",i);
		this->ComboBox_ask_sensor_period->Items->Add(s);
	}

	s.printf("%d", system->ask_sensor_period);
	this->ComboBox_ask_sensor_period->Text = s;


	for (int i = 10; i <= 1000; i+=10) {

		s.printf("%d",i);
		this->ComboBox_tout_read->Items->Add(s);
	}

	s.printf("%d", system->GetPort()->tout_rx);
	this->ComboBox_tout_read->Text = s;

	for (int i = 10; i <= 1000; i+=10) {

		s.printf("%d",i);
		this->ComboBox_tout_write->Items->Add(s);
	}

	s.printf("%d", system->GetPort()->tout_tx);
	this->ComboBox_tout_write->Text = s;

	for (int i = 1; i <= 100; i+=1) {

		s.printf("%d",i);
		this->ComboBox_cmd_delay->Items->Add(s);
	}

	s.printf("%d", system->GetPort()->pause_transact);
	this->ComboBox_cmd_delay->Text = s;


	for (int i = 10; i <= 100; i+=10) {

		s.printf("%d",i);
		this->ComboBox_records_max->Items->Add(s);
	}

	s.printf("%d", system->max_records_meas);
	this->ComboBox_records_max->Text = s;


	for (int i = 10; i <= 100; i+=10) {

		s.printf("%d",i);
		this->ComboBox_records_default->Items->Add(s);
	}

	s.printf("%d", system->def_records_meas);
	this->ComboBox_records_default->Text = s;


	this->CheckBox_ask_param_apply->Checked = *system->ask_save_conf;

	if (system->SysConfMgr.backup_limit <1.0)
	{
		this->ComboBox_backup->Text = "0";
		this->ComboBox_backup->Enabled = false;
		this->CheckBox_backup->Checked = false;
	}
	else
	{
		int bl = (int)system->SysConfMgr.backup_limit;
		s.printf("%d",bl);

		this->ComboBox_backup->Text = s;
		this->ComboBox_backup->Enabled = true;
		this->CheckBox_backup->Checked = true;
	}


}
//---------------------------------------------------------------------------

void __fastcall TForm_SystemAdjust::Button1Click(TObject *Sender)
{
	MACRO_IF_OPERATION_SAVE_PARAM_CONFIRMED

	try{

		system->ask_sensor_period = this->ComboBox_ask_sensor_period->Text.ToInt();

	}
	catch(...)
	{

	}


	try{

		system->GetPort()->tout_rx = this->ComboBox_tout_read->Text.ToInt();

	}
	catch(...)
	{

	}


	try{

		system->GetPort()->tout_tx = this->ComboBox_tout_write->Text.ToInt();

	}
	catch(...)
	{

	}

	try{

		system->GetPort()->pause_transact = this->ComboBox_cmd_delay->Text.ToInt();

	}
	catch(...)
	{

	}


	try{

		system->max_records_meas = this->ComboBox_records_max->Text.ToInt();

	}
	catch(...)
	{

	}

	try{

		system->def_records_meas = this->ComboBox_records_default->Text.ToInt();

	}
	catch(...)
	{

	}


	*system->ask_save_conf = this->CheckBox_ask_param_apply->Checked;
	system->name = Edit_name->Text;

	if (this->CheckBox_backup->Checked == false)
	{
	   system->SysConfMgr.backup_limit = 0.0;
	}
	else
	{
		try
		{
			system->SysConfMgr.backup_limit = (double)this->ComboBox_backup->Text.ToInt();
		}
		catch (...)
		{

		}
    }

	//MessageBox(NULL,"Настройки сохранены","Система",0);
	Button_exitClick(NULL);

}
//---------------------------------------------------------------------------

void __fastcall TForm_SystemAdjust::CheckBox_backupClick(TObject *Sender)
{
	if (this->CheckBox_backup->Checked == false)
	{
		this->ComboBox_backup->Enabled = false;
	}
	else
	{
		this->ComboBox_backup->Enabled = true;
		//this->ComboBox_backup->Text = "1";
	}

}
//---------------------------------------------------------------------------

