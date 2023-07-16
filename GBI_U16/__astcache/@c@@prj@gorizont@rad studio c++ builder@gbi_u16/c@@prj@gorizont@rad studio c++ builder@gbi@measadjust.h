//---------------------------------------------------------------------------

#ifndef MeasAdjustH
#define MeasAdjustH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "Meas.h"
#include "defs.h"

//---------------------------------------------------------------------------
class TForm_MeasAdjust : public TForm
{
__published:	// IDE-managed Components
	TButton *Button_apply;
	TButton *Button_cancel;
	TEdit *Edit_mark;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TStaticText *StaticText_place;
	TStaticText *StaticText_drill;
	void __fastcall Button_applyClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button_cancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm_MeasAdjust(TComponent* Owner);

public:

	TMeas* meas;
	void StartShow();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_MeasAdjust *Form_MeasAdjust;
//---------------------------------------------------------------------------
#endif
