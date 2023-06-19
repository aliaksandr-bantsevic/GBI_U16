//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SensorAdjust.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_SensorAdjust *Form_SensorAdjust;

#include "Channel.h"
#include "Protocol_211.h"


bool serial_read = false;
bool version_read = false;
bool scan_mode = false;
BYTE scan_addr = 0;
TSensor stmp;
TSensor* s_tmp=&stmp;
int total_sensors = 0;

//---------------------------------------------------------------------------
__fastcall TForm_SensorAdjust::TForm_SensorAdjust(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_SensorAdjust::FormCreate(TObject *Sender)
{
	MACRO_FORM_MOVE_TO_THE_CENTER

	//Fill sensor addr values
	this->ComboBox_sensor_addr->Clear();
	for (int i = 1; i < 255; i++) {

		this->ComboBox_sensor_addr->Items->Add(utils_int_to_str(i,0));
		this->ComboBox_sensor_addr->ItemIndex = 0;
	}

	this->ComboBox_protocol->Clear();
	this->ComboBox_protocol->Items->Add("ÈÍ-Ä3");
	this->ComboBox_protocol->Items->Add("ÀÍ-Ä3");

	this->SetFocusedControl(this->Button_exit);

}
//---------------------------------------------------------------------------
void __fastcall TForm_SensorAdjust::Button_exitClick(TObject *Sender)
{
		MACRO_FORM_CLOSE
}
//---------------------------------------------------------------------------
void __fastcall TForm_SensorAdjust::Button_saveClick(TObject *Sender)
{
	MACRO_IF_OPERATION_SAVE_PARAM_CONFIRMED

	SetSensor();

	//MessageBox(NULL,"Íàñòðîéêè ñîõðàíåíû","Äàò÷èê",0);

	Button_exitClick(NULL);

}
//---------------------------------------------------------------------------

void __fastcall TForm_SensorAdjust::Button_startClick(TObject *Sender)
{

	if (scan_mode == false) {

        total_sensors = 0;
		scan_addr = 1;
		scan_mode  = true;
		this->Label_msg->Visible = true;
		this->ProgressBar_scan->Visible = true;
		this->ProgressBar_scan->Min = 0;
		this->ProgressBar_scan->Max = 255;
		this->ProgressBar_scan->Position = 0;
		this->Button_start->Caption = "Ñòîï";
		this->ComboBox_addr_found->Clear();
		s_tmp->SetChan(system->GetPort());
        this->Label_msg->Caption = "Èäåò ïîèñê äàò÷èêîâ ...";
		this->ComboBox_addr_found->Visible = false;
        this->Label_msg_sensors->Visible = false;

		this->Timer_scan->Enabled = true;
	}
	else
	{
		 scan_addr = 253;
    }

}
//---------------------------------------------------------------------------


void __fastcall TForm_SensorAdjust::Timer_runTimer(TObject *Sender)
{
		if (system->GetPort()->IsOpen() == false) {

					return;
		}

		if (scan_mode == true) {

					return;
		}

		Timer_run->Enabled = false;

		TSensor* s = system->GetSensor();

		if (serial_read == false ) {

				if (s->GetSerial() == 0)
				{
					this->Edit_serial->Text = utils_int_to_str(s->serial, 0);
					serial_read = true;
				}
		}

		else  {

				if (version_read == false) {

					if (s->GetSoftVer() == 0)
					{
						this->Edit_version->Text = utils_int_to_str(s->soft_version, 0);
                        version_read = true;
					}

				}
				else {

					if (sensor->GetMeasResult() == 0)
					{
						AnsiString s;

						if (sensor->curr_X>=0)  s.printf("+%.1f",sensor->curr_X);
						else  			s.printf("%.1f",sensor->curr_X);
						this->Edit_X->Text = s;

						if (sensor->curr_Y>=0)  s.printf("+%.1f",sensor->curr_Y);
						else  			s.printf("%.1f",sensor->curr_Y);
						this->Edit_Y->Text = s;
					}
				}
		}

		Timer_run->Enabled = true;


}
//---------------------------------------------------------------------------


void __fastcall TForm_SensorAdjust::Timer_startTimer(TObject *Sender)
{
	this->Timer_start->Enabled=false;
	Start();
}

void TForm_SensorAdjust::StartTimer()
{
	this->Timer_start->Enabled=true;
}

void TForm_SensorAdjust::Start()
{
	AnsiString s("");
	TChannel* p = system->GetPort();
	s.printf("COM%d  %d",p->port, p->baud);
	this->Edit_port_prop->Text = s;
	this->Edit_port_prop->Enabled = false;

	if (p->IsOpen() == false) {

		this->Button_port_open->Caption = "Îòêðûòü ïîðò";
		this->Edit_port_prop->Color = clSilver;
		this->Button_start->Enabled = false;
	}
	else  {

		this->Button_port_open->Caption = "Çàêðûòü ïîðò";
		this->Edit_port_prop->Color = clLime;
        this->Button_start->Enabled = true;
    }

	sensor = system->GetSensor();
	SensorView();

		this->Label_msg->Visible = false;
		this->ProgressBar_scan->Visible = false;
		this->Label_msg_sensors->Visible = false;
		this->ComboBox_addr_found->Visible = false;

		this->ComboBox_protocol->ItemIndex = sensor->used_protocol;

}

void TForm_SensorAdjust::SensorView()
{
	this->ComboBox_sensor_addr->Text = utils_int_to_str(sensor->addr, 0);
	this->Edit_sensor_mark->Text = sensor->mark;

	this->Edit_serial->Text = utils_int_to_str(sensor->serial, 7);
	this->Edit_version->Text = utils_int_to_str(sensor->soft_version,0);
	this->ComboBox_addr->Text = utils_int_to_str(sensor->addr,0);

	this->Edit_serial->Text = "";
	this->Edit_version->Text = "";
	this->Edit_X->Text = "";
	this->Edit_Y->Text = "";

}

void TForm_SensorAdjust::Setup(TGBISystem* s)
{
	system = s;
}

void TForm_SensorAdjust::SetSensor()
{
	sensor->addr = (BYTE)StrToInt(this->ComboBox_sensor_addr->Text);
	sensor->mark = this->Edit_sensor_mark->Text;
    sensor->used_protocol = this->ComboBox_protocol->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TForm_SensorAdjust::Button_port_openClick(TObject *Sender)
{

	TChannel* p = system->GetPort();

	if (p->IsOpen() == true) {

		p->Close();
		this->Button_port_open->Caption = "Îòêðûòü ïîðò";
		this->Edit_port_prop->Color = clSilver;
		this->Button_start->Enabled = true;
	}
	else
	{
		if (p->Open() == 0)
		{
			this->Button_port_open->Caption = "Çàêðûòü ïîðò";
			this->Edit_port_prop->Color = clLime;
			this->Button_start->Enabled = true;
		}
		else
		{
			this->Button_port_open->Caption = "Îòêðûòü ïîðò";
			this->Edit_port_prop->Color = clSilver;
			Application->MessageBoxA(L"Íå óäàëîñü îòêðûòü ïîðò", L"Îøèáêà",0);
			this->Button_start->Enabled = false;
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm_SensorAdjust::Button_port_adjustClick(TObject *Sender)
{
   Form_PortAdjust->Setup(system);
   Form_PortAdjust->StartTimer();
   Form_PortAdjust->ShowModal();

   Start();
}
//---------------------------------------------------------------------------


void __fastcall TForm_SensorAdjust::FormClose(TObject *Sender, TCloseAction &Action)

{
	this->Timer_run->Enabled = false;
	this->Timer_scan->Enabled = false;

	serial_read = false;
	version_read = false;

    scan_mode = false;

}
//---------------------------------------------------------------------------

void __fastcall TForm_SensorAdjust::Timer_scanTimer(TObject *Sender)
{

		this->Timer_scan->Enabled = false;

		s_tmp->SetAddr(scan_addr);

		if (s_tmp->GetSerial() == 0) {
		//if (s_tmp->GetMeasResult() == 0) {

			total_sensors++;
			this->ComboBox_addr_found->Items->Add(utils_int_to_str(scan_addr, 0));
			AnsiString s;
			s.printf("Íàéäåíî äàò÷èêîâ ... %d", total_sensors);
			this->Label_msg->Caption = s;
		}


		scan_addr++;
		this->ProgressBar_scan->Position = scan_addr;

		if (scan_addr>=254) {

			AnsiString s("");
			s.printf("Äàò÷èêîâ íà ëèíèè %d", total_sensors);
			this->Label_msg_sensors->Visible=true;
			this->Label_msg_sensors->Caption=s;

			this->ComboBox_addr_found->Visible = true;
			this->ComboBox_addr_found->ItemIndex = 0;

			this->ProgressBar_scan->Visible = false;
            this->Label_msg->Visible = false;
			this->Button_start->Caption = "Ñòàðò";

			 if (total_sensors>0)
			 {
				 this->ComboBox_addr_found->ItemIndex = 0;

				 if (system->GetSensor()->addr != StrToInt(this->ComboBox_addr_found->Text))
				 {
					if (Application->MessageBoxA(L"Àäðåñ ïåðâîãî îáíàðóæåííîãî äàò÷èêà îòëè÷àåòñÿ îò íàñòðîåê ñèñòåìû. Ñîõðàíèüò â íàñòðîéêàõ íîâîå çíà÷åíèå àäðåñà?",L"Âíèìàíèå!",1)==IDOK) {

						system->GetSensor()->SetAddr(StrToInt(this->ComboBox_addr_found->Text));
						this->SensorView();
					}
				 }
			 }


			scan_mode = false;
			this->Timer_run->Enabled = true;
		}
		else
		{
			this->Timer_scan->Enabled = true;
			this->Timer_run->Enabled = true;
		}

}
//---------------------------------------------------------------------------


