//---------------------------------------------------------------------------

#pragma hdrstop

#include "Protocol_211.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


TProtocol_211::TProtocol_211()
{

}

TProtocol_211::~TProtocol_211()
{

}

int TProtocol_211::EscapeBytesDecode(unsigned char* buf, int* len)
{
		BYTE buft[1024];
		buft[0]=buf[0];
		int idx=1;
		for (int i=1; i<*len-1; i++)
		{
				if (buf[i]!=ESCAPE_BYTE)
				{
						buft[idx]=buf[i];idx++;
				}
				else
				{
						buft[idx]=buf[i+1]^0x20; idx++; i++;
				}
		}

		*len=idx+1;
		buft[idx] = PACKET_END;
		memcpy(buf,buft,*len);
		return 0;
}

int TProtocol_211::EscapeBytesEncode(unsigned char* buf, int* len)
{
		BYTE buft[1024];
		buft[0] = buf[0];
		int idx=1;
		for (int i=1; i<*len-1; i++)
		{
				if ((buf[i]!=PACKET_END)&&(buf[i]!=ESCAPE_BYTE))
				{
						buft[idx]=buf[i];idx++;
				}
				else
				{
						 if (buf[i]==PACKET_END)
						 {
							buft[idx]=ESCAPE_BYTE;idx++;
							buft[idx]=CODE7E_BYTE;idx++;
						 }
						 if (buf[i]==ESCAPE_BYTE)
						 {
							buft[idx]=ESCAPE_BYTE;idx++;
							buft[idx]=CODE7D_BYTE;idx++;
						 }

				}
		}

		buft[idx] = PACKET_END;
		*len=idx+1;
        memcpy(buf,buft,idx);
        return 0;
}

//---------------------------Îñíîâíûå ïàêåòà çàïðîñà-------------------------------------------


//Çàïðîñ ðåçóëüòàòîâ èçìåðåíèÿ îñíîâíîé ïàêåò
void TProtocol_211::RequestMeasureResult(unsigned char addr, unsigned char* buf, int* len)
{

		RequestMainMeterPacket(addr, MEAS_VAL, buf, len);

}

//Çàïðîñèòü âåðñèþ èçìåðèòåëÿ
void TProtocol_211::RequestMeterVerion(unsigned char addr, unsigned char* buf, int* len)
{

	RequestMainMeterPacket(addr, MEAS_VER, buf, len);

}

//---------------------------Äîïîëíèòåëüíûå ïàêåòà çàïðîñà-------------------------------------------
void TProtocol_211::RequestSensorBaudRate(unsigned char addr, unsigned char* buf, int* len)
{
        RequestAddnMeterPacket(addr, GET_BAUD, buf, len);
}

void TProtocol_211::RequestSensorMeterName(unsigned char addr, unsigned char* buf, int* len)
{
        RequestAddnMeterPacket(addr, GET_NAME, buf, len);

}

void TProtocol_211::RequestSensorZeroOffset(unsigned char addr, unsigned char* buf, int* len)
{
        RequestAddnMeterPacket(addr, GET_ZOFF, buf, len);
}

void TProtocol_211::RequestSensorSoftVersion(unsigned char addr, unsigned char* buf, int* len)
{
        RequestAddnMeterPacket(addr, GET_SVER,buf, len);
}

void TProtocol_211::RequestSensorMeterSerialNumber(unsigned char addr, unsigned char* buf, int* len)
{
        RequestAddnMeterPacket(addr, GET_SERN, buf, len);
}

void TProtocol_211::RequestSensorAveragingTacts(unsigned char addr, unsigned char* buf, int* len)
{
        RequestAddnMeterPacket(addr, GET_TACT, buf, len);
}

void TProtocol_211::RequestSensorAveragingPeriod(unsigned char addr, unsigned char* buf, int* len)
{
        RequestAddnMeterPacket(addr, GET_PERD, buf, len);
}


//--------------------------------------received packet process-----------------------------------------------------------

//Îáðàáîòêà îñíîâíîãî ïàêåòà ñúåìà ïîêàçàíèé äàò÷èêà
int TProtocol_211::AcceptSensorMeasVal(BYTE* buf,double* x, double* y, BYTE* unitx, BYTE* unity)
{

//D5.7 çíàê óãëà ïî îñè X
  unsigned char signX=(buf[DATAOFFSET+5])&(1<<7);

//D5.6 ðàçìåðíîñòü óãëàïî îñè X
  unsigned char unitsX=(buf[DATAOFFSET+5])&(1<<6);

//D5.5 - D4.0 öåëàÿ ÷àñòü óãëà ïî X
  unsigned int intX=((unsigned int) (buf[DATAOFFSET+5])&0x3F)<<8;
			   intX+=(unsigned int)buf[DATAOFFSET+4];

//D3.7 - D3.0 äðîáíàÿ ÷àñòü óãëà ïî X
  unsigned int flX=(unsigned int) (buf[DATAOFFSET+3]);

//D2.7 çíàê óãëà ïî îñè Y
  unsigned char signY=(buf[DATAOFFSET+2])&(1<<7);

//D2.6 ðàçìåðíîñòü óãëà ïî îñè Y
  unsigned char unitsY=(buf[DATAOFFSET+2])&(1<<6);

//D2.5-D1.0 - öåëàÿ ÷àñòü óãëà Y
  unsigned int intY=((unsigned int) (buf[DATAOFFSET+2])&0x3F)<<8;
			   intY+=(unsigned int)buf[DATAOFFSET+1];

//D3.7 - D3.0 äðîáíàÿ ÷àñòü óãëà ïî X
  unsigned int flY=(unsigned int) (buf[DATAOFFSET+0]);

//Óñòàíàâëèâàåì äàò÷èêó åäèíèöû ïî Õ
  if (unitsX==0)        *unitx=ANGLE_SECONDS;
  else                  *unitx=ANGLE_MINUTES;

//Óñòàíàâëèâàåì äàò÷èêó åäèíèöû ïî Y
  if (unitsY==0)        *unity=ANGLE_SECONDS;
  else                  *unity=ANGLE_MINUTES;

//Âû÷èñëÿåì è óñòàíàâëèâàåì çíà÷åíèå óãëà ïî X
  double angle = (double)intX+((double)flX/(double)0x100);

//Ïðèâîäèì ê 3çíàêàì ïîñëåçàïÿòîé
//  angle*=1000; angle=floor(angle); angle/=1000;

  if (signX) angle*=-1;
  *x = angle;

//Âû÷èñëÿåìè óñòàíàâëèâàåì çíà÷åíèå óãëà ïë Y
  angle = (double)intY+((double)flY/(double)0x100);

//Ïðèâîäèì ê 3çíàêàì ïîñëåçàïÿòîé
//  angle*=1000; angle=floor(angle); angle/=1000;

  if (signY) angle*=-1;
  *y = angle;

  return 0;
}

int TProtocol_211::AcceptSensorSerialNumber(BYTE* buf, unsigned int* sn)
{
	 unsigned int serial3=((unsigned int)buf[7])<<24;
	 unsigned int serial2=((unsigned int)buf[6])<<16;
	 unsigned int serial1=((unsigned int)buf[5])<<8;
	 unsigned int serial0=((unsigned int)buf[4])<<0;

	 *sn=serial3+serial2+serial1+serial0;

	 return 0;
}

int TProtocol_211::AcceptSensorSoftVersion(BYTE* buf, unsigned int* sv)
{
	*sv =((unsigned short)buf[DATAOFFSET+1])<<8;
	*sv+=(unsigned short)buf[DATAOFFSET];
	return 0;
}

//--------------------------------------global functions packet creating--------------------------------------------------


//Îñíîâíîé ïðîòîêîë ïàêåòà çàïðîñà
void TProtocol_211::RequestMainMeterPacket(unsigned char addr, main_packet_211_id packet, unsigned char* buf, int* len)
{
//Èíèöèàëèçàöèÿ
      int idx=0; unsigned char chsum=0; ClearRequestBuf();

//Íà÷àëî ïàêåòà
	  request_packetBUF[idx]=PACKET_START; idx++;
//Òèï ïðîòîêîëà
	  request_packetBUF[idx]=MAIN_PR_211;       chsum=chsum^request_packetBUF[idx]; idx++;
//Òèï ïàêåòà
	  request_packetBUF[idx]=packet;            chsum=chsum^request_packetBUF[idx]; idx++;
//Àäðêñ èçìåðèòåëÿ
	  request_packetBUF[idx]=addr;              chsum=chsum^request_packetBUF[idx]; idx++;
//Êîíòðîëüíàÿ ñóììà
	  request_packetBUF[idx]=chsum;                                                 idx++;
//Êîíåö ïàêåòà
	  request_packetBUF[idx]=PACKET_END;                                            idx++;

	  request_packetLEN=idx;

//Êîäèðóåì ESCAP Eïîñëåäîâàòåëüíîñòè
	   this->EscapeBytesEncode(request_packetBUF,&request_packetLEN);

//Êîïèðóåì ïàêåò è äëèíó âûçâàâøåé ïðîöåäóðå
		memcpy(buf,request_packetBUF,request_packetLEN); *len=request_packetLEN;
}


//Äîïîëíèòåëüíûé ïðîòîêîë ïàêåòà çàïðîñà
void TProtocol_211::RequestAddnMeterPacket(unsigned char addr, addn_packet_211_id packet, unsigned char* buf, int* len)
{
//Èíèöèàëèçàöèÿ
      int idx=0; unsigned char chsum=0; ClearRequestBuf();

//Íà÷àëî ïàêåòà
      request_packetBUF[idx]=PACKET_START; idx++;
//Òèï ïðîòîêîëà
      request_packetBUF[idx]=ADDN_PR_211;       chsum=chsum^request_packetBUF[idx]; idx++;
//Òèï ïàêåòà
      request_packetBUF[idx]=packet;            chsum=chsum^request_packetBUF[idx]; idx++;
//Àäðåñ èçìåðèòåëÿ
      request_packetBUF[idx]=addr;              chsum=chsum^request_packetBUF[idx]; idx++;
//Êîíòðîëüíàÿ ñóììà
      request_packetBUF[idx]=chsum;                                                 idx++;
//Êîíåö ïàêåòà
      request_packetBUF[idx]=PACKET_END;                                            idx++;

      request_packetLEN=idx;

//Êîäèðóåì ESCAPE Eïîñëåäîâàòåëüíîñòè
	   this->EscapeBytesEncode(request_packetBUF,&request_packetLEN);
//Êîïèðóåì ïàêåò è äëèíó âûçâàâøåé ïðîöåäóðå
        memcpy(buf,request_packetBUF,request_packetLEN); *len=request_packetLEN;
}


int TProtocol_211::CheckPacket(unsigned char addr, unsigned char* buf, int* len)
{

	//Decode escape
	if (EscapeBytesDecode(buf, len)!=0) return -1; //escape error

	//Check sum
	BYTE csum = 0;

	for (int i = 1; i < *len-2; i++) {

		csum^=buf[i];
	}

	if (csum!=buf[*len-2]) {

		return -2; //Checksum is incorrect
	}

	if (addr!=buf[3]) return -3; //Wrong addr



	return 0;
}
//---------------------------------------------------------------------------

