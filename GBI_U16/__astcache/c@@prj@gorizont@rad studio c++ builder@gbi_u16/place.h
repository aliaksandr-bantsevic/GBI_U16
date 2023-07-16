//---------------------------------------------------------------------------

#ifndef PlaceH
#define PlaceH
//---------------------------------------------------------------------------

#include "defs.h"
#include "utils.h"
#include "Drill.h"

#define SYSTEM_DRILLS_MAX   100

class TPlace {

public:

	TPlace();
	TPlace(WideString n);
	~TPlace();

public:

	TTreeNode* node;
	WideString name;

public:

	TTreeNode* Redraw(TTreeView* t, TTreeNode* n);
	TTreeNode* GetNode();
	void SetName(WideString n);
	WideString GetName();

	int num;

	TDrill* drill_list[SYSTEM_DRILLS_MAX];
	int drill_list_idx;

	int SaveConfig (TIniFile* ini);
	int AddDrill(WideString n, int cnt);
	int TPlace::AddDrill(TDrill* drill);
	int LoadDrillConfig(TIniFile* ini);
	int DeleteDrill(TDrill* d, int idx);
    int UpdateDrill(TDrill* d, TDrill* drill);
};




#endif
