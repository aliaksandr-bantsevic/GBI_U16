//---------------------------------------------------------------------------

#ifndef Protocol_211H
#define Protocol_211H
//---------------------------------------------------------------------------


#include "defs.h"
#include "Protocol.h"

typedef enum {

cMEAS_VAL=0x01,        //показания измерителя
cMEAS_VER=0x0E,        //Версия измерителя
cACK_ERR=0xFF,         //сообщение об ошибке

cGET_BAUD=0x11,        //запросить текущуюскорость обмена
cGET_NAME=0x13,        //Запросить имя измерителя
cGET_ZOFF=0x15,        //Запросить смещение нуля
cGET_SVER=0x1A,        //Запросить номер редакции ПО
cGET_SERN=0x1B,        //Запросить заводской номер измерителя
cGET_TACT=0x1C,        //Запросить число тактов усреднения
cGET_PERD=0x1E,        //Запросить период усреднения

} ind3_common_request_type;

//Число тактов усреднения
typedef enum {
	averaging_tacts_1 = 0x00,
	averaging_tacts_2 = 0x01,
	averaging_tacts_4 = 0x02,
	averaging_tacts_8 = 0x03,
	averaging_tacts_16= 0x04,
	averaging_tacts_32= 0x05
} ind3_averaging_tacts;

//Период усреднения
typedef enum {
	averaging_period_10  = 0x00,
	averaging_period_20  = 0x01,
	averaging_period_50  = 0x02,
	averaging_period_100 = 0x03
} ind3_averaging_period;

//Скорости обмена по сом порту
typedef enum {

	baud_1200  =  0x01,
	baud_2400  =  0x02,
	baud_4800  =  0x03,
	baud_9600  =  0x04,
	baud_19200 =  0x05,
	baud_38400 =  0x06,
	baud_57600 =  0x07,
	baud_115200=  0x08

} ind3_baudrate;

//Коды ошибок приходят от датчика
typedef enum {

CHSUM_MEAS_MEM_ERR = 0x10,
CHSUM_ADJS_MEM_ERR = 0x11,
CHSUM_PROG_MEM_ERR = 0x12,

} ind3_sensor_err;

//Единицы измерения угла

typedef enum {

ANGLE_SECONDS=0,
ANGLE_MINUTES=1

} angle_units;


#define PACKET_START 0x7E       //разделитель пакетов
#define PACKET_END   0x7E       //разделитель пакетов
#define ESCAPE_BYTE  0x7D       //escape байт
#define CODE7D_BYTE  0x5D       //0x7D код байт
#define CODE7E_BYTE  0x5E       //0x7E код байт


typedef enum {

MAIN_PR_211=0x9B,     //основные протоколы 2.11
ADDN_PR_211=0x9C,     //дополнительныепротоколы 2.11
PACK_PR_210=0x9A,     //дополнительныепротоколы 2.10
PACK_PR_NVM=0x9D      //дополнительныепротоколы запись в NVM

} protocol_211_id;


typedef enum {

MEAS_VAL=0x01,        //показания измерителя
MEAS_VER=0x0E,        //Версия измерителя
PACK_ERR=0xFF         //сообщение об ошибке

} main_packet_211_id;

typedef enum {

GET_BAUD=0x01,        //запросить текущуюскорость обмена
SET_BAUD=0x02,        //Установить текущую скорость обмена
GET_NAME=0x03,        //Запросить имя измерителя
SET_NAME=0x04,        //Установить имя измерителя
GET_ZOFF=0x05,        //Запросить смещение нуля
SET_ZOFF=0x06,        //Установить смещение нуля
SET_ADDR=0x09,        //Установить новый адрес
GET_SVER=0x0A,        //Запросить номер редакции ПО
GET_SERN=0x0B,        //Запросить заводской номеризмерителя
GET_TACT=0x0C,        //Запросить число тактов усреднения
SET_TACT=0x0D,        //Установить число тактов усреднения
GET_PERD=0x0E,        //Запросить период усреднения
SET_PERD=0x0F         //Установить период усреднения


} addn_packet_211_id;

typedef enum {

MEAS_VAL10=0x01,      //показания измерителя
MEAS_PNG10=0x03       //пинг змерителя

} addn_packet_210_id;

//смещение в пакете на начало полезных данных
#define DATAOFFSET 4

#define request_packetBUF_len 1024
#define ClearRequestBuf() memset(request_packetBUF,0,request_packetBUF_len)

class TProtocol_211 : public TProtocol {

public:

	TProtocol_211();
	~TProtocol_211();

   	int CheckPacket(unsigned char addr, unsigned char* buf, int* len);
	int EscapeBytesDecode(unsigned char* buf, int* len);
	int EscapeBytesEncode(unsigned char* buf, int* len);

private:


	BYTE request_packetBUF [request_packetBUF_len];
	int request_packetLEN;


	void RequestMainMeterPacket(unsigned char addr, main_packet_211_id packet, unsigned char* buf, int* len);
	void RequestAddnMeterPacket(unsigned char addr, addn_packet_211_id packet, unsigned char* buf, int* len);

public:

//------------------Основной протокол 2.11-------------------------------------

//Запросить результат измерения (сформированный пакет копируется в buf число байт len)

void RequestMeasureResult(unsigned char addr, unsigned char* buf, int* len);

//Запросить версию измерителя
void RequestMeterVerion(unsigned char addr, unsigned char* buf, int* len);

//------------------Дополнтельный протокол 2.11--------------------------------

//Запросить скорость обмена
void RequestSensorBaudRate(unsigned char addr, unsigned char* buf, int* len);

//Запросить имя измерителя
void RequestSensorMeterName(unsigned char addr, unsigned char* buf, int* len);

//Запросить смещение нуля
void RequestSensorZeroOffset(unsigned char addr, unsigned char* buf, int* len);

//Запросить номер редакции ПО
void RequestSensorSoftVersion(unsigned char addr, unsigned char* buf, int* len);

//Запросить заводской номер измерителя
void RequestSensorMeterSerialNumber(unsigned char addr, unsigned char* buf, int* len);

//Запросить количество тактов усреднения
void RequestSensorAveragingTacts(unsigned char addr, unsigned char* buf, int* len);

//Запросить период усреднения
void RequestSensorAveragingPeriod(unsigned char addr, unsigned char* buf, int* len);

//////////ФОРМИРОВАНИЕ ПАКЕТА УСТАНОВКИ ПАРАМЕТРОВ В СТОРОНУ ДАТЧИКА////////////

//Установить скорость обмена
void SetSensorBaudRate(unsigned char addr, ind3_baudrate baud, unsigned char* buf, int* len);

//Установить имя измерителя  передаваемая в функцию строка неболее 16 значащих символов должна заканчиваться нулем
void SetSensorName(unsigned char addr, char* name, unsigned char* buf, int* len);

//Установить смещение нуля
void SetsensorZeroOffset(unsigned char addr, double angle_X, double angle_Y, angle_units units_X, angle_units units_Y, unsigned char* buf, int* len);

//Установить новый адрес
void SetSensorNewAddress(unsigned char addr, unsigned char newaddr, unsigned char* buf, int* len);

//Установить количество тактов усреднения
void SetSensorAveragingTacts(unsigned char addr, ind3_averaging_tacts tacts, unsigned char* buf, int* len);

//Установить период усреднения
void SetSensorAveragingPeriod(unsigned char addr, ind3_averaging_period period, unsigned char* buf, int* len);

void RequestSaveSettingsNVM(unsigned char addr, unsigned char* buf, int* len);

//-------------------------------Обработка принятых пакетов---------------------------------------

//Основной пакет измерения
int AcceptSensorMeasVal(BYTE* buf,double* x, double* y, BYTE* unitx, BYTE* unity);

//Запрос заводского номера
int AcceptSensorSerialNumber(BYTE* buf, unsigned int* sn);

int AcceptSensorSoftVersion(BYTE* buf, unsigned int* sv);

};






#endif
