//---------------------------------------------------------------------------

#pragma hdrstop

#include "Place.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


TPlace::TPlace()
{
	node = NULL;
	name = "Ïëîùàäêà";
	num = 0;
}

TPlace::TPlace(AnsiString n)
{
	node = NULL;
	name = n;
	num = 0;

	for (int i = 0; i < SYSTEM_DRILLS_MAX; i++) {

		drill_list[i] = NULL;

	}

	drill_list_idx = 0;
}


TPlace::~TPlace()
{

}


TTreeNode* TPlace::Redraw(TTreeView* t, TTreeNode* n)
{
	if (n == NULL) {

		return NULL;
	}

	AnsiString s("");

	s.printf("%d [%s]",  num, name.c_str());

	node  =	t->Items->AddChild(n,s);
	utils_set_tree_node_view(node, SYSTEM_NODE_PLACE, SYSTEM_NODE_STATE_NORMAL);

		for (int i = 0; i < drill_list_idx; i++) {

			drill_list[i]->Redraw(t, node);

		}

    node->Expand(true);
	return node;
}

TTreeNode* TPlace::GetNode()
{
	return node;
}

void TPlace::SetName(AnsiString n)
{
    name = n;
}

AnsiString TPlace::GetName()
{
	return name;
}

int TPlace::SaveConfig (TIniFile* ini)
{
	AnsiString section("");
	AnsiString value("");

	section.printf("PLACE%d", this->num);
	ini->WriteString(section, "NAME", this->name);
	ini->WriteInteger(section, "INDEX", this->num);

		for (int i = 0; i < drill_list_idx; i++) {

			drill_list[i]->SaveConfig(ini);
		}


	return 0;
}

int TPlace::AddDrill(AnsiString n, int cnt)
{

	for (int i = 0; i < drill_list_idx; i++) {

		if (drill_list[i]->name == n) {

            ShowMessage("Äàííîå èìÿ ñêâàæèíû óæå ñóùåñòâóåò!");
			return -2;
		}
	}

	TDrill* d = new TDrill(n);

	d->num = drill_list_idx+1;
	d->pnum = this->num;
	d->records_cnt = cnt;

	drill_list[drill_list_idx] = d;
	drill_list_idx++;

	return 0;
}

int TPlace::LoadDrillConfig(TIniFile* ini)
{
	AnsiString section("");
	AnsiString spar("");
	int ipar = -1;

	for (int i = 0; i < SYSTEM_DRILLS_MAX; i++) {

		section.printf("DRILL%d.%d",num,i+1);
		spar = ini->ReadString(section, "NAME", "endoflist");


			if (spar!="endoflist") {

				ipar = ini->ReadInteger(section, "RECCNT", MAX_RECORDS_MEAS);
				AddDrill(spar,ipar);

				ipar = ini->ReadInteger(section, "ORIENT", 0);
				drill_list[drill_list_idx-1]->drill_orient = ipar;

				ipar = ini->ReadInteger(section, "STARTPOINT", 0);
				drill_list[drill_list_idx-1]->start_point = ipar;

				ipar = ini->ReadInteger(section, "STARTREQUEST", 0);
				drill_list[drill_list_idx-1]->i_first_request_point = ipar;


				spar =  ini->ReadString(section, "ASIMUT", "0.0");

				try
				{
					drill_list[drill_list_idx-1]->drill_asimut = spar.ToDouble();
				}
				catch (...)
				{

                }

				spar =  ini->ReadString(section, "ZEROSHIFT", "0.0");

				try
				{
					drill_list[drill_list_idx-1]->own_zero_shift = spar.ToDouble();
				}
				catch (...)
				{

                }

				drill_list[drill_list_idx-1]->single_way =  ini->ReadInteger(section, "SINGLEWAY", 0);
				drill_list[drill_list_idx-1]->LoadMeasConfig(ini);
  				drill_list[drill_list_idx-1]->pname = this->name;
			}
			else
			{
				break;
			}

	}

	return 0;
}

int TPlace::DeleteDrill(TDrill* d, int idx)
{

  for (int i = 0; i < drill_list_idx; i++) {

	if (i == idx) {

		if (d!=drill_list[idx]) {

			return -1; //Îøèáêà ýëåìåíòà ñèñòåìû
		}

		delete drill_list[idx];

		for (int i = idx+1; i < drill_list_idx; i++) {

			drill_list[i-1]=drill_list[i];
			drill_list[i-1]->num--;
		}

		drill_list_idx--;
	}

  }

  return 0;
}

