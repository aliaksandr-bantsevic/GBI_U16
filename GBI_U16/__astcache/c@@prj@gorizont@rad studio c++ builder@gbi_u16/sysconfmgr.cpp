//---------------------------------------------------------------------------

#pragma hdrstop

#include "SysConfMgr.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


   TSysConfMgr::TSysConfMgr()
   {
		ini = new TIniFile(ChangeFileExt(Application->ExeName,".gcf"));
		strcpy(cur_conf_path,"");
		strcpy(cur_base_path,"");
		strcpy(cur_conf_fold_path,"");
		backup_limit = 1.0;
		auto_backup_flag = false;
		auto_backup_flag_completed = false;
   }

   TSysConfMgr::~TSysConfMgr()
   {

   }

   TIniFile* TSysConfMgr::GetIniFile(void)
   {
		GetCurConf();
		return ini;
   }

   void TSysConfMgr::GetCurConf(void)
   {

		strcpy(cur_conf_path,"");
		strcpy(cur_base_path,"");
		strcpy(cur_conf_fold_path,"");

		TIniFile *inigcf = new TIniFile(ChangeFileExt(Application->ExeName,".gcf"));

		AnsiString sname("");
		sname = inigcf ->ReadString("GENERAL","CONFNAME","GBI");
		strcpy(cur_conf_name,sname.c_str());
		sname = sname + ".ini";

		backup_limit = (double) inigcf ->ReadInteger("BACKUP","PERIOD",7.0);

		::GetCurrentDirectory(1024,cur_conf_path);
		::GetCurrentDirectory(1024,cur_base_path);
		::GetCurrentDirectory(1024,cur_back_fold_path);

		strcat(cur_conf_path,"\\Config\\");
		if (!DirectoryExists(cur_conf_path))  CreateDirectory(cur_conf_path,0);
		strcpy(cur_conf_fold_path,cur_conf_path);

		strcat(cur_back_fold_path,"\\Backup\\");
		if (!DirectoryExists(cur_back_fold_path))  CreateDirectory(cur_back_fold_path,0);

		strcat(cur_base_path,"\\Base\\");
		if (!DirectoryExists(cur_base_path))  CreateDirectory(cur_base_path,0);
		strcpy(cur_base_fold_path,cur_base_path);
		strcat(cur_base_path,cur_conf_name);
		strcat(cur_base_path,"\\");
		if (!DirectoryExists(cur_base_path))  CreateDirectory(cur_base_path,0);


		strcat(cur_conf_path,sname.c_str());

		if (ini != NULL) delete ini;

		ini = new TIniFile (cur_conf_path);

		AutoBackup();
   }

   char* TSysConfMgr::GetCurBase(void)
   {
		return cur_base_path;
   }

   char* TSysConfMgr::GetCurIniPath(void)
   {
		return cur_conf_path;
   }

   char* TSysConfMgr::GetCurConfFoldPath(void)
   {
		return cur_conf_fold_path;
   }

   char* TSysConfMgr::GetCurBaseFoldPath(void)
   {
		return cur_base_fold_path;
   }

   char* TSysConfMgr::GetCurBackFoldPath(void)
   {
		return cur_back_fold_path;
   }

   void TSysConfMgr::SaveCurConf(void)
   {
		TIniFile *inigcf = new TIniFile(ChangeFileExt(Application->ExeName,".gcf"));
		inigcf ->WriteString("GENERAL","CONFNAME",cur_conf_name);

		inigcf ->WriteInteger("BACKUP","PERIOD",(int)backup_limit);
   }

   int TSysConfMgr::Accept(char* cnew)
   {
		strcpy(cur_conf_name,cnew);
		SaveCurConf();
		return 0;
   }


   int TSysConfMgr::AutoBackup(void)
   {
		if (auto_backup_flag == true ) {

			return -1;
		}

		Backup(1,0);

		auto_backup_flag = true;
		return 0;
   }

   int TSysConfMgr::Backup(int autobackup, int showmsg)
   {

		if (autobackup != 0)
		{
			if (backup_limit >= 1.0)
			{
				if (backup_limit > GetBckTime()) {

					return -1; //Ïåðèîä ðåçåðâèðîâàíèÿ íå èñòåê
				}
			}
			else
			{
					return -2; //Àâòî áýêàï îòêëþ÷åí
            }

		}


		TDateTime t = Now();
		char cdir[1024];
		GetCurrentDirectory(1024,cdir);
		AnsiString sdir("");
		sdir = sdir + cdir;

		AnsiString sgini = ChangeFileExt(Application->ExeName,".gcf");
		AnsiString sapp = sdir;
		AnsiString sconf = sdir+"\\Config";
		AnsiString sbase = sdir+"\\Base";
		AnsiString sback = sdir+"\\Backup\\";

		//AnsiString sfold = FormatDateTime("dd_mm_yyyy_hh_nn_ss\\",t);
		AnsiString sfold = FormatDateTime("yyyy_mm_dd_hh_nn_ss\\",t);

		sback = sback + sfold;
		if (!DirectoryExists(sback.c_str()))  CreateDirectory(sback.c_str(),0);

		AnsiString cmd("copy ");
		cmd.printf ("copy \"%s\" \"%sGBI.gcf\"",sgini.c_str(),sback.c_str());
		system(cmd.c_str());
		//ShellExecute(0,"open",cmd.c_str(),0,0,SW_HIDE);

		cmd.printf ("xcopy /s /i \"%s\" \"%sBase\"",sbase.c_str(),sback.c_str());
		system(cmd.c_str());
		//ShellExecute(0,"open",cmd.c_str(),0,0,SW_HIDE);

		cmd.printf ("xcopy /s /i \"%s\" \"%sConfig\"",sconf.c_str(),sback.c_str());

		system(cmd.c_str());
		//ShellExecute(0,"open",cmd.c_str(),0,0,SW_HIDE);

		if (autobackup == 0)
		{
			AnsiString msg("");
			sfold[strlen(sfold.c_str())] = '\0';
			msg.printf("Ðåçåðâíàÿ êîïèÿ áàçû ñîõðàíåíà â ïàïêå ../Backup/%s",sfold.c_str());
			if (showmsg) MessageBox(NULL,msg.c_str(),"ÐÅÇÅÐÂÍÎÅ ÊÎÏÈÐÎÂÀÍÈÅ",0);
		}
		else
		{
			//ShowMessage("Auto backup!");
			auto_backup_flag_completed = true;
        }

		return 0;
   }


#define T_ONE_DAY       (1.)
#define T_ONE_HOUR      (1./24.)
#define T_ONE_MIN       (1./(24.*60.))
#define T_ONE_SEC       (1./(24.*60.*60.))
#define T_ONE_MSEC      ((1./(24.*60.*60.))/1000)
#define T_ONE_DSEC      ((1./(24.*60.*60.))/10)

//Ñêîëüêî äíåé ïðîøëî ïîñå ïîñëåäíåãî áýêàïà
   double TSysConfMgr::GetBckTime (void)
   {

		double dayage = 0.0;

//Ñþäà áóäåì ÷èòàòü àòðèáóòû ïàïêè
		WIN32_FIND_DATA FileDataAtr;

		AnsiString fpath("");
		int idx=0;
		LONGLONG T = 0;
		LONGLONG Tmax = 0;

//Õýíäë äëÿ ïîèñêà ôàéëîâ â ïàïêå
		WIN32_FIND_DATA w32fd;
		HANDLE hFind;

//Ïóòü ê ïàïêå ñ ôàéëàìè
		char dbpath [1024];
		strcpy(dbpath,GetCurBackFoldPath());

//Ìàñêà
		char cpar[1024];
		sprintf(cpar,"*.*");
		strcat(dbpath,cpar);

//×èòàåì ïåðâûé ôàéë â ïàïêå
		hFind=FindFirstFile(dbpath,&w32fd);

		SYSTEMTIME sysTime;
		FILETIME creationTime;
		FILETIME localfiletime;

//Â ïàïêå íåò ôàéëîâ
		if ((hFind==INVALID_HANDLE_VALUE)||(hFind==NULL))
		{
			return 0.0;
		}
//Åñëè ôàéëû åñòü ÷èòàåì âåñü äèðåêòîðèé
		else
		{
				  FileDataAtr = w32fd;
				  T=FileDataAtr.ftCreationTime.dwHighDateTime;
				  T<<=4;
				  T+=FileDataAtr.ftCreationTime.dwLowDateTime;

				  int lh = sizeof(FileDataAtr.ftCreationTime.dwHighDateTime);
				  int ll = sizeof(FileDataAtr.ftCreationTime.dwLowDateTime);

				  if (T>Tmax)
				  {
					Tmax = T;
					creationTime = FileDataAtr.ftCreationTime;
				  }

					while(FindNextFile( hFind, &w32fd))
					{
						  FileDataAtr = w32fd;
						  T=FileDataAtr.ftCreationTime.dwHighDateTime;
						  T<<=4;
						  T+=FileDataAtr.ftCreationTime.dwLowDateTime;

						  if (T>Tmax)
						  {
							Tmax = T;
                            creationTime = FileDataAtr.ftCreationTime;
						  }

					}

					/*
			//GetFileTime(hFind, &creationTime, 0, 0);
			creationTime = FileDataAtr.ftCreationTime;
			FileTimeToLocalFileTime(&creationTime,&localfiletime);
			FileTimeToSystemTime(&localfiletime, &sysTime);

			unsigned short year, mon, day, hour, min, sec, msec = 0;

			year = sysTime.wYear; mon = sysTime.wMonth; day = sysTime.wDay;
			hour = sysTime.wHour; min = sysTime.wMinute; sec = sysTime.wSecond; msec = sysTime.wMilliseconds;
			TDateTime ct = TDateTime(year,mon,day) + TDateTime(hour,min,sec,msec);
			TDateTime age = Now() - ct;
			dayage = (double)age;

			//dayage/=T_ONE_DAY;

			dayage/=T_ONE_MIN;
					*/
		}

			//GetFileTime(hFind, &creationTime, 0, 0);
			creationTime = FileDataAtr.ftCreationTime;
			FileTimeToLocalFileTime(&creationTime,&localfiletime);
			FileTimeToSystemTime(&localfiletime, &sysTime);

			unsigned short year, mon, day, hour, min, sec, msec = 0;

			year = sysTime.wYear; mon = sysTime.wMonth; day = sysTime.wDay;
			hour = sysTime.wHour; min = sysTime.wMinute; sec = sysTime.wSecond; msec = sysTime.wMilliseconds;
			TDateTime ct = TDateTime(year,mon,day) + TDateTime(hour,min,sec,msec);
			TDateTime age = Now() - ct;
			dayage = (double)age;

			dayage/=T_ONE_DAY;
			//dayage/=T_ONE_MIN;


	return dayage;
}


