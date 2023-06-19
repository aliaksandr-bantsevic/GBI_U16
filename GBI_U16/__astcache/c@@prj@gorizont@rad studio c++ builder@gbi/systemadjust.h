//---------------------------------------------------------------------------

#ifndef SystemAdjustH
#define SystemAdjustH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>

#include "defs.h"
#include "SensorAdjust.h"
#include "GBISystem.h"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm_SystemAdjust : public TForm
{
__published:	// IDE-managed Components
	TButton *Button_exit;
	TButton *Button1;
	TPageControl *PageControl_system_adjust;
	TTabSheet *TabSheet_system_adjust_common;
	TLabel *Label1;
	TLabel *Label6;
	TLabel *Label7;
	TEdit *Edit_name;
	TComboBox *ComboBox_records_max;
	TComboBox *ComboBox_records_default;
	TTimer *Timer_start;
	TCheckBox *CheckBox_ask_param_apply;
	TLabel *Label8;
	TTabSheet *TabSheet_backup;
	TComboBox *ComboBox_backup;
	TLabel *Label9;
	TCheckBox *CheckBox_backup;
	TLabel *Label10;
	TTabSheet *TabSheet_timers;
	TLabel *Label2;
	TComboBox *ComboBox_ask_sensor_period;
	TLabel *Label3;
	TComboBox *ComboBox_tout_read;
	TLabel *Label4;
	TComboBox *ComboBox_tout_write;
	TLabel *Label5;
	TComboBox *ComboBox_cmd_delay;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button_exitClick(TObject *Sender);
	void __fastcall Timer_startTimer(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall CheckBox_backupClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm_SystemAdjust(TComponent* Owner);

	void Start();

	TGBISystem* system;

};
//---------------------------------------------------------------------------
extern PACKAGE TForm_SystemAdjust *Form_SystemAdjust;
//---------------------------------------------------------------------------
#endif
