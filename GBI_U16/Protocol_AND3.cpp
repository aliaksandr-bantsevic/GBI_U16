//---------------------------------------------------------------------------

#pragma hdrstop

#include "Protocol_AND3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


TProtocol_AND3::TProtocol_AND3()
{

}

TProtocol_AND3::~TProtocol_AND3()
{

}

int  TProtocol_AND3::RequestMeasureResult(unsigned char addr, unsigned char* buf, int* len)
{

	int idx = 0;

	buf[idx] = addr; idx++;
	buf[idx] = AND3_CMD_GETALL; idx++;
	buf[idx] = AND3_DAT1_GETALL; idx++;
	buf[idx] = AND3_DAT2_GETALL; idx++;

	*((WORD*)(buf+2+2))=CRC16CCITT(2+2,buf);

	*len = AND3_LEN_CMD;

	return 0;
}


int TProtocol_AND3::CheckPacket(unsigned char addr, unsigned char* buf, int* len)
{
	if (buf[0] != addr) return -1; //wrong address

	if(*((WORD*)(buf+2+*len))!=CRC16CCITT((unsigned short)(2+*len),buf)) return -2; //wrong crc

	return 0;
}

int TProtocol_AND3::AcceptSensorMeasVal(BYTE* buf,double* x, double* y, BYTE* unitx, BYTE* unity)
{
	and3_res_float* res;
	res = (and3_res_float*) (buf+2) ;

	 if (res->sw.fdr)
	 {
		  *x= (double) res->X;
		  *y= (double) res->Y;
	 }

   *unitx = 0;
   *unity = 0;

   return 0;
}

