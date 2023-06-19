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
	TPlace(AnsiString n);
	~TPlace();

public:

	TTreeNode* node;
	AnsiString name;

public:

	TTreeNode* Redraw(TTreeView* t, TTreeNode* n);
	TTreeNode* GetNode();
	void SetName(AnsiString n);
	AnsiString GetName();

	int num;

	TDrill* drill_list[SYSTEM_DRILLS_MAX];
	int drill_list_idx;

	int SaveConfig (TIniFile* ini);
	int AddDrill(AnsiString n, int cnt);
	int LoadDrillConfig(TIniFile* ini);
	int DeleteDrill(TDrill* d, int idx);
};




#endif
