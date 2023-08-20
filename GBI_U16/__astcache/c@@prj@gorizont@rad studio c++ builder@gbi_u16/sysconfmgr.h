//---------------------------------------------------------------------------

#ifndef SysConfMgrH
#define SysConfMgrH
//---------------------------------------------------------------------------

#include "defs.h"
#include "utils.h"

class TSysConfMgr {

public:

   TSysConfMgr();
   ~TSysConfMgr();

   TIniFile * ini;

   TCHAR cur_conf_path[1024];
   TCHAR cur_base_path[1024];
   TCHAR cur_conf_name[1024];
   TCHAR cur_conf_fold_path[1024];
   TCHAR cur_base_fold_path[1024];
   TCHAR cur_back_fold_path[1024];

   TIniFile* GetIniFile(void);
   void GetCurConf(void);
   TCHAR* GetCurBase(void);
   void SaveCurConf(void);
   TCHAR* GetCurIniPath(void);
   TCHAR* GetCurConfFoldPath(void);
   TCHAR* GetCurBaseFoldPath(void);
   TCHAR* GetCurBackFoldPath(void);
   int Accept(TCHAR* cnew);
   int Backup(int autobackup, int showmsg);
   double GetBckTime (void);

   double backup_limit;

   int AutoBackup(void);

   bool auto_backup_flag;
   bool auto_backup_flag_completed;
   int isGcfTxtUTF8(TCHAR* path);
   int isIniTxtUTF8(TCHAR* path);
};












#endif
