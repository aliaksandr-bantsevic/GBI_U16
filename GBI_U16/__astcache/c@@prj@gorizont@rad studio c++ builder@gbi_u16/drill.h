//---------------------------------------------------------------------------

#ifndef DrillH
#define DrillH
//---------------------------------------------------------------------------

#include "defs.h"
#include "utils.h"
//#include "Place.h"
#include "Meas.h"
#define SYSTEM_MEAS_MAX   100

#define DRILL_ORIENT_HORIZONT     0
#define DRILL_ORIENT_VERTICAL     1

#define DRILL_TOP_POINT     0
#define DRILL_BOT_POINT     1

#define DRILL_FIRST_REQUEST_TOP     0
#define DRILL_FIRST_REQUEST_BOT     1

//extern TStringGrid* StringGrid_meas;

class TDrill {

public:

	TDrill();
	TDrill(WideString n);
	~TDrill();


//TPlace* place;


private:



public:

TTreeNode* node;

WideString name;
int pnum;
int num;

TTreeNode* Redraw(TTreeView* t, TTreeNode* n);
int SaveConfig (TIniFile* ini);

TMeas* meas_list[SYSTEM_MEAS_MAX];
int    meas_list_idx;

int AddMeas(TStringGrid* t, WideString n);
int LoadMeasConfig(TIniFile* ini);
int DeleteMeas(TMeas* m, int idx);

int records_cnt;

int drill_orient;

double drill_asimut;

bool selected;

void Select();
void Unselect();

WideString pname;

int single_way;

int start_point;

double own_zero_shift;

int Excel(void);

int ReCalc();

public:

int i_first_request_point;

struct {

	bool geo_on;
	double input_point;
    double output_point;

} geo_data;

int UpdateMeas(void);

};





#endif
