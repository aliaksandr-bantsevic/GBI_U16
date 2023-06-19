//---------------------------------------------------------------------------

#ifndef AboutH
#define AboutH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "defs.h"
//---------------------------------------------------------------------------
class TForm_about : public TForm
{
__published:	// IDE-managed Components
	TButton *Button_close;
	TLabel *Label_version;
	TLabel *Label2;
	TLabel *Label_year;
	void __fastcall Button_closeClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm_about(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_about *Form_about;
//---------------------------------------------------------------------------
#endif
