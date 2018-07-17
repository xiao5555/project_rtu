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
	}HARD_ENUM;//硬件接口
	typedef enum{
		TYPE_NONE,
		TYPE_SXH,
		TYPE_HASX,
		TYPE_HKWS,
		TYPE_NUM
	}TYPE_ENUM;//类型
	typedef enum{
		IMAGE_NONE,
		IMAGE_320x240,
		IMAGE_640x480,
		IMAGE_1280x1024,
		IMAGE_1600x1024,
		IMAGE_NUM
	}IMAGE_ENUM;//类型
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
		IDEN_CONDUCTIVITY,//电导率
		IDEN_PH,
		IDEN_GEOTHERMAL,//地温
		IDEN_INSTANTANEOUS_FLOW_RATE,//瞬时流速
		IDEN_HUMIDITY,//湿度
		IDEN_AIR_PRESSURE,//气压
		IDEN_WIND_DIRECTION,//风向
		IDEN_WIND_SPEED,//风速
		IDEN_CURRENT_EVAPORATION,//当前蒸发
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
struct CamerPar{//摄像头参数
	struct Attribute Number;//编号
	struct Attribute Id;//ID
	struct Attribute HardInterface;//硬件接口
	struct Attribute Type;//类型
	struct Attribute ImageSize;//图像大小
	struct Attribute ReportInterval;//上报间隔
};
struct PassagePar{//通道参数
	struct Attribute PassNumber;//通道号
	struct Attribute  Identification;//标识
	struct Attribute  Unit;//单位
	struct Attribute  Precision;// 精度 
	struct Attribute  AcquisitionSwitch;//采集开关
	struct Attribute HardInterface;// 硬件接口 
	struct Attribute PowerOnTime;//上电时间 
	struct Attribute SamplingBaseValue;//采样基值 
	struct Attribute SamplingInterval;//采样间隔 
	struct Attribute AlarmUpLimitValue;//报警上限值 
	struct Attribute AlarmDownLimitValue;//报警下限值 
	struct Attribute AlarmThreshold;//报警阈值 
	struct Attribute AlarmCaptureInterval;//报警抓拍间隔 
	struct Attribute AlarmAssociatedRelay;//报警关联继电器 
	struct Attribute AlarmAssociatedDo;//报警关联DO
};
struct TerminalPar{//终端参数
	struct Attribute WorkingAgreement;//工作协议
	struct Attribute OperatingMode;//工作模式
	struct Attribute TelemetryStationAddress;//遥测站地址
	struct Attribute DebugLevel;//调试等级
	struct Attribute TimingInterval;//定时上报间隔
	struct Attribute OverlapInterval;//家报间隔
	struct Attribute CommunicationStationNumber;//通信站识别号
	struct Attribute UniformTimeInterval;//均匀时段间隔
};
struct CenterPar{//中心参数
	struct Attribute ApnDialNumber;//APN拨号号码
	struct Attribute APN;//APN
	struct Attribute PppDialUsername;//PPP 拨号用户名
	struct Attribute PppDialPassword;//PPP 拨号密码
	struct Attribute HeartbeatInterval;//心跳间隔
	struct Attribute ReconnectionInterval;//重连间隔
	struct Attribute ServicesNumber; //服务个数
};
struct ServerPar{//服务器参数
	struct Attribute ServerNumber;//服务器编号
	struct Attribute ServerSite;//服务器站址
	struct Attribute ServerType;//服务器类型
	struct Attribute serverAddress;//服务器地址
	struct Attribute ServerPort;//服务器端口
};
struct BeIDouPar{//北斗参数
	struct Attribute CommunicationID;//通信ID
	struct Attribute Encoding;//编码方式
	struct Attribute CommunicationInterface;//通信接口
	struct Attribute CommunicationBaudRate;//通信波特率
	struct Attribute TargetingApplication;//定位申请
	struct Attribute CalibrationTimeInterval;//校时间隔
};
/*********************************************参数***************************************************************/
typedef struct SysInfo{
	struct HandSetPar ManualParSet;//人工置数
	struct CamerPar CamerParSet;//摄像头
	struct PassagePar PassageParSet;//通道设置
	struct TerminalPar TerminalParSet;//终端参数
	struct CenterPar  CenterParSet;//中心参数
	struct ServerPar ServerParSet;//服务器参数
	struct BeIDouPar BeIDouParSet;//北斗参数
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

