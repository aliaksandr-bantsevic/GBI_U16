//---------------------------------------------------------------------------

#pragma hdrstop

#include "Sensor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

	TSensor::TSensor(void)
	{
		addr = 1;
		curr_X = 0;
		curr_Y = 0;
		protocol_211 = new TProtocol_211();
		protocol_AND3 = new TProtocol_AND3();
		serial = 0;
		on = false;
		mark = L"Глубинный инклинометр";
		port = NULL;
		serial = 0;
		soft_version = 0;

		hist_x_idx = 0;
		memset(hist_x,0,sizeof(hist_x));
		sko_X = 0;

		hist_y_idx = 0;
		memset(hist_y,0,sizeof(hist_y));
		sko_Y = 0;

		node = NULL;

		//used_protocol = USED_PROTOCOL_211;
		used_protocol = USED_PROTOCOL_AND3;
	}

	TSensor::~TSensor(void)
	{
		delete protocol_211;
	}


	int TSensor::Run(void)
	{
		if (on) {

			if (serial ==0) {

			}
			else
			{


			}

			return 0;
		}

		return -1;
	}

	void TSensor::SetChan(TChannel* c)
	{
		 port = c;
	}

	void TSensor::SetAddr(BYTE a)
	{
		 addr = a;
	}


//------------------Communication requests----------------------------------

int TSensor::GetMeasResult(void)
{
	if (port == NULL) {

		return -1; //port is not initialized
	}

	if (port->IsOpen() == false) {

		return -2; //port is not ready
	}


	TProtocol_211* p211 =  protocol_211;
	TProtocol_AND3* pand3 =  protocol_AND3;

	int lentx, lenrx = 0;
	int res = 0;

	if (used_protocol == USED_PROTOCOL_211)
	{
		p211->RequestMeasureResult(addr,buftx,&lentx);
	}

	if (used_protocol == USED_PROTOCOL_AND3)
	{
		pand3->RequestMeasureResult(addr,buftx,&lentx);
	}

	lenrx = 12; //expect 12 symbols+ for this request
	res = port->Transact(buftx,bufrx,&lentx,&lenrx);

	if (res!=0) {

		return res; //transact fail
	}

	if (used_protocol == USED_PROTOCOL_211)
	{
		res = p211->CheckPacket(addr,bufrx,&lenrx);
	}

	if (used_protocol == USED_PROTOCOL_AND3)
	{
		lenrx = AND3_LEN_GETALL;
		res = pand3->CheckPacket(addr,bufrx,&lenrx);
	}

	if (res!=0) {

		return res; //communication error
	}

	if (used_protocol == USED_PROTOCOL_211)
	{
		p211->AcceptSensorMeasVal(bufrx,&curr_X,&curr_Y,&unitx,&unity);
	}

	if (used_protocol == USED_PROTOCOL_AND3)
	{
		pand3->AcceptSensorMeasVal(bufrx,&curr_X,&curr_Y,&unitx,&unity);
	}

	if (unitx) curr_X*=60;
	if (unity) curr_Y*=60;

	calc_sko_X();
	calc_sko_Y();

	return 0;
}


int TSensor::GetSerial(void)
{

	if (port == NULL) {

		return -1; //port is not initialized
	}

	if (port->IsOpen() == false) {

		return -2; //port is not ready
	}

	TProtocol_211* p=protocol_211;
	int lentx, lenrx = 0;
	int res = 0;

	p->RequestSensorMeterSerialNumber(addr, buftx, &lentx);
	lenrx = 5; //expect 12 symbols+ for this request
	res = port->Transact(buftx,bufrx,&lentx,&lenrx);

	if (res!=0) {

		return res; //transact fail
	}

	res = p->CheckPacket(addr,bufrx,&lenrx);

	if (res!=0) {

		return res; //communication error
	}

	p->AcceptSensorSerialNumber(bufrx,&serial);

	return 0;
}

int TSensor::GetSoftVer(void)
{

	if (port == NULL) {

		return -1; //port is not initialized
	}

	if (port->IsOpen() == false) {

		return -2; //port is not ready
	}

	TProtocol_211* p=protocol_211;
	int lentx, lenrx = 0;
	int res = 0;

	p->RequestSensorSoftVersion(addr, buftx, &lentx);
	lenrx = 5;
	res = port->Transact(buftx,bufrx,&lentx,&lenrx);

	if (res!=0) {

		return res; //transact fail
	}

	res = p->CheckPacket(addr,bufrx,&lenrx);

	if (res!=0) {

		return res; //communication error
	}

	p->AcceptSensorSoftVersion(bufrx,&soft_version);

	return 0;
}

int TSensor::calc_sko_X(void)
{

   /*
   if (hist_x_idx > 9) {

	hist_x_idx = 0;

   }
   */

//   hist_x[hist_x_idx%10] = curr_X; hist_x_idx++;

	for (int i = 9; i > 0; i--) {

		hist_x[i] = hist_x[i-1];
	}

	hist_x[0] = curr_X;

   double mid = 0;

   for (int i = 0; i<10; i++) {

	mid+= hist_x[i];

   }

   mid/= 10;

   double smid = 0;

	for (int i = 0; i<10; i++) {

	smid+= (hist_x[i]-mid)*(hist_x[i]-mid);

   }

   smid/=10;

   sko_X=Sqrt(smid);

   return 0;
}


int TSensor::calc_sko_Y(void)
{
   /*
   if (hist_y_idx > 9) {

	hist_y_idx = 0;

   }
   */


  //hist_y[hist_y_idx%10] = curr_Y; hist_y_idx++;

  	for (int i = 9; i > 0; i--) {

		hist_y[i] = hist_y[i-1];
	}

	hist_y[0] = curr_Y;

   double mid = 0;

   for (int i = 0; i<10; i++) {

	mid+= hist_y[i];

   }

   mid/= 10;

   double smid = 0;

	for (int i = 0; i<10; i++) {

	smid+= (hist_y[i]-mid)*(hist_y[i]-mid);

   }

   smid/=10;

   sko_Y=Sqrt(smid);

   return 0;
}


TTreeNode* TSensor::Redraw(TTreeView* t, TTreeNode* n)
{
	if (n == NULL) {

		return NULL;
	}

	WideString s("");

	s.printf(L"BIN-D3 [%d][%s]", this->addr, mark.c_bstr());

	node  =	t->Items->AddChild(n,s);
	utils_set_tree_node_view(node, SYSTEM_NODE_SENSOR, SYSTEM_NODE_STATE_NORMAL);

	return node;
}

TTreeNode* TSensor::GetNode()
{
	return node;
}



//--------------------------------------------------------------------------
