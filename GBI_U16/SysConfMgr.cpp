//---------------------------------------------------------------------------

#pragma hdrstop

#include "SysConfMgr.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


   TSysConfMgr::TSysConfMgr()
   {
		 /*
		TCHAR dirini [1024];

		::GetCurrentDirectoryW(1024,dirini);

		wcscat(dirini, L"\\Config");

		CreateDirectoryW(dirini,0);

		wcscat(dirini, L"\\gbi16.ini");

		FILE* ftmp = NULL;
		ftmp = _wfopen(dirini, L"rb");

		if (ftmp == NULL)
		{
		   CreateTextFile_UTF16LEBOM (dirini);
		}

		fclose(ftmp);

		ini = new TIniFile(dirini);

		wcscpy(cur_conf_path,dirini);

		wcscpy(cur_base_path,dirini);
		wcscat(cur_base_path,L"\\BASE");

		wcscpy(cur_conf_fold_path,L"dirini");
		wcscat(cur_base_path,L"\\BASE\\GBI16");

		backup_limit = 1.0;
		auto_backup_flag = false;
		auto_backup_flag_completed = false;   */
   }

   TSysConfMgr::~TSysConfMgr()
   {

   }

   TIniFile* TSysConfMgr::GetIniFile(void)
   {
		GetCurConf();
		return ini;
   }

   extern bool global_base_convert;

   void TSysConfMgr::GetCurConf(void)
   {

        AutoBackup();

		wcscpy(cur_conf_path,L"");
		wcscpy(cur_base_path,L"");
		wcscpy(cur_conf_fold_path,L"");


		TCHAR dirgcf [1024];
		TCHAR dirgcfold [1024];
		TCHAR dirgcfutf8 [1024];

		::GetCurrentDirectoryW(1024, dirgcf);
		::GetCurrentDirectoryW(1024, dirgcfold);
		::GetCurrentDirectoryW(1024, dirgcfutf8);

		wcscat(dirgcf,L"\\gbi16.gcf");
		wcscat(dirgcfold,L"\\gbi.gcf");
		wcscat(dirgcfutf8,L"\\gbi16.gcf.utf8");


		if (isGcfTxtUTF8(dirgcfold) ==0)
		{
			 utils_ShowMessage(L"Файлы конфигурации системы будут преобразованы к новому формату UTF16!");
			 ::RenameFile(dirgcfold,dirgcf);
			 ::DeleteFile(dirgcfutf8);
			 ConvertTextFile_UTF16LEBOM (dirgcf);
		}

		/*
		FILE* ftmp = NULL;
		ftmp = _wfopen(dirgcf,L"rb");

		if (ftmp == NULL)
		{

			CreateTextFile_UTF16LEBOM (dirgcf);

		}

		fclose (ftmp);
		*/

		CreateTextFile_UTF16LEBOM (dirgcf);
		TIniFile *inigcf = new TIniFile(dirgcf);

		WideString sname(L"");
		sname = inigcf ->ReadString(L"GENERAL",L"CONFNAME",L"GBI16");
		wcscpy(cur_conf_name,sname.c_bstr());
		sname = sname + ".ini";

		backup_limit = (double) inigcf ->ReadInteger(L"BACKUP",L"PERIOD",7.0);

		::GetCurrentDirectoryW(1024,cur_conf_path);
		::GetCurrentDirectoryW(1024,cur_base_path);
		::GetCurrentDirectoryW(1024,cur_back_fold_path);

		wcscat(cur_conf_path,L"\\Config\\");
		if (!DirectoryExists(cur_conf_path))  CreateDirectory(cur_conf_path,0);
		wcscpy(cur_conf_fold_path,cur_conf_path);

		wcscat(cur_back_fold_path,L"\\Backup\\");
		if (!DirectoryExists(cur_back_fold_path))  CreateDirectory(cur_back_fold_path,0);

		wcscat(cur_base_path,L"\\Base\\");
		if (!DirectoryExists(cur_base_path))  CreateDirectory(cur_base_path,0);
		wcscpy(cur_base_fold_path,cur_base_path);
		wcscat(cur_base_path,cur_conf_name);
		wcscat(cur_base_path,L"\\");
		if (!DirectoryExists(cur_base_path))  CreateDirectory(cur_base_path,0);


		wcscat(cur_conf_path,sname.c_bstr());

		if (ini != NULL) delete ini;


		/*
		ftmp = _wfopen(cur_conf_path, L"rb");

		if (ftmp == NULL)
		{

			CreateTextFile_UTF16LEBOM (cur_conf_path);
		}

		fclose (ftmp);
		*/




		if (isIniTxtUTF8(cur_conf_path) ==0 )
		{
		   ConvertTextFile_UTF16LEBOM (cur_conf_path);
		   global_base_convert = true;
		}

		CreateTextFile_UTF16LEBOM (cur_conf_path);

		ini = new TIniFile (cur_conf_path);


   }

   TCHAR* TSysConfMgr::GetCurBase(void)
   {
		return cur_base_path;
   }

   TCHAR* TSysConfMgr::GetCurIniPath(void)
   {
		return cur_conf_path;
   }

   TCHAR* TSysConfMgr::GetCurConfFoldPath(void)
   {
		return cur_conf_fold_path;
   }

   TCHAR* TSysConfMgr::GetCurBaseFoldPath(void)
   {
		return cur_base_fold_path;
   }

   TCHAR* TSysConfMgr::GetCurBackFoldPath(void)
   {
		return cur_back_fold_path;
   }

   void TSysConfMgr::SaveCurConf(void)
   {

		TIniFile *inigcf = new TIniFile(ChangeFileExt(Application->ExeName,".gcf"));
		inigcf ->WriteString("GENERAL","CONFNAME",cur_conf_name);

		inigcf ->WriteInteger("BACKUP","PERIOD",(int)backup_limit);
   }

   int TSysConfMgr::Accept(TCHAR* cnew)
   {
		wcscpy(cur_conf_name,cnew);
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

					return -1;
				}
			}
			else
			{
					return -2;
            }

		}


		TDateTime t = Now();
		TCHAR cdir[1024];
		GetCurrentDirectoryW(1024,cdir);
		WideString sdir(L"");
		sdir = sdir + cdir;

		WideString sgini = ChangeFileExt(Application->ExeName,".gcf");
		WideString sapp = sdir;
		WideString sconf = sdir+"\\Config";
		WideString sbase = sdir+"\\Base";
		WideString sback = sdir+"\\Backup\\";

		//WideString sfold = FormatDateTime("dd_mm_yyyy_hh_nn_ss\\",t);
		WideString sfold = FormatDateTime("yyyy_mm_dd_hh_nn_ss\\",t);

		sback = sback + sfold;
		if (!DirectoryExists(sback.c_bstr()))  CreateDirectoryW(sback.c_bstr(),0);

		WideString cmd("copy ");
		cmd.printf (L"copy \"%s\" \"%sGBI16.gcf\"",sgini.c_bstr(),sback.c_bstr());
		system((char*)cmd.c_bstr());
		//ShellExecute(0,"open",cmd.c_str(),0,0,SW_HIDE);

		cmd.printf (L"xcopy /s /i \"%s\" \"%sBase\"",sbase.c_bstr(),sback.c_bstr());
		system((char*)cmd.c_bstr());
		//ShellExecute(0,"open",cmd.c_str(),0,0,SW_HIDE);

		cmd.printf (L"xcopy /s /i \"%s\" \"%sConfig\"",sconf.c_bstr(),sback.c_bstr());

		system((char*)cmd.c_bstr());
		//ShellExecute(0,"open",cmd.c_str(),0,0,SW_HIDE);

		if (autobackup == 0)
		{
			WideString msg(L"");
			sfold[wcslen(sfold.c_bstr())] = '\0';
			msg.printf(L"Резервная копия базы сохранена в папке ../Backup/%s",sfold.c_bstr());
			if (showmsg) MessageBoxW(NULL,msg.c_bstr(),L"РЕЗЕРВНОЕ КОПИРОВАНИЕ",0);
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

		WideString fpath(L"");
		int idx=0;
		LONGLONG T = 0;
		LONGLONG Tmax = 0;

//Õýíäë äëÿ ïîèñêà ôàéëîâ â ïàïêå
		WIN32_FIND_DATA w32fd;
		HANDLE hFind;

//Ïóòü ê ïàïêå ñ ôàéëàìè
		TCHAR dbpath [1024];
		wcscpy(dbpath,GetCurBackFoldPath());

//Ìàñêà
		TCHAR cpar[1024];
		swprintf(cpar,L"*.*");
		wcscat(dbpath,cpar);

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

int TSysConfMgr::isGcfTxtUTF8(TCHAR* path)
{
	FILE* f = _wfopen (path, L"rb");

	if (f == NULL) {

		return -3;
	}

	char buf[10];
	int res = 0;

	if (fread(buf,10,1,f))
	{
		 if (strstr(buf, "[GENERAL]") == 0 )
		 {
			res = -1;
		 }
	}
	else
	{
		res = -2;
	}

	fclose(f);

	return res;
}

int TSysConfMgr::isIniTxtUTF8(TCHAR* path)
{
	FILE* f = _wfopen (path, L"rb");

	if (f == NULL) {

		return -3;
	}

	char buf[10];
	int res = 0;

	if (fread(buf,10,1,f))
	{
		 if (strstr(buf, "[SYSTEM]") == 0 )
		 {
			res = -1;
		 }
	}
	else
	{
		res = -2;
	}

	fclose(f);

	return res;
 }

