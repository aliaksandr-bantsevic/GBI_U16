//---------------------------------------------------------------------------

#ifndef MeasH
#define MeasH
//---------------------------------------------------------------------------


#include "utils.h"
#include "defs.h"
#include <Vcl.Grids.hpp>
#include "SysConfMgr.h"
#include "ExcelDrv.h"
#include "ExcelWait.h"

/*
	Îäíà çàïèñü èçìåðåíèÿ
*/

#define MAX_RECORDS_MEAS   500

typedef struct {

	double depth;
	double tuberr;

	double X1;
	double Y1;

	double X2;
	double Y2;

	double Xres;
	double Yres;

	double LX;
	double LY;
	double LR;
	double AR;

    double res[5];

} meas_record;


class TMeas {

public:

TMeas();
TMeas (TStringGrid* t, AnsiString n);
~TMeas();

meas_record records 	 [MAX_RECORDS_MEAS];
meas_record records_sort [MAX_RECORDS_MEAS];

private:

//int records_count;

public:

TStringGrid* table;
bool finalized;
TDateTime   create_time;
TDateTime   finalize_time;

int DataToTable(void);
int TableToData(void);
int Calculate(void);

TTreeNode* node;

int num;
int dnum;
int pnum;

TTreeNode* Redraw(TTreeView* t, TTreeNode* n);

AnsiString name;

void Select();
void Unselect();
bool selected;

AnsiString name_place;
AnsiString name_drill;

int type_drill;
int drill_start_point;
int single_way;

int LoadData();
int SaveData(int par);


int  records_cnt_def;
int  records_cnt;
int  ImportDepthTable(TMeas* m);
bool DeleteDir(AnsiString DirName);

TSysConfMgr* SysConfMgr;

int Excel (int par);

int Sort (int par);

double own_zero_shift;

AnsiString mark;

};

#endif
