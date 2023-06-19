//---------------------------------------------------------------------------

#ifndef SensorAdjustH
#define SensorAdjustH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "defs.h"
#include "utils.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "GBISystem.h"
#include "PortAdjust.h"

//---------------------------------------------------------------------------
class TForm_SensorAdjust : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl_sensor;
	TTabSheet *TabSheet_sensor_main;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TComboBox *ComboBox_sensor_type;
	TEdit *Edit_sensor_mark;
	TComboBox *ComboBox_sensor_addr;
	TCheckBox *CheckBox_sensor_on;
	TButton *Button_exit;
	TButton *Button_save;
	TTabSheet *TabSheet_sensor_extended;
	TTimer *Timer_run;
	TTimer *Timer_start;
	TGroupBox *GroupBox1;
	TButton *Button_port_open;
	TEdit *Edit_port_prop;
	TButton *Button_port_adjust;
	TGroupBox *Sensor;
	TEdit *Edit_serial;
	TEdit *Edit_version;
	TEdit *Edit_X;
	TEdit *Edit_Y;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TComboBox *ComboBox_addr;
	TLabel *Label9;
	TGroupBox *GroupBox2;
	TButton *Button_start;
	TButton *Button_set_addr;
	TProgressBar *ProgressBar_scan;
	TLabel *Label_msg;
	TComboBox *ComboBox_addr_found;
	TLabel *Label_msg_sensors;
	TTimer *Timer_scan;
	TComboBox *ComboBox_protocol;
	TLabel *Label10;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button_exitClick(TObject *Sender);
	void __fastcall Button_saveClick(TObject *Sender);
	void __fastcall Button_startClick(TObject *Sender);
	void __fastcall Timer_runTimer(TObject *Sender);
	void __fastcall Timer_startTimer(TObject *Sender);
	void __fastcall Button_port_openClick(TObject *Sender);
	void __fastcall Button_port_adjustClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Timer_scanTimer(TObject *Sender);

private:	// User declarations

	TGBISystem* system;

public:		// User declarations
	__fastcall TForm_SensorAdjust(TComponent* Owner);
	void StartTimer();
	void Start();
	void SensorView();
	void Setup(TGBISystem* s);

	TSensor* sensor;

	void SetSensor();


};
//---------------------------------------------------------------------------
extern PACKAGE TForm_SensorAdjust *Form_SensorAdjust;
//---------------------------------------------------------------------------
#endif
