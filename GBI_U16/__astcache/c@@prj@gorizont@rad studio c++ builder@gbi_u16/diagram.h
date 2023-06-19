//---------------------------------------------------------------------------

#ifndef DiagramH
#define DiagramH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.Chart.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.Series.hpp>
//---------------------------------------------------------------------------
class TForm_diagram : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TChart *Chart_diagram;
	TLineSeries *Series1;
	TLineSeries *Series2;
	TLineSeries *Series3;
	void __fastcall Chart_diagramEndDrag(TObject *Sender, TObject *Target, int X, int Y);

private:	// User declarations
public:		// User declarations
	__fastcall TForm_diagram(TComponent* Owner);

    void DrawVector(int xmax, int xmin, int ymax, int ymin, int lx, int ly);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm_diagram *Form_diagram;
//---------------------------------------------------------------------------
#endif
