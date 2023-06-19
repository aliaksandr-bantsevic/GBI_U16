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
	TGroupBox *GroupBox1;
	TRadioButton *RadioButton_start_first;
	TRadioButton *RadioButton_start_last;
	void __fastcall Button_applyClick(TObject *Sender);
	void __fastcall Timer_startTimer(TObject *Sender);
	void __fastcall Button_cancelClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ComboBox_orientChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm_DrillAdjust(TComponent* Owner);


    TDrill* drill;
	AnsiString* str;
	int mode;
	void Start();

	int records_cnt_def;
	int* records_cnt;
	double* as;
	int* single_way;
	int* start_point;
	int* ori;
    int* start_request;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_DrillAdjust *Form_DrillAdjust;
//---------------------------------------------------------------------------
#endif
