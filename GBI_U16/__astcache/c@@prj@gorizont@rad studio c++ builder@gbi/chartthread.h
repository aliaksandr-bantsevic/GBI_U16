//---------------------------------------------------------------------------

#ifndef ChartThreadH
#define ChartThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>

#include <tchar.h>
#include <VCLTee.Chart.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.Series.hpp>

#include "Drill.h"
#include <string.h>

#define DATA_SOURCE_X 		0
#define DATA_SOURCE_Y 		1
#define DATA_SOURCE_R       2

extern int g_xmax;
extern int g_xmin;
extern int g_ymax;
extern int g_ymin;
extern int g_lx;
extern int g_ly;


TColor ChartColorsTable [] = {

clRed,
clBlue,
clGreen,
clLime,
clMaroon,
clGreen,
clOlive,
clNavy,
clPurple,
clTeal,
clGray,
clGreen,
clRed,
clLime,
clBlue,
clMoneyGreen,
clSkyBlue,
clBlue,
clMedGray,
clOlive

 };



//---------------------------------------------------------------------------
class TChartThread : public TThread
{

public:

/*
	TChartThread();
	TChartThread(TChart* c);
	~TChartThread();
*/

	TChart* chart;
	bool redraw_flag;
	int data_source;
	TDrill* drill;

public:

	int thread_num;

	void Redraw(void);
	void __fastcall StartRedraw(void);
	void SetDrill(TDrill* d);

	void SetName();

private:
protected:
	void __fastcall Execute();
public:
	__fastcall TChartThread(bool CreateSuspended);
	__fastcall TChartThread(bool CreateSuspended, TChart* c, int ds, int num);

};
//---------------------------------------------------------------------------
#endif
