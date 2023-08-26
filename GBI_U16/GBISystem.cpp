//---------------------------------------------------------------------------

#pragma hdrstop

#include "GBISystem.h"
#include <vcl.h>
//#include <filesystem>
//---------------------------------------------------------------------------
#pragma package(smart_init)


 TGBISystem::TGBISystem (void)
 {
	   tree = NULL;
	   ask_save_par = true;
	   name = "";
	   run = false;
	   edit_meas_X = NULL;
	   edit_meas_Y = NULL;

	   node = NULL;
 }


 TGBISystem::TGBISystem (TTreeView* t)
 {
	   tree = t;
	   this->sensor.SetChan(&this->port);
	   run = false;
	   name = L"Gorizont Borehole Inclinpmeter System";
	   edit_meas_X = NULL;
	   edit_meas_Y = NULL;


	   for (int i = 0; i < SYSTEM_PLACES_MAX; i++) {

		   place_list[i] = NULL;

	   }

	   place_list_idx = 0;

	   system_ini=new TIniFile(ChangeFileExt(Application->ExeName,L".ini"));

	   edit_SKO = NULL;
	   sko_limit = 1;

	   max_records_meas = 100;
	   def_records_meas = 20;

	   ask_save_conf = NULL;

	   last_place_idx = -1;
	   last_drill_idx = -1;
       i_use_side_keyboard = 0;
 }


 TGBISystem::~TGBISystem (void)
 {

 }

TChannel* TGBISystem::GetPort()
{
	return &port;
}

TSensor* TGBISystem::GetSensor()
{
	return &sensor;
}

void TGBISystem::SaveSysConf()
{
	SysConfMgr.SaveCurConf();

	WideString sfold(L"");
	WideString sfnew(L"");

	sfold =  SysConfMgr.GetCurIniPath();
	sfnew = sfold+ L".bak";

	DeleteFile(sfnew);
	RenameFile(sfold,sfnew);

	TIniFile *ini = SysConfMgr.GetIniFile();

	ini->WriteString(L"SYSTEM",L"Name",this->name);

	ini->WriteBool(L"SYSTEM",L"ASKPARAMSAVE",*ask_save_conf);

	ini->WriteInteger(L"SYSTEM",L"SKOLIMIT",sko_limit);

	ini->WriteInteger(L"SYSTEM",L"askperiod",ask_sensor_period);

	max_records_meas = MAX_RECORDS_MEAS;

	ini->WriteInteger(L"SYSTEM",L"MAXRECORDS",max_records_meas);
	ini->WriteInteger(L"SYSTEM",L"DEFRECORDS",def_records_meas);

	ini->WriteInteger(L"SYSTEM",L"last_place_idx",last_place_idx);
	ini->WriteInteger(L"SYSTEM",L"last_drill_idx",last_drill_idx);

	ini->WriteInteger(L"PORT",L"ReadTimeOut",GetPort()->tout_rx);
	ini->WriteInteger(L"PORT",L"WriteTimeOut",GetPort()->tout_tx);
	ini->WriteInteger(L"PORT",L"PauseTransact",GetPort()->pause_transact);
	ini->WriteInteger(L"PORT",L"PauseReopen",GetPort()->pause_reopen);

	ini->WriteInteger(L"PORT",L"BaudRate",GetPort()->baud);
	ini->WriteInteger(L"PORT",L"Port",GetPort()->port);
	ini->WriteString(L"PORT",L"Mark",L"Порт инклинометра");

	ini->WriteInteger(L"SENSOR",L"Addr",GetSensor()->addr);
	ini->WriteString(L"SENSOR",L"Mark",GetSensor()->mark);
	ini->WriteInteger(L"SENSOR",L"Protocol",GetSensor()->used_protocol);

	ini->WriteInteger(L"SYSTEM",L"SideVirtKbd",i_use_side_keyboard);

	for (int i = 0; i < place_list_idx; i++) {

		place_list[i]->SaveConfig(system_ini);

	}



}

extern bool global_base_convert;

void TGBISystem::LoadSysConf()
{
	SysConfMgr.GetCurConf();

	system_ini = SysConfMgr.GetIniFile();
	//TIniFile *ini=new TIniFile(ChangeFileExt(Application->ExeName,L".ini"));
	TIniFile *ini =  SysConfMgr.GetIniFile();

	TChannel* port = GetPort();
	TSensor* sensor = GetSensor();

	name = ini->ReadString(L"SYSTEM",L"Name",L"Gorizont Borehole Inclinometer");

	*ask_save_conf = ini->ReadBool(L"SYSTEM",L"ASKPARAMSAVE",true);

	//b_MessageConfirmParamsetShow = ask_save_conf;

	sko_limit = ini->ReadInteger(L"SYSTEM",L"SKOLIMIT",1);

	ask_sensor_period = ini->ReadInteger(L"SYSTEM",L"askperiod",100);

	max_records_meas = ini->ReadInteger(L"SYSTEM",L"MEXRECORDS",100);

    max_records_meas = MAX_RECORDS_MEAS;

	def_records_meas = ini->ReadInteger(L"SYSTEM",L"DEFRECORDS",20);


	port->tout_rx = ini->ReadInteger(L"PORT",L"ReadTimeOut",5000);
	port->tout_tx = ini->ReadInteger(L"PORT",L"WriteTimeOut",5000);

	last_place_idx = ini->ReadInteger(L"SYSTEM",L"last_place_idx",-1);
	last_drill_idx = ini->ReadInteger(L"SYSTEM",L"last_drill_idx",-1);

	port->pause_transact = ini->ReadInteger(L"PORT",L"PauseTransact",10);
	port->pause_reopen = ini->ReadInteger(L"PORT",L"PauseReopen",5000);
	port->baud = (EBaudrate)ini->ReadInteger(L"PORT",L"BaudRate",EBaud9600);
	port->port = ini->ReadInteger(L"PORT",L"Port",1);
	port->mark = ini->ReadString(L"PORT",L"Mark",L"Порт инклинометра");

	sensor->addr = ini->ReadInteger(L"SENSOR",L"Addr",1);
	sensor->mark = ini->ReadString(L"SENSOR",L"Mark",L"Скважинный инклинометр");
	sensor->used_protocol = ini->ReadInteger(L"SENSOR",L"Protocol",1);

	i_use_side_keyboard = ini->ReadInteger(L"SYSTEM",L"SideVirtKbd",1);

	WideString section(L"");
	WideString spar(L"");
	int ipar = 0;

	for (int i = 0; i < SYSTEM_PLACES_MAX; i++) {

		section.printf(L"PLACE%d",i+1);
		spar = ini->ReadString(section, "NAME", "");

		if (spar != L"") {

			this->AddPlace(spar);
			place_list[place_list_idx-1]->LoadDrillConfig(ini);

		}
		else
		{
			break;
        }

	}

	Redraw();

	global_base_convert = false;
}

void TGBISystem::Start(TEdit* ex, TEdit* ey)
{
	//if (this->port.IsOpen() == false) {

		/*
		if (port.Open() != 0) {

			utils_ShowMessage(L"Не удалось открыть порт!");
			return;
		}
		*/
	//}

	run = true;
	edit_meas_X = ex;
	edit_meas_Y = ey;
}

void TGBISystem::Stop(void)
{
	run = false;
}

double xx = 100;
double yy = 200;

int TGBISystem::RunProc(void)
{

	if (run != true) {

		return  -1;
	}

	if (this->port.IsOpen() == false)
	{

		try{


			if (this->port.OpenComPort(port.port, port.baud) !=0)
			{
				this->edit_meas_X->Font->Color = clGray;
				this->edit_meas_Y->Font->Color = clGray;

				this->edit_meas_X->Text = L"ОШИБКА ПОРТА";
				this->edit_meas_Y->Text = L"ОШИБКА ПОРТА";

				return  -2;
			}
		}
		catch (...)
		{
			utils_ShowMessage(L"Выбранный порт не доступен!");
        }
	}


	TSensor* sensor = GetSensor();

	if (sensor->GetMeasResult() == 0)
	{
		WideString s;

		//sensor->curr_X = xx;
		//sensor->curr_Y = yy;

		COLORREF c = RGB(0,255,0);

		if (sensor->sko_X<(sko_limit/100.)) {

			this->edit_meas_X->Font->Color = clLime;//(TColor)RGB(0,150,0);//clLime;
		}
		else
		{
			this->edit_meas_X->Font->Color = clRed;
		}

		if (sensor->sko_Y<(sko_limit/100.)) {

			this->edit_meas_Y->Font->Color = clLime;
		}
		else
		{
			this->edit_meas_Y->Font->Color = clRed;
		}

		if (sensor->curr_X>=0)  s.printf(L" +%.1f (%.1f)",sensor->curr_X, sensor->sko_X);
		else  					s.printf(L" %.1f (%.1f)",sensor->curr_X, sensor->sko_X);
		this->edit_meas_X->Text = s;

		if (sensor->curr_Y>=0)  s.printf(L" +%.1f (%.1f)",sensor->curr_Y, sensor->sko_Y);
		else  					s.printf(L" %.1f (%.1f)",sensor->curr_Y, sensor->sko_Y);
		this->edit_meas_Y->Text = s;
	}
	else
	{
		this->edit_meas_X->Font->Color = clGray;
		this->edit_meas_Y->Font->Color = clGray;

		this->edit_meas_X->Text = L"ОШИБКА СВЯЗИ";
		this->edit_meas_Y->Text = L"ОШИБКА СВЯЗИ";
	}


	xx+= 0.001;
	yy+= 0.001;

	return 0;
}

bool TGBISystem::IsRunning (void)
{
	return run;
}

int TGBISystem::Redraw (void)
{

/*
Пересчет всеx индексов элементов системы
*/

	Reindex();

	if (tree == NULL) {

		return -1;
	}


	tree->Visible = false;

	tree->Items->Clear();
    tree->ReadOnly = true;

/*
Вершина с именем системы
*/

		WideString s(L"");
		TTreeNode* n = NULL;

		s.printf(L"Система [%s]", name.c_bstr());
		n = this->tree->Items->Add(NULL, s);
		this->node = n;

		utils_set_tree_node_view(node, SYSTEM_NODE_SYSTEM, SYSTEM_NODE_STATE_NORMAL);

		n = this->port.Redraw(tree,node);

        n = this->sensor.Redraw(tree, n);

		node->Expand(true);


		for (int i = 0; i < place_list_idx; i++) {

			if (place_list[i] == NULL) {

				break;

			}

			place_list[i]->Redraw(tree,node);

		}

    tree->Visible = true;

	return 0;
}

int TGBISystem::CheckTreeItemSelected(int* type, int* idx, void** obj)
{
	TTreeNode* n = NULL;
	n = tree->Selected;
	*obj = NULL;

	if (n == this->node) {

		*type = TREE_ITEM_TYPE_SYSTEM;
		*idx = 0;

		*obj = this;
		return 0;
	}


	if (n == this->port.GetNode()) {

		*type = TREE_ITEM_TYPE_PORT;
		*idx = 0;

		*obj = &this->port;
		return 0;
	}


	if (n == this->sensor.GetNode()) {

		*type = TREE_ITEM_TYPE_SENSOR;
		*idx = 0;

		*obj = &this->sensor;
		return 0;
	}


	for (int i = 0; i < place_list_idx; i++) {

		if (n == this->place_list[i]->GetNode()) {

			*type = TREE_ITEM_TYPE_PLACE;
			*idx = i;

			*obj = this->place_list[i];
			return 0;
		}

		for (int j = 0; j < place_list[i]->drill_list_idx ; j++) {

			if (n == this->place_list[i]->drill_list[j]->node) {

				*type = TREE_ITEM_TYPE_DRILL;
				*idx = j;
				*obj = this->place_list[i]->drill_list[j];

				return 0;
			}

			for (int k = 0; k < place_list[i]->drill_list[j]->meas_list_idx ; k++) {

				if (n == this->place_list[i]->drill_list[j]->meas_list[k]->node) {

					*type = TREE_ITEM_TYPE_MEAS;
					*idx = k;
					*obj = this->place_list[i]->drill_list[j]->meas_list[k];

					return 0;
				}

            }

		}

	}


	*type = -1;
	*idx = -1;

	return -1;
}

int TGBISystem::AddPlace(WideString name)
{
	if (place_list_idx>=SYSTEM_PLACES_MAX) {

		utils_ShowMessage(L"Список переполнен!");
		return -1;
	}


	for (int i=0; i < place_list_idx; i++) {

		if (place_list[i]->GetName() == name) {

			utils_ShowMessage(L"Данное имя уже существует в системе!");
			return -2;
		}

	}


   TPlace* p = new TPlace(name);
   this->place_list[place_list_idx] = p;
   place_list_idx++;
   p->num = place_list_idx;
   this->Redraw();

   return 0;
}

int TGBISystem::DeletePlace(TPlace* p, int idx)
{

  for (int i = 0; i < place_list_idx; i++)
  {

	if (i == idx) {

		if (p!=place_list[idx]) {

			return -1; //Ошибка элемента системы
		}

		delete place_list[idx];

		for (int i = idx+1; i < place_list_idx; i++) {

			place_list[i-1]=place_list[i];
			place_list[i-1]->num--;

			TPlace* p = place_list[i-1];

				for (int j = 0; j < p->drill_list_idx; j++) {

					p->drill_list[j]->pnum--;
				}
		}

		place_list_idx--;

		this->Redraw();

	}

  }

  return 0;
}

int TGBISystem::Reindex(void)
{

	int pndex = 0;
	int dndex = 0;
	int index = 0;

	TPlace* p = NULL;
	TDrill* d = NULL;
	TMeas* m = NULL;


	for (int i = 0; i < place_list_idx; i++) {

		p = place_list[i];
		pndex = i+1;
		p->num = pndex;

		for (int j = 0; j < p->drill_list_idx; j++) {

			d = p->drill_list[j];
			dndex = j+1;
			d->num = dndex;
			d->pnum = pndex;

			for (int k = 0; k < d->meas_list_idx; k++) {

				m = d->meas_list[k];
				index = k+1;
				m->num = index;
				m->pnum = pndex;
				m->dnum = dndex;

				m->name.printf(L"Измерение_%d", index);
				m->name_drill = d->name;
				m->name_place = p->GetName();
				m->type_drill = d->drill_orient;
				m->single_way = d->single_way;
                m->drill_start_point = d->start_point;
			}

		}

	}


	return 0;
}

void TGBISystem::ViewSKOlimit()
{
	if (edit_SKO == NULL) {

		return;
	}


	WideString s(L"");
	s.printf(L"%.2f", sko_limit/100.);
	edit_SKO->Text = s;


}

bool TGBISystem::DeleteDir(WideString DirName)
{
	TSearchRec sr;
	if (DirName.Length())
	{
		 if (!FindFirst(DirName+"\\*.*",faAnyFile,sr))
		 {
			 do
			  {
				  if (!(sr.Name=="." || sr.Name==".."))// это удалять не надо
				  {
					   if (((sr.Attr & faDirectory) == faDirectory ) ||   (sr.Attr == faDirectory))// найдена папка
					   {
							FileSetAttr(DirName+""+sr.Name, faDirectory );// сброс всяких read-only
							DeleteDir(DirName+""+sr.Name);//рекурсивно удаляем содержимое
							RemoveDir(DirName + ""+sr.Name);// удаляем теперь уже пустую папку
					   }
					   else// иначе найден файл
					   {
							FileSetAttr(DirName+""+sr.Name, 0);// сброс всяких read-only
							DeleteFile(DirName+""+sr.Name);// удаляем файл
					   }
				  }
			  }
			 while (!FindNext(sr));// ищем опять, пока не найдем все
		 }
		 FindClose(sr);
	 }

	RemoveDir(DirName);

return true;
}

int TGBISystem::ResaveData()
{
	TPlace* p = NULL;
	TDrill* d = NULL;
	TMeas* m = NULL;


	for (int i = 0; i < place_list_idx; i++) {

		p = place_list[i];

		for (int j = 0; j < p->drill_list_idx; j++) {

			d = p->drill_list[j];

			for (int k = 0; k < d->meas_list_idx; k++) {

				m = d->meas_list[k];
				m->SaveData(0);

			}

		}

	}

	return 0;
}

int TGBISystem::KillBase()
{

	TPlace* p = NULL;
	TDrill* d = NULL;
	TMeas* m = NULL;

	TCHAR dir[1024];

	wcscpy(dir, SysConfMgr.GetCurBase());

	TCHAR pdir[1024];
	TCHAR ddir[1024];
	TCHAR mdir[1024];

	for (int i = 0; i < place_list_idx; i++) {

		p = place_list[i];
		wcscpy(pdir,dir);
		wcscat(pdir,p->GetName().c_bstr());
		wcscat(pdir,L"\\");

		for (int j = 0; j < p->drill_list_idx; j++) {

			d = p->drill_list[j];
			wcscpy(ddir,pdir);
			wcscat(ddir,d->name.c_bstr());
			wcscat(ddir,L"\\");

			for (int k = 0; k < d->meas_list_idx; k++) {

				m = d->meas_list[k];
				wcscpy(mdir,ddir);
				wcscat(mdir,m->name.c_bstr());
				wcscat(mdir,L"\\");
				this->DeleteDir(mdir);
			}

			this->DeleteDir(ddir);
		}

			this->DeleteDir(pdir);
	}

	this->DeleteDir(dir);

	return 0;
}

int TGBISystem::LoadData()
{

	TPlace* p = NULL;
	TDrill* d = NULL;
	TMeas* m = NULL;


	for (int i = 0; i < place_list_idx; i++) {

		p = place_list[i];

		for (int j = 0; j < p->drill_list_idx; j++) {

			d = p->drill_list[j];

			for (int k = 0; k < d->meas_list_idx; k++) {

				m  = d->meas_list[k];
				m->LoadData();
			}
		}

	}


	return 0;
}

int TGBISystem::CreateConf (TSaveDialog* dlg)
{

	this->port.Close();

	this->edit_meas_X->Text = L"";
	this->edit_meas_Y->Text = L"";

	wchar_t fres[1024];
	wchar_t cres[1024];
	
	 dlg->InitialDir = SysConfMgr.GetCurConfFoldPath();
	 dlg->Filter = L"*.ini|*.ini";
	 dlg->FileName = L"NewSystemGBI";
	 dlg->Title = L"Cоздать новую систему";
	 if (dlg->Execute()!=IDOK) return -1;
	 
	 wcscpy(fres, (wchar_t*)dlg->FileName.c_str());

	 

	 wcscpy(cres, (wchar_t*)dlg->FileName.c_str());

	 int i = 0;

	 for (i = wcslen(cres); i >=0 ; i--) {

		if (cres[i] == '\\') break;
	 }

	 TCHAR cnew [1024];
	 wcscpy(cnew, &cres[i+1]);

	 i = 0;

	 for (i = wcslen(cnew); i >=0 ; i--) {

		if (cnew[i] == '.')
		{
			cnew[i] = 0;
			break;
		}
	 }


	 SysConfMgr.Accept(cnew);

	return 0;
}

int TGBISystem::OpenConf (TOpenDialog* dlg)
{
	 this->port.Close();

	 this->edit_meas_X->Text = L"";
	 this->edit_meas_Y->Text = L"";

	 WideString fres(L"");

	 dlg->InitialDir = SysConfMgr.GetCurConfFoldPath();
	 dlg->Filter = L"*.ini|*.ini";
	 
	 wcscpy((TCHAR*)dlg->FileName.data(), SysConfMgr.cur_conf_name);

	 dlg->FileName = L"Пока не работает!";

	 dlg->Title = L"Открыть конфигурацию";
	 if (dlg->Execute()!=IDOK) return -1;

	 fres = dlg->FileName;

	 TCHAR cres[1024];
	 wcscpy(cres,fres.c_bstr());

	 int i = 0;

	 for (i = wcslen(cres); i >=0 ; i--) {

		if (cres[i] == '\\') break;
	 }

	 TCHAR cnew [1024];
	 wcscpy(cnew, &cres[i+1]);

	 i = 0;

	 for (i = wcslen(cnew); i >=0 ; i--) {

		if (cnew[i] == '.')
		{
			cnew[i] = '\0';
			break;
		}
	 }

	 SysConfMgr.Accept(cnew);


	return 0;
}


int TGBISystem::SaveConf (TSaveDialog* dlg)
{
     this->port.Close();

	 this->edit_meas_X->Text = L"";
	 this->edit_meas_Y->Text = L"";

	 WideString fres(L"");
	 int i = 0;

	 dlg->InitialDir = SysConfMgr.GetCurConfFoldPath();
	 dlg->Filter = L"*.ini|*.ini";
	 
	 wcscpy((TCHAR*)dlg->FileName.data(), SysConfMgr.cur_conf_name);

	 dlg->FileName = L"Пока не работает!";
	 
	 dlg->Title = L"Сохранить конфигурацию как ...";
	 if (dlg->Execute()!=IDOK) return -1;

	 fres = dlg->FileName;
	 TCHAR cftmp[1024];
	 
	 wcscpy(cftmp,fres.c_bstr());

	 for (i = wcslen(cftmp); i>=0; i--)
	 {
		 if (cftmp[i] == '.')
		 {
			 cftmp[i] = '\0';
			 break;
		 }
	 }

	 wcscat(cftmp,L".ini");

	 FILE* ftmp = NULL;

	 ftmp = _wfopen(cftmp,L"rb");

	 if (ftmp != NULL) {

		fclose(ftmp);
		Application->MessageBoxW(L"Данная конфигурация уже существует!",L"ВНИМАНИЕ!",0);
		return -1;
	 }


	 TCHAR cres[1024];
	 
	 wcscpy(cres,fres.c_bstr());



	 for (i = wcslen(cres); i >=0 ; i--) {

		if (cres[i] == '\\') break;
	 }

	 TCHAR cnew [1024];
	 wcscpy(cnew, &cres[i+1]);

	 i = 0;

	 for (i = wcslen(cnew); i >=0 ; i--) {

		if (cnew[i] == '.')
		{
			cnew[i] = '\0';
			break;
		}
	 }


	 TCHAR cmd[1024];

	 wcscpy (cmd, L"copy \"");

	 wcscat(cmd,SysConfMgr.GetCurIniPath());

	 wcscat(cmd,L"\" ");

	 TCHAR cpar[1024];
	 wcscpy(cpar,L"\"");
	 wcscat(cpar,SysConfMgr.GetCurIniPath());

	 for (i = wcslen(cpar); i >=0 ; i--) {

		if (cpar[i] == '\\')
		{
			cpar[i+1] = '\0';
			break;
		}
	 }

	 wcscat(cpar,cnew);
	 wcscat(cpar,L".ini");
	 wcscat(cmd,cpar);
	 wcscat(cmd,L"\"");

	 system((char*)cmd);


	 wcscpy (cmd, L"xcopy /s /i \"");
	 
	 wcscat(cmd, SysConfMgr.cur_base_path);
	 
	 cmd[wcslen(cmd)-1] = '\0';
	 
	 wcscat (cmd,L"\" ");

	 wcscpy(cpar,L"\"");
	 wcscat(cpar,SysConfMgr.GetCurBaseFoldPath());

	 for (i = wcslen(cpar)-1; i >=0 ; i--) {

		if (cpar[i] == '\\')
		{
			cpar[i+1] = '\0';
			break;
		}
	 }

	 wcscat(cpar,cnew);
	 wcscat(cpar,L"\"");
	 wcscat(cmd,cpar);
	 
	 system((char*)cmd);
	 
	 SysConfMgr.Accept(cnew);

	return 0;
}


int TGBISystem::Clear (void)
{
	TPlace* p = NULL;
	TDrill* d = NULL;
	TMeas* m = NULL;

	for (int i = 0; i < place_list_idx; i++) {

		p = place_list[i];

		for (int j = 0; j < p->drill_list_idx; j++) {

			d = p->drill_list[j];

			for (int k = 0; k < d->meas_list_idx; k++) {

				m = d->meas_list[k];
				delete m;
			}

			delete d;

		}

		delete p;

	}

	place_list_idx = 0;
	LoadSysConf();

	return 0;
}


void TGBISystem::Collapse(void)
{

	 TPlace* place = NULL;
	 TDrill* drill = NULL;

	 for (int i = place_list_idx - 1 ; i>=0; i--)
	 {
		  place = place_list[i];

		   for (int j = 0; j < place->drill_list_idx; j++) {

				   //drill = place->drill_list [j];
				   //drill-> node_folder_sens->Collapse(true);
				   //drill-> node_folder_meas->Collapse(true);

				   //Sleep(100) ;



				   //Sleep(100);

				   //drill->node->Collapse(true);

				   //Sleep(100);

		   }

		   place->node->Collapse(true);

		   //Sleep(100);
	 }

	 //if (tt_gobal_sens_node != NULL) {
	 //
	 //	 tt_gobal_sens_node->Collapse(true);
	 //}
}

TMeas* TGBISystem::GetMeasByNode(TTreeNode *node)
{
	TMeas* res = NULL;
	TMeas* meas = NULL;
	TPlace* place = NULL;
	TDrill* drill = NULL;

	for (int i = 0; i < this->place_list_idx; i++)
	{
		place = this->place_list[i];
		for (int j = 0; j < place->drill_list_idx; j++)
		{
			drill =  place->drill_list[j];
			for (int k = 0; k < drill->meas_list_idx; k++)
			{
				meas = drill->meas_list[k];
				if (meas->node == node)
				{
					res = meas;
					break;
				}
			}

		}
	}

	return res;
}


