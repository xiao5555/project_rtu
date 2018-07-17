#ifndef _SYS_INFO_H__
#define _SYS_INFO_H__
#include <stdint.h>
#include "PrivateList/PrivateList.h"
#include "Inc/AttributeTypes.h"
	typedef enum{
		HARD_NONE,
		HARD_RS485_1,
		HARD_RS485_2,
		HARD_RS232_1,
		HARD_RS232_2,
		HARD_RAIN_FALL,
		HARD_RAIN_FALL1,
		HARD_ADC0,
		HARD_ADC1,
		HARD_ADC2,
		HARD_ADC3,
		HARD_ADC4,
		HARD_ADC5,
		HARD_ADC6,
		HARD_ADC7,
		HARD_DI0,
		HARD_DI1,
		HARD_DI2,
		HARD_DI3,
		HARD_GRAY_CODE,
		HARD_SDI,
		HARD_NUM
	}HARD_ENUM;//Ӳ���ӿ�
	typedef enum{
		TYPE_NONE,
		TYPE_SXH,
		TYPE_HASX,
		TYPE_HKWS,
		TYPE_NUM
	}TYPE_ENUM;//����
	typedef enum{
		IMAGE_NONE,
		IMAGE_320x240,
		IMAGE_640x480,
		IMAGE_1280x1024,
		IMAGE_1600x1024,
		IMAGE_NUM
	}IMAGE_ENUM;//����
	typedef enum{
		IDEN_RAIN_1,
		IDEN_WATER_1,
		IDEN_FLOW,
		IDEN_M10,
		IDEN_M20,
		IDEN_M30,
		IDEN_M40,
		IDEN_M50,
		IDEN_M60,
		IDEN_M80,
		IDEN_M100,
		IDEN_CONDUCTIVITY,//�絼��
		IDEN_PH,
		IDEN_GEOTHERMAL,//����
		IDEN_INSTANTANEOUS_FLOW_RATE,//˲ʱ����
		IDEN_HUMIDITY,//ʪ��
		IDEN_AIR_PRESSURE,//��ѹ
		IDEN_WIND_DIRECTION,//����
		IDEN_WIND_SPEED,//����
		IDEN_CURRENT_EVAPORATION,//��ǰ����
		IDEN_CURRENT_NUM
	}IDEN_ENUM;
	typedef enum{
		UNIT_MM,
		UNIT_M,
		UNIT_KM,
		UNIT_NUM
	}UNIT_ENUM;
	typedef enum{
		SWITCH_OPEN,
		SWITCH_CLOSE,
		SWITCH_NUM
	}SWITCH_ENUM;
	typedef enum{
		RELAY_NONE,
		RELAY_K1,
		RELAY_K2,
		RELAY_K1_K2,
		RELAY_NUM
	}RELAY_ENUM;
	typedef enum{
		DO_NONE,
		DO_DO0,
		DO_DO1,
		DO_DO0_DO1,
		DO_NUM
	}DO_ENUM;
	typedef enum{
		PROTOCOL_HEX,
		PROTOCOL_EXPANSION,
		PROTOCOL_MODEBUS,
		PROTOCOL_WATER_RESOURCE,
		PROTOCOL_WATER_ASCII,
		PROTOCOL_NUM
	}PROTOCOL_ENUM;
	typedef enum{
		MODE_COMPATIBLE,
		MODE_SELF_REPORT,
		MODE_INQUIRE,
		MODE_DEBUG,
		MODE_NUM
	}MODE_ENUM;
	typedef enum{
		LEVEL_0,
		LEVEL_1,
		LEVEL_2,
		LEVEL_NUM
	}LEVEL_ENUM;
	typedef enum{
		SERVER_NUM_0,
		SERVER_NUM_1,
		SERVER_NUM_2,
		SERVER_NUM_3,
		SERVER_NUM_4,
		SERVER_NUM
	}SERVER_NUM_ENUM;
	typedef enum{
		SERVER_TYPE_NONE,
		SERVER_TYPE_TCP,
		SERVER_TYPE_BEI_DOU,
		SERVER_TYPE_HAI_SHI,
		SERVER_TYPE_PSTN,
		SERVER_TYPE_SHORT_WAVE,
		SERVER_TYPE_UDP,
		SERVER_TYPE_SERAL_PORT,
		SERVER_TYPE_NUM
	}SERVER_TYPE_ENUM;
	typedef enum{
		ENCODING_CHINESE,
		ENCODING_BCD
	}ENCODING_ENUM;
	typedef enum{
		COMMUNICATION_RS485_1,
		COMMUNICATION_RS485_2,
		COMMUNICATION_RS232_1,
		COMMUNICATION_RS232_2,
		COMMUNICATION_NUM
	}COMMUNICATION_ENUM;
	typedef enum{
		BAUDRATE_2400,
		BAUDRATE_4800,
		BAUDRATE_9600,
		BAUDRATE_19200,
		BAUDRATE_14400,
		BAUDRATE_38400,
		BAUDRATE_57600,
		BAUDRATE_115200,
		BAUDRATE_NUM
	}BAUDRATE_ENUM;
	typedef enum{
		POSITION_REQUEST,
		POSITION_CLOSE,
		POSITION_NUM
	}POSITION_ENUM;
	
struct HandSetPar{
	struct Attribute RainData;
	struct Attribute WaterData;
};
struct CamerPar{//����ͷ����
	struct Attribute Number;//���
	struct Attribute Id;//ID
	struct Attribute HardInterface;//Ӳ���ӿ�
	struct Attribute Type;//����
	struct Attribute ImageSize;//ͼ���С
	struct Attribute ReportInterval;//�ϱ����
};
struct PassagePar{//ͨ������
	struct Attribute PassNumber;//ͨ����
	struct Attribute  Identification;//��ʶ
	struct Attribute  Unit;//��λ
	struct Attribute  Precision;// ���� 
	struct Attribute  AcquisitionSwitch;//�ɼ�����
	struct Attribute HardInterface;// Ӳ���ӿ� 
	struct Attribute PowerOnTime;//�ϵ�ʱ�� 
	struct Attribute SamplingBaseValue;//������ֵ 
	struct Attribute SamplingInterval;//������� 
	struct Attribute AlarmUpLimitValue;//��������ֵ 
	struct Attribute AlarmDownLimitValue;//��������ֵ 
	struct Attribute AlarmThreshold;//������ֵ 
	struct Attribute AlarmCaptureInterval;//����ץ�ļ�� 
	struct Attribute AlarmAssociatedRelay;//���������̵��� 
	struct Attribute AlarmAssociatedDo;//��������DO
};
struct TerminalPar{//�ն˲���
	struct Attribute WorkingAgreement;//����Э��
	struct Attribute OperatingMode;//����ģʽ
	struct Attribute TelemetryStationAddress;//ң��վ��ַ
	struct Attribute DebugLevel;//���Եȼ�
	struct Attribute TimingInterval;//��ʱ�ϱ����
	struct Attribute OverlapInterval;//�ұ����
	struct Attribute CommunicationStationNumber;//ͨ��վʶ���
	struct Attribute UniformTimeInterval;//����ʱ�μ��
};
struct CenterPar{//���Ĳ���
	struct Attribute ApnDialNumber;//APN���ź���
	struct Attribute APN;//APN
	struct Attribute PppDialUsername;//PPP �����û���
	struct Attribute PppDialPassword;//PPP ��������
	struct Attribute HeartbeatInterval;//�������
	struct Attribute ReconnectionInterval;//�������
	struct Attribute ServicesNumber; //�������
};
struct ServerPar{//����������
	struct Attribute ServerNumber;//���������
	struct Attribute ServerSite;//������վַ
	struct Attribute ServerType;//����������
	struct Attribute serverAddress;//��������ַ
	struct Attribute ServerPort;//�������˿�
};
struct BeIDouPar{//��������
	struct Attribute CommunicationID;//ͨ��ID
	struct Attribute Encoding;//���뷽ʽ
	struct Attribute CommunicationInterface;//ͨ�Žӿ�
	struct Attribute CommunicationBaudRate;//ͨ�Ų�����
	struct Attribute TargetingApplication;//��λ����
	struct Attribute CalibrationTimeInterval;//Уʱ���
};
/*********************************************����***************************************************************/
typedef struct SysInfo{
	struct HandSetPar ManualParSet;//�˹�����
	struct CamerPar CamerParSet;//����ͷ
	struct PassagePar PassageParSet;//ͨ������
	struct TerminalPar TerminalParSet;//�ն˲���
	struct CenterPar  CenterParSet;//���Ĳ���
	struct ServerPar ServerParSet;//����������
	struct BeIDouPar BeIDouParSet;//��������
	struct Attribute SoftVersion;//
}SysInfo_TypeDef;

void SetRainDay(float rain);
float GetRainDay(void);
void SetRainHour(float Rain);
float GetRainHour(void);
void SetWaterDay(float water);
float GetWaterDay(void);

extern struct SIS_List* SerialReceivedList;
/**********************************************External function**********************************************************/
void VariableInit(void);
#endif//_SYS_INFO_H__

