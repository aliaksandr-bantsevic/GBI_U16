//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DrillAdjust.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_DrillAdjust *Form_DrillAdjust;
//---------------------------------------------------------------------------
__fastcall TForm_DrillAdjust::TForm_DrillAdjust(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_DrillAdjust::Button_applyClick(TObject *Sender)
{
    Update();

	 if (mode == 0) {

		 *str = this->Edit_name->Text;
		 *records_cnt = this->ComboBox_meas_cnt->Text.ToInt()+1;


			if (MAX_RECORDS_MEAS  < *records_cnt) {

				utils_ShowMessage("Ïðåâûøåí ëèìèò ÷èñëà óðîâíåé!");
				return;

			}

		 *single_way = (int) CheckBox_single->Checked;

        *ori = this->ComboBox_orient->ItemIndex;

		if (this->RadioButton_top->Checked)
		{
			*start_point = 0;
		}

		if (this->RadioButton_bot->Checked)
		{
			*start_point = 1;
		}

		if (this->RadioButton_start_first->Checked)
		{
			*start_request = 0;
		}

		if (this->RadioButton_start_last->Checked)
		{
			*start_request = 1;
		}

		if (this->RadioButton_start_first->Checked)
		{
			*start_request = 0;
		}

		if (this->RadioButton_start_last->Checked)
		{
			*start_request = 1;
		}

		if (this->ComboBox_orient->ItemIndex == 0) {

			this->RadioGroup1->Visible = false;
			this->RadioButton_top->Visible = false;
			this->RadioButton_bot->Visible = false;

		}
		else
		{
			this->RadioGroup1->Visible = true;
			this->RadioButton_top->Visible = true;
			this->RadioButton_bot->Visible = true;
		}

	 }
	 else
	 {
		 drill->name =  this->Edit_name->Text;
	 }

	 if (drill!=NULL) {

		 drill->drill_orient = this->ComboBox_orient->ItemIndex;
		 drill->drill_asimut = this->Edit_asimut->Text.ToDouble();
		 drill->own_zero_shift = this->Edit_zshift->Text.ToDouble();
		 drill->records_cnt = this->ComboBox_meas_cnt->Text.ToDouble()+1;

		 if (CheckBox_single->Checked)
		 {
			 drill->single_way = 1;
		 }
		 else
		 {
			 drill->single_way = 0;
		 }

		if (this->RadioButton_top->Checked)
		{
			drill->start_point = 0;
		}

		if (this->RadioButton_bot->Checked)
		{
			drill->start_point = 1;
		}

		if (this->RadioButton_start_first->Checked)
		{
			drill->i_first_request_point = 0;
		}

		if (this->RadioButton_start_last->Checked)
		{
			drill->i_first_request_point = 1;
		}


	 }

	Close();
}

void TForm_DrillAdjust::Start()
{
		Timer_start->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TForm_DrillAdjust::Timer_startTimer(TObject *Sender)
{

	Timer_start->Enabled = false;

	if (mode == 0) {

		this->Button_apply->Caption = "Äîáàâèòü";
		Caption = "Äîáàâèòü ñêâàæèíó";
		this->Edit_name->Text = "Ñêâàæèíà";
		this->ComboBox_meas_cnt->Enabled = true;
		CheckBox_single->Checked = false;
		CheckBox_single->Enabled = true;
		this->ComboBox_orient->Enabled = true;

		this->RadioButton_top->Checked = true;

		this->RadioGroup1->Visible = false;
		this->RadioButton_top->Visible = false;
		this->RadioButton_bot->Visible = false;

        this->ComboBox_orient->ItemIndex = 0;
	}
	else
	{
		this->Button_apply->Caption = "Ïðèìåíèòü";
		Caption = "Íàñòðîèòü ñêâàæèíó";
		this->Edit_name->Text = drill->name;

		if (drill->i_first_request_point == 0) {

			this->RadioButton_start_first->Checked = true;
			this->RadioButton_start_last->Checked = false;
		}
		else
		{
			this->RadioButton_start_first->Checked = false;
			this->RadioButton_start_last->Checked = true;
        }


		if (drill->meas_list_idx>0) {

			this->ComboBox_meas_cnt->Enabled = false;
			this->ComboBox_orient->Enabled = false;
			this->CheckBox_single->Enabled = false;
		}
		else
		{
			this->ComboBox_meas_cnt->Enabled = true;
			this->ComboBox_orient->Enabled = true;
			this->CheckBox_single->Enabled = true;
        }

		CheckBox_single->Checked = (bool)drill->single_way;


		if (drill->drill_orient == 0)
		{
			this->RadioGroup1->Visible = false;
			this->RadioButton_top->Visible = false;
			this->RadioButton_bot->Visible = false;
		}
		else
		{

			this->RadioGroup1->Visible = true;
			this->RadioButton_top->Visible = true;
			this->RadioButton_bot->Visible = true;


			if (drill->start_point == 0)
			{
				this->RadioButton_top->Checked = true;

			}
			else
			{
				this->RadioButton_bot->Checked = true;
			}
		}

	}


	 AnsiString s("");

	 for (int i = 10; i <= MAX_RECORDS_MEAS; i+=10) {

		s.printf("%d",i);
		this->ComboBox_meas_cnt->Items->Add(s);
	 }


	 if (mode == 1) {

		 s.printf("%d",drill->records_cnt-1);

	 }
	 else
	 {
		 s.printf("%d",records_cnt_def);
	 }

	this->ComboBox_meas_cnt->Text = s;

	if (drill != NULL) {

		this->ComboBox_orient->ItemIndex = drill->drill_orient;
		s.printf("%.1f",drill->drill_asimut);
		this->Edit_asimut->Text = s;

		if (drill->drill_orient == DRILL_ORIENT_VERTICAL)
		{
			this->CheckBox_single->Visible = false;
			this->Edit_asimut->Visible = true;
			this->Label_asimut->Visible = true;
		}

		if (drill->drill_orient == DRILL_ORIENT_HORIZONT)
		{
			this->CheckBox_single->Visible = true;
			this->Edit_asimut->Visible = false;
			this->Label_asimut->Visible = false;
		}

		s.printf("%.1f",drill->own_zero_shift);
		this->Edit_zshift->Text = s;

	}
	else
	{
		this->Edit_asimut->Text = "0.0";
		this->Edit_zshift->Text = "0.0";
		this->ComboBox_orient->ItemIndex = 0;
	}


}
//---------------------------------------------------------------------------
void __fastcall TForm_DrillAdjust::Button_cancelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm_DrillAdjust::FormCreate(TObject *Sender)
{
	drill = NULL;
	str = NULL;
	records_cnt = NULL;
	as = NULL;
	single_way = NULL;

	MACRO_FORM_MOVE_TO_THE_CENTER
	records_cnt_def = 20;
	this->ComboBox_orient->Clear();
	this->ComboBox_orient->Items->Add("Ãîðèçîíòàëüíàÿ");
	this->ComboBox_orient->Items->Add("Âåðòèêàëüíàÿ");

	this->RadioButton_start_first->Checked = true;

}
//---------------------------------------------------------------------------


void __fastcall TForm_DrillAdjust::ComboBox_orientChange(TObject *Sender)
{
	ComboBox_orient->Update();

	if (this->ComboBox_orient->ItemIndex == 1)
	{
		this->CheckBox_single->Visible = false;
		this->Edit_asimut->Visible = true;
		this->Label_asimut->Visible = true;

		this->RadioGroup1->Visible = true;
		this->RadioButton_top->Visible = true;
		this->RadioButton_bot->Visible = true;

	}

	if (this->ComboBox_orient->ItemIndex == 0)
	{
		this->CheckBox_single->Visible = true;
		this->Edit_asimut->Visible = false;
		this->Label_asimut->Visible = false;

		this->RadioGroup1->Visible = false;
		this->RadioButton_top->Visible = false;
		this->RadioButton_bot->Visible = false;

	}

}
//---------------------------------------------------------------------------






