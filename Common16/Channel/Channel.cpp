﻿//---------------------------------------------------------------------------

#pragma hdrstop

#include "Channel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


TChannel::TChannel()
{
	com = NULL;
	server = NULL;
	//type = CHAN_TYPE_UNDEF;

    type = CHAN_TYPE_COM_PORT;

	port = 0;

	TmOpen=Now(); TmClose=TmOpen;

	state.on = false;
	state.run = false;
	state.res = false;
	state.cmd = 0;

	isopen = false;

	pause_transact = 10;
	pause_reopen = 5000;

	tout_tx = 5000;
	tout_rx = 5000;

	baud = EBaud9600;
	port = 1;

	mark = L"Порт итклинометра";

	node = NULL;
}


TChannel::~TChannel()
{
	switch(type)
	{
		case CHAN_TYPE_COM_PORT:

			com->Close();
			if (com != NULL) delete com;

		break;

		default:
		break;
	}
}


int TChannel::OpenComPort(DWORD com_number, EBaudrate baud)
{
	if (com_number > 255) {

		return -1; //com port number wrong
	}

	if (com == NULL) com = new TSerial();

	if (com->Open(com_number) == false) {

		return -2; //com port open fall
	}

	if (com->Setup(baud) == false) {

		return -3; //com baud set fall
	}


	this->type = CHAN_TYPE_COM_PORT;
	this->isopen = true;

	return 0;
}


int TChannel::Close()
{

  switch(type)
  {
	  case CHAN_TYPE_COM_PORT:

				if (com != NULL)
				{
					com->Close();
					//delete com;
					//com = NULL;
				}

	  break;

	  default:
	  break;
  }

  Sleep(DbgSleep);

  state.cmd=0;
  state.on=false;
  state.run=false;
  TmClose=Now();
  isopen = false;

  return 0;

}
//---------------------------------------------------------------------------


int TChannel::SetTouts(DWORD rx, DWORD tx)
{
  this->tout_rx = rx;
  this->tout_tx = tx;
  return 0;
}

int TChannel::SetPause(DWORD p)
{
  this->pause_transact = p;
  return 0;
}

int TChannel::Transact(BYTE* tx, BYTE* rx, int* lentx, int* lenrx)
{

	//Read by 1 byte until success
	BYTE b;

	//Read the device answer
	int idx=0;

	if (IsOpen() == false) {

		if (OpenComPort(port, baud) == false) return -3;
		else Sleep(pause_reopen);

	}

	switch (this->type)
	{
	  case CHAN_TYPE_COM_PORT:

		if (com->IsOpen() == false) {

			return -1; //compot is not ready
		}

		//Purge comport
		this->com->PurgeCom();

		//Set comport touts
		this->com->SetTimeouts(tout_rx, tout_tx);

		//Send command buf
		if (this->com->NWrite(*lentx,tx) == false)
		{
			Close();
			return -4;
        }

		//Wait for cmd performing
		Sleep(pause_transact);

		if (*lenrx !=0)
		{
			if (this->com->NRead(*lenrx,rx)) {

				idx+= *lenrx;
			}
			else
			{
				Close();
				return -2; //Device not answer
			}
		}

		if (rx[*lenrx-1]!=0x7E)
		{
			while (com->BytesAvilable())
			{
				com->NRead(1,&b);
				rx[idx] = b;
				idx++;
			}

		}

		*lenrx = idx;

		if (idx == 0) {

			Close();
			return -2; //Device not answer
		}

		return 0;

	  break;


	default:

        Close();
		return -10; //Undefine error

	break;

	}


}

int TChannel::Setup(channel_type t, DWORD c, EBaudrate b)
{
	this->type = t;
	this->port = c;
	this->baud = b;

	return 0;
}

int TChannel::Open()
{
	return this->OpenComPort(this->port, this->baud);
}

bool TChannel::IsOpen()
{
	switch(type)
	{
		case  CHAN_TYPE_COM_PORT:
		  return isopen;
		break;

		default:
			return false;
		break;
	}

	return false;
}

TTreeNode* TChannel::Redraw(TTreeView* t, TTreeNode* n)
{
	if (n == NULL) {

		return NULL;
	}

	WideString s("");

	s.printf(L"COM%d [%s]", port, mark.c_bstr());
	node  =	t->Items->AddChild(n,s);
	utils_set_tree_node_view(node, 4, SYSTEM_NODE_STATE_NORMAL);

	return node;
}

TTreeNode* TChannel::GetNode()
{
	return node;
}
