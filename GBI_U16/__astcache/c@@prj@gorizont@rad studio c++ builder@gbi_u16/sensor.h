//---------------------------------------------------------------------------

#ifndef SensorH
#define SensorH
//---------------------------------------------------------------------------

#include "defs.h"
#include "Protocol_211.h"
#include "Protocol_AND3.h"
#include "Channel.h"

#define SENSOR_BUFFERS_LEN 1024

#define USED_PROTOCOL_211   0
#define USED_PROTOCOL_AND3  1

class TSensor {

public:


	TSensor();
	TSensor(TChannel* port);
	~TSensor();

	int Run();
	BYTE addr;

	WideString mark;
	void SetChan(TChannel* c);
	void SetAddr(BYTE a);

   	unsigned int serial;
	unsigned int soft_version;

	double curr_X;
	double curr_Y;

	int used_protocol;

private:


	BYTE buftx[SENSOR_BUFFERS_LEN];
	BYTE bufrx[SENSOR_BUFFERS_LEN];

	bool on;

	TProtocol_AND3* protocol_AND3;
	TProtocol_211* protocol_211;
	TChannel* port;

	BYTE unitx;
	BYTE unity;

	void GetGurrentMeas(void);

	double hist_x[10];
	int    hist_x_idx;

	double hist_y[10];
	int    hist_y_idx;

	int calc_sko_X(void);
	int calc_sko_Y(void);

    TTreeNode* node;

public:

	double sko_X;
	double sko_Y;

	int GetMeasResult(void);
	int GetSerial(void);
	int GetSoftVer(void);

	TTreeNode* Redraw(TTreeView* t, TTreeNode* n);
    TTreeNode* GetNode();
};

#endif
