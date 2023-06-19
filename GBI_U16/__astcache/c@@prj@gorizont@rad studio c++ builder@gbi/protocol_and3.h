//---------------------------------------------------------------------------

#ifndef Protocol_AND3H
#define Protocol_AND3H

#include "defs.h"
#include "Protocol.h"

//---------------------------------------------------------------------------

typedef struct
{
  WORD  frst:1; // Ïåðåçàãðóçêà
  WORD   fdr:1; // Ãîòîâíîñòü äàííûõ äàò÷èêà
  WORD ft5dr:1; // Ãîòîâíîñòü äàííûõ òåìïåðàòóðû
  WORD fthdr:1; // Ãîòîâíîñòü äàííûõ âåíòèëÿòîðà

  WORD   fte:1; // Îøèáêè ÷òåíèÿ äàò÷èêà
  WORD   fce:1; // Îøèáêè CRC äàò÷èêà
  WORD   fre:1; // Îøèáêè äèàïàçîíà äàò÷èêà
  WORD    r1:1; // Ðåçåðâ

  WORD ft5te:1; // Îøèáêè ÷òåíèÿ òåìïåðàòóðû
  WORD ft5re:1; // Îøèáêè äèàïàçîíà òåìïåðàòóðû
  WORD fthre:1; // Îøèáêà ÷àñòîòû âåíòèëÿòîðà
  WORD ftrme:1; // Îøèáêà òåðìîðåãóëÿòîðà

  WORD  fadr:1; // Èäåò ïîèñê àäðåñà
  WORD  ftrm:1; // Òåðìîðåãóëÿòîð âêëþ÷åí
  WORD    r2:1; // Ðåçåðâ
  WORD    r3:1; // Ðåçåðâ
} and3_SW;

typedef struct
{
  WORD nofir1:1;   // Îòêëþ÷èòü ôèëüòð 1
  WORD nofir2:1;   // Îòêëþ÷èòü ôèëüòð 2
  WORD noidle:1;   // Îòêëþ÷èòü IDLE
  WORD nod3:1;     // Îòêëþ÷èòü òàéìàóòû

  WORD not5av:1;   // Íå óñðåäíÿòü ïî òåìïåðàòóðå
  WORD notrm:1;    // Îòêëþ÷èòü òåðìîðåãóëÿòîð
  WORD nostack:1;  // Íå çàïîëíÿòü áóôåð àêñåëåðîìåòðà
  WORD noadrdet:1; // Íå äåòåêòèðîâàòü àäðåñ äàò÷èêà

  WORD noacmp:1;   // Íå êîìïåíñèðîâàòü óñêîðåíèå íà 0 ÷àñòîòå
  WORD nofir3:1;   // Îòêëþ÷èòü ôèëüòð 3
  WORD nopwr:1;    // Îòêëþ÷èòü ïèòàíèå äàò÷èêîâ äëÿ ÁÑ
  WORD nometeo:1;  // Îòêëþ÷èòü ìåòåîñòàíöèþ

   // WORD reserved:4;
  WORD  tostart:1;  // Çàïðîñ ïî òàéìàóòó      // !!! 1.202
  WORD    br115:1;  // Ñêîðîñòü 115200         // !!! 1.202
  WORD     to10:1;  // Òàéìàóò 10 ìñ (èëè 5 ìñ)// !!! 1.202
  WORD reserved:1;
} and3_MODE;

typedef struct {

	BYTE addr;
	BYTE cmd_code;
	BYTE cmd_byte1;
	BYTE cmd_byte2;
	int cmd_len;

} and3_cmd;


typedef struct {

float X;
float Y;
short T;
and3_SW sw;
DWORD pn;
and3_MODE md;

}and3_res_float;


#define AND3_CMD_GETALL 		201
#define AND3_LEN_GETALL 		18
#define AND3_DAT1_GETALL 		0
#define AND3_DAT2_GETALL 		0

#define AND3_LEN_CMD            6

class TProtocol_AND3 : public TProtocol {

public:

	TProtocol_AND3();
	~TProtocol_AND3();

	int RequestMeasureResult(unsigned char addr, unsigned char* buf, int* len);
	int CheckPacket(unsigned char addr, unsigned char* buf, int* len);
	int AcceptSensorMeasVal(BYTE* buf,double* x, double* y, BYTE* unitx, BYTE* unity);

private:


	and3_cmd cmd;

};


#endif
