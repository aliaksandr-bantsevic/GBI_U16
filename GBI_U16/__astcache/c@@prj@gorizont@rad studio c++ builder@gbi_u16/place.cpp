//---------------------------------------------------------------------------

#pragma hdrstop

#include "Place.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


TPlace::TPlace()
{
	node = NULL;
	name = L"Площадка";
	num = 0;
}

TPlace::TPlace(WideString n)
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

	WideString s(L"");

	s.printf(L"%d [%s]",  num, name.c_bstr());

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

void TPlace::SetName(WideString n)
{
    name = n;
}

WideString TPlace::GetName()
{
	return name;
}

int TPlace::SaveConfig (TIniFile* ini)
{
	WideString section(L"");
	WideString value(L"");

	section.printf(L"PLACE%d", this->num);
	ini->WriteString(section, L"NAME", this->name);
	ini->WriteInteger(section, L"INDEX", this->num);

		for (int i = 0; i < drill_list_idx; i++) {

			drill_list[i]->SaveConfig(ini);
		}


	return 0;
}

int TPlace::AddDrill(WideString n, int cnt)
{

	for (int i = 0; i < drill_list_idx; i++) {

		if (drill_list[i]->name == n) {

			ShowMessage(L"Данное имя скважины уже существует!");
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

int TPlace::AddDrill(TDrill* drill)
{

	for (int i = 0; i < drill_list_idx; i++) {

		if (drill_list[i]->name == drill->name) {

			ShowMessage(L"Данное имя скважины уже существует!");
			return -2;
		}
	}

	TDrill* d = new TDrill();

	d->name = drill->name;
	d->num = drill_list_idx+1;
	d->pnum = this->num;
	d->records_cnt = drill->records_cnt;
	d->i_first_request_point = drill->i_first_request_point;
	d->start_point = drill->start_point;
	d->single_way = drill->single_way;
	d->drill_orient = drill->drill_orient;
	d->drill_asimut = drill->drill_asimut;

	drill_list[drill_list_idx] = d;
	drill_list_idx++;

	return 0;

}

int TPlace::UpdateDrill(TDrill* d, TDrill* drill)
{

	d->name = drill->name;
	d->records_cnt = drill->records_cnt;
	d->i_first_request_point = drill->i_first_request_point;
	d->start_point = drill->start_point;
	d->single_way = drill->single_way;
	d->drill_orient = drill->drill_orient;
    d->drill_asimut = drill->drill_asimut;
    d->geo_data = drill->geo_data;

	return 0;

}

int TPlace::LoadDrillConfig(TIniFile* ini)
{
	WideString section(L"");
	WideString spar(L"");
	int ipar = -1;

	for (int i = 0; i < SYSTEM_DRILLS_MAX; i++) {

		section.printf(L"DRILL%d.%d",num,i+1);
		spar = ini->ReadString(section, L"NAME", L"endoflist");


			if (spar!=L"endoflist") {

				ipar = ini->ReadInteger(section, L"RECCNT", MAX_RECORDS_MEAS);
				AddDrill(spar,ipar);

				ipar = ini->ReadInteger(section, L"ORIENT", 0);
				drill_list[drill_list_idx-1]->drill_orient = ipar;

				ipar = ini->ReadInteger(section, L"STARTPOINT", 0);
				drill_list[drill_list_idx-1]->start_point = ipar;

				ipar = ini->ReadInteger(section, L"STARTREQUEST", 0);
				drill_list[drill_list_idx-1]->i_first_request_point = ipar;


				spar = ini->ReadString(section, L"GEO_INPUT_POINT", L"0.0");
				drill_list[drill_list_idx-1]->geo_data.input_point = spar.ToDouble();

				spar = ini->ReadString(section, L"GEO_OUTPUT_POINT", L"0.0");
				drill_list[drill_list_idx-1]->geo_data.output_point = spar.ToDouble();

				drill_list[drill_list_idx-1]->geo_data.geo_on = ini->ReadInteger(section,L"GEO_DATA_ON", 0);

				spar =  ini->ReadString(section, L"ASIMUT", L"0.0");

				try
				{
					drill_list[drill_list_idx-1]->drill_asimut = spar.ToDouble();
				}
				catch (...)
				{

                }

				spar =  ini->ReadString(section, L"ZEROSHIFT", L"0.0");

				try
				{
					drill_list[drill_list_idx-1]->own_zero_shift = spar.ToDouble();
				}
				catch (...)
				{

                }

				drill_list[drill_list_idx-1]->single_way =  ini->ReadInteger(section, L"SINGLEWAY", 0);
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

			return -1;
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

