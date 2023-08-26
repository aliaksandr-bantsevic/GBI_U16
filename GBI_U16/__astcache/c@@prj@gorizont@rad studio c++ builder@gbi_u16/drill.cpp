//---------------------------------------------------------------------------

#pragma hdrstop

#include "Drill.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

extern TStringGrid* global_meas_table;

TDrill::TDrill()
{
//	place = NULL;
	pnum = 0;
	num = 0;

	geo_data.geo_on = false;
	geo_data.input_point = 0.;
	geo_data.output_point = 0.;

	drill_asimut = 0.;
}



TDrill::TDrill(WideString n)
{
//	place = NULL;
	name = n;
	pnum = 0;
	num = 0;
	node = NULL;

	for (int i = 0; i < SYSTEM_MEAS_MAX; i++) {

		meas_list[i] = NULL;

	}

	meas_list_idx = 0;
	int records_cnt = 21;
	drill_orient = DRILL_ORIENT_HORIZONT;
    drill_asimut = 0;
	selected = false;
	pname = "";

	single_way = 0;
	start_point = DRILL_TOP_POINT;
	own_zero_shift = 0;

	i_first_request_point = DRILL_FIRST_REQUEST_TOP;

	geo_data.geo_on = false;
	geo_data.input_point = 0.;
	geo_data.output_point = 0.;

	drill_asimut = 0.;

}

TDrill::~TDrill()
{

}

TTreeNode* TDrill::Redraw(TTreeView* t, TTreeNode* n)
{
	if (n == NULL) {

		return NULL;
	}

	WideString s(L"");

	s.printf(L"%d.%d [%s]",  pnum, num, name.c_bstr());

	node  =	t->Items->AddChild(n,s);

	if (selected)
	{
		utils_set_tree_node_view(node, SYSTEM_NODE_DRILL, SYSTEM_NODE_STATE_ALARM);
	}
	else
	{
		utils_set_tree_node_view(node, SYSTEM_NODE_DRILL, SYSTEM_NODE_STATE_NORMAL);
	}


		for (int i = 0; i < meas_list_idx; i++) {

			meas_list[i]->Redraw(t, node);

		}


	return node;

}


int TDrill::SaveConfig (TIniFile* ini)
{
	WideString section(L"");
	WideString value(L"");
	WideString s(L"");

	section.printf(L"DRILL%d.%d", this->pnum, this->num);
	ini->WriteString(section, L"NAME", this->name);
	ini->WriteInteger(section, L"INDEX", this->num);
	ini->WriteInteger(section, L"PNDEX", this->pnum);
	ini->WriteInteger(section, L"RECCNT", this->records_cnt);

	ini->WriteInteger(section, L"ORIENT", this->drill_orient);
	ini->WriteInteger(section, L"STARTPOINT", this->start_point);
    ini->WriteInteger(section, L"STARTREQUEST", this->i_first_request_point);

	s.printf(L"%.1f",this->drill_asimut);
	ini->WriteString(section, L"ASIMUT", s);

	s.printf(L"%.1f",this->own_zero_shift);
	ini->WriteString(section, L"ZEROSHIFT", s);

	s.printf(L"%.2f",this->geo_data.input_point);
	ini->WriteString(section, L"GEO_INPUT_POINT", s);

	s.printf(L"%.2f",this->geo_data.output_point);
	ini->WriteString(section, L"GEO_OUTPUT_POINT", s);

	ini->WriteInteger(section,L"GEO_DATA_ON", geo_data.geo_on);

	ini->WriteInteger(section,L"SINGLEWAY", single_way);

		for (int i = 0; i < meas_list_idx; i++) {

			TMeas* m = meas_list[i];

			section.printf(L"MEAS%d.%d.%d", m->pnum, m->dnum, m->num);
			ini->WriteString(section, L"NAME", m->name);
			ini->WriteString(section, L"MARK", m->mark);
			ini->WriteInteger(section, L"INDEX", m->num);
			ini->WriteInteger(section, L"PNDEX", m->pnum);
			ini->WriteInteger(section, L"DNDEX", m->dnum);

		}


	return 0;
}

int TDrill::AddMeas(TStringGrid* t, WideString n)
{
	//TMeas* m = new TMeas(StringGrid_meas,n);

	TMeas* m = new TMeas(t,n);

	m->num = meas_list_idx+1;

	m->name.printf(L"Измерение_%d", meas_list_idx+1);
	m->mark.printf(L"Маркировка Измерение_%d", meas_list_idx+1);

	m->pnum = this->pnum;
	m->dnum = this->num;
	m->create_time = Now();
	m->records_cnt = records_cnt;

	m->type_drill = this->drill_orient;
	m->single_way = this->single_way;
	m->own_zero_shift = this->own_zero_shift;
    m->drill_start_point = this->start_point;

	m->geo_on = this->geo_data.geo_on;
	m->input_point = this->geo_data.input_point;
    m->output_point = this->geo_data.output_point;

	meas_list[meas_list_idx] = m;


	double tdepth = 0.0;

	if (meas_list_idx == 0) {

		for (int i = 0; i < records_cnt; i++) {

			m->records[i].depth = tdepth; tdepth+=0.5;
		}
	}

	meas_list_idx++;

	return 0;
}



int TDrill::UpdateMeas(void)
{

	TMeas* m;

	for (int i = 0; i < meas_list_idx; i++) {

		m = meas_list[i];
		m->geo_on = this->geo_data.geo_on;
		m->input_point = this->geo_data.input_point;
		m->output_point = this->geo_data.output_point;
	}


	return 0;
}


extern bool global_base_convert;

int TDrill::LoadMeasConfig(TIniFile* ini)
{
	WideString section(L"");
	WideString spar(L"");
	WideString mmark(L"");

	for (int i = 0; i < SYSTEM_MEAS_MAX; i++) {

		section.printf(L"MEAS%d.%d.%d",pnum,num,i+1);
		spar = ini->ReadString(section, L"NAME", L"endoflist");

			if (spar!="endoflist") {

				AddMeas(global_meas_table, L"Измерение");
				meas_list[meas_list_idx-1]->type_drill = this->drill_orient;
				meas_list[meas_list_idx-1]->drill_start_point = this->start_point;
				meas_list[meas_list_idx-1]->single_way = this->single_way;
				meas_list[meas_list_idx-1]->own_zero_shift = this->own_zero_shift;

				mmark = meas_list[meas_list_idx-1]->mark;
				spar = ini->ReadString(section, L"MARK", mmark);
				meas_list[meas_list_idx-1]->mark = spar;

				if (global_base_convert)
				{
				  meas_list[meas_list_idx-1]->SaveData(0);
				}
			}
			else
			{
				break;
            }

	}

	return 0;
}

int TDrill::DeleteMeas(TMeas* m, int idx)
{

  for (int i = 0; i < meas_list_idx; i++) {

	if (i == idx) {

		if (m!=meas_list[idx]) {

			return -1; //Îøèáêà ýëåìåíòà ñèñòåìû
		}

		delete meas_list[idx];

		for (int i = idx+1; i < meas_list_idx; i++) {



			//!!!rename(L"",L"");

			meas_list[i-1]=meas_list[i];
			meas_list[i-1]->num--;
		}

		meas_list_idx--;
	}

  }

  return 0;
}

void TDrill::Select()
{
	utils_set_tree_node_view(node, SYSTEM_NODE_DRILL, SYSTEM_NODE_STATE_ALARM);
	selected = true;
}

void TDrill::Unselect()
{
	utils_set_tree_node_view(node, SYSTEM_NODE_DRILL, SYSTEM_NODE_STATE_NORMAL);
	selected = false;
}

int TDrill::Excel(void)
{
	TCHAR dir[1024];
	wcscpy(dir,meas_list[0]->SysConfMgr->GetCurBase());
	wcscat(dir,pname.c_bstr());
	wcscat(dir,L"\\");
	wcscat(dir,name.c_bstr());
	wcscat(dir,L"\\");

	wcscat(dir,name.c_bstr());
	wcscat(dir,L".xlsx");

	TCHAR cmd[1024];
	wcscpy(cmd,L"del ");
	wcscat(cmd,L"\"");
	wcscat(cmd,dir);
	wcscat(cmd,L"\"");
	system((char*)cmd);

			if (OpenExcelReportTable(this->meas_list_idx) == false)
			{
				Application->MessageBoxW(L"Не удалось создать таблицу!",L"ОШИБКА",0);
				return -1;
			}

    Form_excel_progress->StartShow(records_cnt*meas_list_idx);

	for (int i = 0; i < meas_list_idx; i++) {

			if (meas_list[i]->Excel(0) != 0)
			{
					Application->MessageBoxW(L"Не удалось экспортировать измерение!",L"ОШИБКА",0);
				return -2;
			}
	}


	Form_excel_progress->StopShow();
	SaveExcelReport(dir);

	return 0;
}

int TDrill::ReCalc()
{
	for (int i = 0; i < meas_list_idx; i++) {
		meas_list[i]->drill_start_point = this->start_point;
		meas_list[i]->Calculate();
	}

	return 0;
}
