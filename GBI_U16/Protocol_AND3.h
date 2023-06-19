//---------------------------------------------------------------------------

#ifndef Protocol_AND3H
#define Protocol_AND3H

#include "defs.h"
#include "Protocol.h"

//---------------------------------------------------------------------------

typedef struct
{
  WORD  frst:1; // Перезагрузка
  WORD   fdr:1; // Готовность данных датчика
  WORD ft5dr:1; // Готовность данных температуры
  WORD fthdr:1; // Готовность данных вентилятора

  WORD   fte:1; // Ошибки чтения датчика
  WORD   fce:1; // Ошибки CRC датчика
  WORD   fre:1; // Ошибки диапазона датчика
  WORD    r1:1; // Резерв

  WORD ft5te:1; // Ошибки чтения температуры
  WORD ft5re:1; // Ошибки диапазона температуры
  WORD fthre:1; // Ошибка частоты вентилятора
  WORD ftrme:1; // Ошибка терморегулятора

  WORD  fadr:1; // Идет поиск адреса
  WORD  ftrm:1; // Терморегулятор включен
  WORD    r2:1; // Резерв
  WORD    r3:1; // Резерв
} and3_SW;

typedef struct
{
  WORD nofir1:1;   // Отключить фильтр 1
  WORD nofir2:1;   // Отключить фильтр 2
  WORD noidle:1;   // Отключить IDLE
  WORD nod3:1;     // Отключить таймауты

  WORD not5av:1;   // Не усреднять по температуре
  WORD notrm:1;    // Отключить терморегулятор
  WORD nostack:1;  // Не заполнять буфер акселерометра
  WORD noadrdet:1; // Не детектировать адрес датчика

  WORD noacmp:1;   // Не компенсировать ускорение на 0 частоте
  WORD nofir3:1;   // Отключить фильтр 3
  WORD nopwr:1;    // Отключить питание датчиков для БС
  WORD nometeo:1;  // Отключить метеостанцию

   // WORD reserved:4;
  WORD  tostart:1;  // Запрос по таймауту      // !!! 1.202
  WORD    br115:1;  // Скорость 115200         // !!! 1.202
  WORD     to10:1;  // Таймаут 10 мс (или 5 мс)// !!! 1.202
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
