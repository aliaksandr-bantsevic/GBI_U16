//---------------------------------------------------------------------------

#ifndef SystemH
#define SystemH
//---------------------------------------------------------------------------



#include "defs.h"
#include "Channel.h"
#include "Sensor.h"
#include "Protocol_211.h"
#include "Meas.h"
#include "Place.h"
#include "SysConfMgr.h"

#define SYSTEM_PLACES_MAX   100

#define TREE_ITEM_TYPE_SYSTEM 		0
#define TREE_ITEM_TYPE_PORT 		1
#define TREE_ITEM_TYPE_SENSOR 		2
#define TREE_ITEM_TYPE_PLACE        3
#define TREE_ITEM_TYPE_DRILL 		4
#define TREE_ITEM_TYPE_MEAS         5

class TGBISystem {

public:

	  TGBISystem();
	  TGBISystem (TTreeView* t);
	  ~TGBISystem();

	  bool ask_save_par;
	  WideString name;

private:

	TTreeView* tree;
	TChannel port;
	TSensor sensor;

	bool run;

	TEdit* edit_meas_X;
	TEdit* edit_meas_Y;

public:

	TTreeNode* node;

//Ñïèñîê ìåñò

public:

	TPlace* place_list[SYSTEM_PLACES_MAX];
	int place_list_idx;

    TIniFile* system_ini;

public:

	TChannel* GetPort();
	TSensor* GetSensor();
	int OpenPort();

	void SaveSysConf();
	void LoadSysConf();
	void Start(TEdit* ex, TEdit* ey);
	void Stop (void);
	int RunProc(void);
	bool IsRunning (void);

	int Redraw (void);
	int CheckTreeItemSelected(int* type, int* idx, void** obj);
	int AddPlace(WideString name);
	int DeletePlace(TPlace* p, int idx);
	int Reindex(void);

	TEdit* edit_SKO;
	double sko_limit;
	void ViewSKOlimit();

	int ask_sensor_period;

	int max_records_meas;
	int def_records_meas;

	bool* ask_save_conf;

	int last_place_idx;
	int last_drill_idx;

	bool DeleteDir(WideString DirName);

	int ResaveData();
	int KillBase();
	int LoadData();

	TSysConfMgr SysConfMgr;

	int CreateConf (TSaveDialog* dlg);
	int OpenConf (void);
	int SaveConf (void);
	int OpenConf (TOpenDialog* dlg);
	int SaveConf (TSaveDialog* dlg);
	int Clear (void);
	int i_use_side_keyboard;
	void Collapse(void);
    TMeas* GetMeasByNode(TTreeNode *node);
};



#endif
