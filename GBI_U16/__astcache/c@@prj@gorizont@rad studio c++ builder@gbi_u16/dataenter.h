//---------------------------------------------------------------------------

#ifndef DataEnterH
#define DataEnterH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "defs.h"
//---------------------------------------------------------------------------
class TForm_data_enter : public TForm
{
__published:	// IDE-managed Components
	TButton *Button_apply;
	TButton *Button_cancel;
	TEdit *Edit_data;
	void __fastcall Button_cancelClick(TObject *Sender);
	void __fastcall Button_applyClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm_data_enter(TComponent* Owner);
public:
	TCHAR* s;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_data_enter *Form_data_enter;
//---------------------------------------------------------------------------
#endif
