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
}


TDrill::TDrill(AnsiString n)
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
}

TDrill::~TDrill()
{

}

TTreeNode* TDrill::Redraw(TTreeView* t, TTreeNode* n)
{
	if (n == NULL) {

		return NULL;
	}

	AnsiString s("");

	s.printf("%d.%d [%s]",  pnum, num, name.c_str());

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
	AnsiString section("");
	AnsiString value("");
	AnsiString s("");

	section.printf("DRILL%d.%d", this->pnum, this->num);
	ini->WriteString(section, "NAME", this->name);
	ini->WriteInteger(section, "INDEX", this->num);
	ini->WriteInteger(section, "PNDEX", this->pnum);
	ini->WriteInteger(section, "RECCNT", this->records_cnt);

	ini->WriteInteger(section, "ORIENT", this->drill_orient);
	ini->WriteInteger(section, "STARTPOINT", this->start_point);
    ini->WriteInteger(section, "STARTREQUEST", this->i_first_request_point);

	s.printf("%.1f",this->drill_asimut);
	ini->WriteString(section, "ASIMUT", s);

	s.printf("%.1f",this->own_zero_shift);
	ini->WriteString(section, "ZEROSHIFT", s);

	ini->WriteInteger(section,"SINGLEWAY", single_way);

		for (int i = 0; i < meas_list_idx; i++) {

			TMeas* m = meas_list[i];

			section.printf("MEAS%d.%d.%d", m->pnum, m->dnum, m->num);
			ini->WriteString(section, "NAME", m->name);
			ini->WriteString(section, "MARK", m->mark);
			ini->WriteInteger(section, "INDEX", m->num);
			ini->WriteInteger(section, "PNDEX", m->pnum);
			ini->WriteInteger(section, "DNDEX", m->dnum);

		}


	return 0;
}

int TDrill::AddMeas(TStringGrid* t, AnsiString n)
{
	//TMeas* m = new TMeas(StringGrid_meas,n);

	TMeas* m = new TMeas(t,n);

	m->num = meas_list_idx+1;

	m->name.printf("Èçìåðåíèå_%d", meas_list_idx+1);
	m->mark.printf("Ìàðêèðîâêà Èçìåðåíèå_%d", meas_list_idx+1);

	m->pnum = this->pnum;
	m->dnum = this->num;
	m->create_time = Now();
	m->records_cnt = records_cnt;

	m->type_drill = this->drill_orient;
	m->single_way = this->single_way;
	m->own_zero_shift = this->own_zero_shift;
    m->drill_start_point = this->start_point;

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

int TDrill::LoadMeasConfig(TIniFile* ini)
{
	AnsiString section("");
	AnsiString spar("");
	AnsiString mmark("");

	for (int i = 0; i < SYSTEM_MEAS_MAX; i++) {

		section.printf("MEAS%d.%d.%d",pnum,num,i+1);
		spar = ini->ReadString(section, "NAME", "endoflist");

			if (spar!="endoflist") {

				AddMeas(global_meas_table, "Èçìåðåíèå");
				meas_list[meas_list_idx-1]->type_drill = this->drill_orient;
				meas_list[meas_list_idx-1]->drill_start_point = this->start_point;
				meas_list[meas_list_idx-1]->single_way = this->single_way;
				meas_list[meas_list_idx-1]->own_zero_shift = this->own_zero_shift;

				mmark = meas_list[meas_list_idx-1]->mark;
				spar = ini->ReadString(section, "MARK", mmark);
				meas_list[meas_list_idx-1]->mark = spar;
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



			rename("","");

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
	char dir[1024];
	strcpy(dir,meas_list[0]->SysConfMgr->GetCurBase());
	strcat(dir,pname.c_str());
	strcat(dir,"\\");
	strcat(dir,name.c_str());
	strcat(dir,"\\");

	//AnsiString nrep("");
	//nrep = FormatDateTime("dd_mm_yyyy_hh_nn_ss",Now());
	//strcat(dir,nrep.c_str());
	strcat(dir,name.c_str());
	strcat(dir,".xlsx");

	char cmd[1024];
	strcpy(cmd,"del ");
	strcat(cmd,"\"");
	strcat(cmd,dir);
	strcat(cmd,"\"");
	system(cmd);

			if (OpenExcelReportTable(this->meas_list_idx) == false)
			{
				Application->MessageBoxA(L"Íå óäàëîñü ñîçäàòü òàáëèöó!",L"ÎØÈÁÊÀ",0);
				return -1;
			}

    Form_excel_progress->StartShow(records_cnt*meas_list_idx);

	for (int i = 0; i < meas_list_idx; i++) {

			if (meas_list[i]->Excel(0) != 0)
			{
					Application->MessageBox(L"Íå óäàëîñü ýêñïîðòèðîâàòü èçìåðåíèå!",L"ÎØÈÁÊÀ",0);
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
