﻿//---------------------------------------------------------------------------

#ifndef ChannelH
#define ChannelH
//---------------------------------------------------------------------------

#include "defs.h"
#include "Serial.h"
#include <System.Win.ScktComp.hpp>
#include "utils.h"

typedef enum {

CHAN_TYPE_UNDEF,
CHAN_TYPE_COM_PORT,
CHAN_TYPE_TCP_SERVER,
CHAN_TYPE_TCP_CLIENT,
CHAN_TYPE_UDP_SERVER,
CHAN_TYPE_UDP_CLIENT

} channel_type;

typedef struct
{

  bool on;     //Ïîðò âêëþ÷åí â îïðîñ
  bool run;    //Ïðîöåññ îïðîñà íà äàííîì ïîðòó çàïóùåí
  bool res;    //Ðåçóëüòàò òåêóùåé îïåðàöèè
  int cmd;     //Òèï êîìàíäû íà ïîðòó

} channel_state;

class TChannel {

public:

	TChannel();
	~TChannel();

	int OpenComPort(DWORD com_number, EBaudrate baud);
	int Transact(BYTE* tx, BYTE* rx, int* lentx,  int* lenrx);
	int Setup(channel_type t, DWORD c, EBaudrate b);

	DWORD port;
	EBaudrate baud;
	AnsiString mark;

	DWORD   pause_transact;
    DWORD   pause_reopen;
	DWORD   tout_tx;
	DWORD   tout_rx;

private:

	channel_type type;


	TSerial* com;
	TServerSocket* server;
	double TmOpen,TmClose;
	channel_state state;

	bool isopen;
	TTreeNode* node;

public:

   int SetTouts(DWORD rx, DWORD tx);
   int SetPause(DWORD p);
   int Close();
   int Open();
   bool IsOpen();

   TTreeNode* Redraw(TTreeView* t, TTreeNode* n);
   TTreeNode* GetNode();
};


#endif
