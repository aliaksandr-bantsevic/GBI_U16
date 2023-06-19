//---------------------------------------------------------------------------

#ifndef ExcelWaitH
#define ExcelWaitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include "defs.h"
//---------------------------------------------------------------------------
class TForm_excel_progress : public TForm
{
__published:	// IDE-managed Components
	TProgressBar *ProgressBar_excel;
	TLabel *Label1;
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm_excel_progress(TComponent* Owner);

void StartShow(int max);
void StopShow();
void UpdateShow(int pos);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm_excel_progress *Form_excel_progress;
//---------------------------------------------------------------------------
#endif
