//---------------------------------------------------------------------------

#ifndef DrillAdjustH
#define DrillAdjustH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "defs.h"
#include "Drill.h"

//---------------------------------------------------------------------------
class TForm_DrillAdjust : public TForm
{
__published:	// IDE-managed Components
	TButton *Button_cancel;
	TButton *Button_apply;
	TEdit *Edit_name;
	TLabel *Label1;
	TTimer *Timer_start;
	TComboBox *ComboBox_meas_cnt;
	TLabel *Label2;
	TEdit *Edit_asimut;
	TLabel *Label_asimut;
	TComboBox *ComboBox_orient;
	TLabel *Label4;
	TCheckBox *CheckBox_single;
	TEdit *Edit_zshift;
	TRadioGroup *RadioGroup1;
	TRadioButton *RadioButton_top;
	TRadioButton *RadioButton_bot;
	TGroupBox *GroupBox_start_collect_data;
	TRadioButton *RadioButton_start_first;
	TRadioButton *RadioButton_start_last;
	TGroupBox *GroupBox2;
	TCheckBox *CheckBox_GeoOn;
	TEdit *Edit_Input_point;
	TEdit *Edit_Output_point;
	TLabel *Label3;
	TLabel *Label5;
	void __fastcall Button_applyClick(TObject *Sender);
	void __fastcall Timer_startTimer(TObject *Sender);
	void __fastcall Button_cancelClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ComboBox_orientChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm_DrillAdjust(TComponent* Owner);


    int mode;
	void Start();
	TDrill* drill;
	int* records_cnt;
	int records_cnt_def;

	/*
	TCHAR* str;


	double* as;
	int* single_way;
	int* start_point;
	int* ori;
	int* start_request;
	*/

	bool OK;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_DrillAdjust *Form_DrillAdjust;
//---------------------------------------------------------------------------
#endif
