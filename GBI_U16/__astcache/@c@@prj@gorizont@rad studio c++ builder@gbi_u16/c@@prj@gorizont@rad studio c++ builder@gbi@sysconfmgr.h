//---------------------------------------------------------------------------

#ifndef SysConfMgrH
#define SysConfMgrH
//---------------------------------------------------------------------------

#include "defs.h"

class TSysConfMgr {

public:

   TSysConfMgr();
   ~TSysConfMgr();

   TIniFile * ini;

   char cur_conf_path[1024]; //ïîëíûé ïóòü ê èíè ôàéëó òåêóùåé ñèñòåìû
   char cur_base_path[1024]; //
   char cur_conf_name[1024];
   char cur_conf_fold_path[1024];
   char cur_base_fold_path[1024];
   char cur_back_fold_path[1024];

   TIniFile* GetIniFile(void);
   void GetCurConf(void);
   char* GetCurBase(void);
   void SaveCurConf(void);
   char* GetCurIniPath(void);
   char* GetCurConfFoldPath(void);
   char* GetCurBaseFoldPath(void);
   char* GetCurBackFoldPath(void);
   int Accept(char* cnew);
   int Backup(int autobackup, int showmsg);
   double GetBckTime (void);

   double backup_limit;

   int AutoBackup(void);

   bool auto_backup_flag;
   bool auto_backup_flag_completed;

};












#endif
