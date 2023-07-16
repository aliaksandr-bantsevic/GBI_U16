//---------------------------------------------------------------------------

#ifndef DepthAdjustH
#define DepthAdjustH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "utils.h"
#include "defs.h"
#include "Drill.h"

//---------------------------------------------------------------------------
class TForm_DepthAdjust : public TForm
{
__published:	// IDE-managed Components
	TButton *Button_enter;
	TButton *Button2;
	TEdit *Edit_depth;
	TEdit *Edit_trerr;
	TLabel *Label1;
	TLabel *Label_tuberr;
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button_enterClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);

	//void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	//void __fastcall FormKeyPress(TObject *Sender, System::WideChar &Key);
	//void __fastcall Edit_depthKeyPress(TObject *Sender, System::WideChar &Key);

	void __fastcall Edit_depthKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);

private:	// User declarations
public:		// User declarations
	__fastcall TForm_DepthAdjust(TComponent* Owner);

	TCHAR* str;
	TCHAR* str1;

};
//---------------------------------------------------------------------------
extern PACKAGE TForm_DepthAdjust *Form_DepthAdjust;
//---------------------------------------------------------------------------
#endif
