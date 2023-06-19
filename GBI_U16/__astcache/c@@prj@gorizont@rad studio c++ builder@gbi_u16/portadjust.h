//---------------------------------------------------------------------------

#ifndef PortAdjustH
#define PortAdjustH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "defs.h"
#include "utils.h"
#include "GBISystem.h"
#include <Vcl.ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TForm_PortAdjust : public TForm
{
__published:	// IDE-managed Components
	TButton *Button_exit;
	TEdit *Edit_port_name;
	TComboBox *ComboBox_port_number;
	TComboBox *ComboBox_baud_rate;
	TButton *Button_save;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TCheckBox *CheckBox_port_on;
	TLabel *Label4;
	TComboBox *ComboBox_port_type;
	TLabel *Label5;
	TButton *Button_com_ports_scan;
	TTimer *Timer_start;
	void __fastcall Button_exitClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button_saveClick(TObject *Sender);
	void __fastcall Timer_startTimer(TObject *Sender);
private:	// User declarations

	TGBISystem* system;
	TChannel* port;
	void Start();

public:		// User declarations
	__fastcall TForm_PortAdjust(TComponent* Owner);

	void Setup(TGBISystem* s);
	void PortView();
	void StartTimer();

	void PortSet();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_PortAdjust *Form_PortAdjust;
//---------------------------------------------------------------------------
#endif
