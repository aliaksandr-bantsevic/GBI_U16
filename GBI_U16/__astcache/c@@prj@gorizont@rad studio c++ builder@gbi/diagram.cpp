//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Diagram.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_diagram *Form_diagram;
//---------------------------------------------------------------------------
__fastcall TForm_diagram::TForm_diagram(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_diagram::Chart_diagramEndDrag(TObject *Sender, TObject *Target,
		  int X, int Y)
{
	Sleep(1);
}
//---------------------------------------------------------------------------

void TForm_diagram::DrawVector(int xmax, int xmin, int ymax, int ymin, int lx, int ly)
{
	Chart_diagram->Color = clInfoBk;



	Chart_diagram->Legend[0].Visible = false;
	Chart_diagram->Series[0]->Clear();
	Chart_diagram->Series[0]->AddXY(0,0,"",clBlue);
	Chart_diagram->Series[0]->AddXY(5,5,"",clBlue);

	Chart_diagram->Series[1]->AddXY(0,-10,"",clRed);
	Chart_diagram->Series[1]->AddXY(0,10,"",clRed);

	Chart_diagram->Series[2]->AddXY(-10,0,"",clRed);
	Chart_diagram->Series[2]->AddXY(10,0,"",clRed);

	for (int i = -10; i < 10; i++) {



	}

}
