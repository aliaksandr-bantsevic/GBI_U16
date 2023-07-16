//---------------------------------------------------------------------------

#ifndef PlaceAdjustH
#define PlaceAdjustH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "defs.h"
#include "Place.h"
#include <Vcl.ExtCtrls.hpp>

#include "place.h"
//---------------------------------------------------------------------------
class TForm_PlaceAdjust : public TForm
{
__published:	// IDE-managed Components
	TEdit *Edit_name;
	TButton *Button_apply;
	TButton *Button_cance;
	TLabel *Label1;
	TTimer *Timer_start;
	void __fastcall Button_canceClick(TObject *Sender);
	void __fastcall Button_applyClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Timer_startTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm_PlaceAdjust(TComponent* Owner);

	//WideString* str;

	TPlace* place;
	int mode;
	void Start();
    bool OK;

};
//---------------------------------------------------------------------------
extern PACKAGE TForm_PlaceAdjust *Form_PlaceAdjust;
//---------------------------------------------------------------------------
#endif
