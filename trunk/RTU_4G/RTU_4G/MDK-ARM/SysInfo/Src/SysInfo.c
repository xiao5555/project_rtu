#include "Inc/sysinfo.h"
#include <stdint.h>
#include <stdio.h>


	static float  RainData;
	static float  RainHour;
	static float  WaterData;
	static uint8_t  Number;//编号
	static uint16_t Id;//ID
	static HARD_ENUM HardInterface;//硬件接口
	static TYPE_ENUM Type;//类型
	static IMAGE_ENUM ImageSize;//图像大小
	static uint16_t ReportInterval;//上报间隔
	static uint8_t PassNumber;//通道号
	static IDEN_ENUM  Identification;//标识
	static UNIT_ENUM  Unit;//单位
	static float  Precision;// 精度 
	static SWITCH_ENUM  AcquisitionSwitch;//采集开关
	static HARD_ENUM HardInterface;// 硬件接口 
	static uint8_t PowerOnTime;//上电时间 
	static float SamplingBaseValue;//采样基值 
	static uint16_t SamplingInterval;//采样间隔 
	static uint16_t AlarmUpLimitValue;//报警上限值 
	static uint16_t AlarmDownLimitValue;//报警下限值 
	static float AlarmThreshold;//报警阈值 
	static uint16_t AlarmCaptureInterval;//报警抓拍间隔 
	static RELAY_ENUM AlarmAssociatedRelay;//报警关联继电器 
	static DO_ENUM AlarmAssociatedDo;//报警关联DO
	static PROTOCOL_ENUM WorkingAgreement;//工作协议
	static MODE_ENUM OperatingMode;//工作模式
	static char TelemetryStationAddress[10];//遥测站地址
	static LEVEL_ENUM DebugLevel;//调试等级
	static uint16_t TimingInterval;//定时上报间隔
	static uint16_t OverlapInterval;//家报间隔
	static char CommunicationStationNumber[22];//通信站识别号
	static uint16_t UniformTimeInterval;//均匀时段间隔
	static char ApnDialNumber[24];//APN拨号号码
	static char APN[10];//APN
	static char PppDialUsername[24];//PPP 拨号用户名
	static char PppDialPassword[24];//PPP 拨号密码
	static uint16_t HeartbeatInterval;//心跳间隔
	static uint16_t ReconnectionInterval;//重连间隔
	static SERVER_NUM_ENUM ServicesNumber; //服务个数
	static char ServerNumber;//服务器编号?????????????????????????????????????????
	static char ServerSite[15];//服务器站址
	static SERVER_TYPE_ENUM ServerType;//服务器类型
	static char serverAddress[15];//服务器地址
	static uint32_t ServerPort;//服务器端口
	static char CommunicationID[10];//通信ID
	static ENCODING_ENUM Encoding;//编码方式
	static COMMUNICATION_ENUM CommunicationInterface;//通信接口
	static BAUDRATE_ENUM CommunicationBaudRate;//通信波特率
	static POSITION_ENUM TargetingApplication;//定位申请
	static uint8_t  CalibrationTimeInterval;//校时间隔

void SetRainDay(float rain)
{
	RainData=rain;
}
float GetRainDay(void)
{
	return RainData;
}
void SetRainHour(float Rain)
{
	RainHour=Rain;
}
float GetRainHour(void)
{
	return RainHour;
}
void SetWaterDay(float water)
{
	WaterData=water;
}
float GetWaterDay(void)
{
	return WaterData;
}
/********************************************************************
     *@bref 
     *     
     *@ret 
  ***********************************************************************/	
static IO_ERR AttributeProcess(struct Attribute *c_this,void* val,IO_FLAG flag)
{
	IO_ERR err = IO_ERR_OK;
	if(flag == IO_FLAG_R)
	{
		*(void**)(val) = ReadAttr(c_this,&err);//读的时候实际传的val应为二级指针
	}
	else//IO_FLAG_W
	{
		err = WriteAttr(c_this, val);
	}
	return err;
}
/********************************************************************
 *@bref 
 *     
 *@ret 
***********************************************************************/
static void CommonSet(struct Attribute *c_this,const void* val,IO_ERR* err)
{
	IO_ERR _err;
	void* _val = (void*)val;
	_err = AttributeProcess(c_this,_val,IO_FLAG_W);
	if(err)
		*err = _err;
	return ;
}
/********************************************************************
 *@bref 
 *     
 *@ret 
***********************************************************************/
static const void* CommonGet(struct Attribute *c_this,IO_ERR* err)
{
	IO_ERR _err;
	double* val = 0;
	_err = AttributeProcess(c_this,&val,IO_FLAG_R);
	if(err)
		*err = _err;
	return val;
}
SysInfo_TypeDef SysInfoPar={
	.CamerParSet={
			.Number={
				.priv={
					.Value=&Number,
					.Listener=NULL,
					.ValuePath="0x0000",
					.SourceType = source_eerom,
					.CacheType = cache_cache,
					.ValueType = attr_u8
				},
				.Set = CommonSet,
				.Get = CommonGet
			},
			.Id={
				.priv={
						.Value=&Id,
						.Listener=NULL,
						.ValuePath="0x0001",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u16
				},
				.Set = CommonSet,
				.Get = CommonGet
			},
			.HardInterface={
				.priv={
						.Value=&HardInterface,
						.Listener=NULL,
						.ValuePath="0x0003",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u32
				},
				.Set = CommonSet,
				.Get = CommonGet
			},
			.Type={
				.priv={
						.Value=&Type,
						.Listener=NULL,
						.ValuePath="0x0007",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u32
				},
				.Set = CommonSet,
				.Get = CommonGet
			},
			.ImageSize={
				.priv={
						.Value=&ImageSize,
						.Listener=NULL,
						.ValuePath="0x000b",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u32
				},
				.Set = CommonSet,
				.Get = CommonGet
			},
			.ReportInterval={
				.priv={
						.Value=&ReportInterval,
						.Listener=NULL,
						.ValuePath="0x000e",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u16
				},
				.Set = CommonSet,
				.Get = CommonGet
			},
	},
	.PassageParSet={
			.PassNumber={
				.priv={
						.Value=&PassNumber,
						.Listener=NULL,
						.ValuePath="0x0010",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u8
				},
				.Set = CommonSet,
				.Get = CommonGet
			},
			.Identification={
				.priv={
						.Value=&Identification,
						.Listener=NULL,
						.ValuePath="0x0011",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u32
				},
				.Set = CommonSet,
				.Get = CommonGet
			},
			
			.Unit={
				.priv={
						.Value=&Unit,
						.Listener=NULL,
						.ValuePath="0x0012",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u32
				},
				.Set = CommonSet,
				.Get = CommonGet
			},
			.Precision={
				.priv={
						.Value=&Precision,
						.Listener=NULL,
						.ValuePath="0x0016",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_float
				},
				.Set = CommonSet,
				.Get = CommonGet
			},
			.AcquisitionSwitch={
				.priv={
						.Value=&AcquisitionSwitch,
						.Listener=NULL,
						.ValuePath="0x001a",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u32
				},
				.Set = CommonSet,
				.Get = CommonGet
			},
			.HardInterface={
				.priv={
						.Value=&HardInterface,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u32
				},
				.Set = CommonSet,
				.Get = CommonGet
			},
			.PowerOnTime={
				.priv={
						.Value=&PowerOnTime,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u8
				},
				.Set = CommonSet,
				.Get = CommonGet
			},
			.SamplingBaseValue={
				.priv={
						.Value=&SamplingBaseValue,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_float
				},
				.Set = CommonSet,
				.Get = CommonGet
			},
			.SamplingInterval={
				.priv={
						.Value=&SamplingInterval,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u16
				},
				.Set = CommonSet,
				.Get = CommonGet
			},
			.AlarmUpLimitValue={
				.priv={
						.Value=&AlarmUpLimitValue,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u16
				},
				.Set = CommonSet,
				.Get = CommonGet
			},
			.AlarmDownLimitValue={
				.priv={
						.Value=&AlarmDownLimitValue,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u16
				},
				.Set = CommonSet,
				.Get = CommonGet
			},
			.AlarmThreshold={
				.priv={
						.Value=&AlarmThreshold,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_float
				},
				.Set = CommonSet,
				.Get = CommonGet
			},
			.AlarmCaptureInterval={
				.priv={
						.Value=&AlarmCaptureInterval,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u16
				},
				.Set = CommonSet,
				.Get = CommonGet
			},
			.AlarmAssociatedRelay={
				.priv={
						.Value=&AlarmAssociatedRelay,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u32
				},
				.Set = CommonSet,
				.Get = CommonGet
			},
			.AlarmAssociatedDo={
				.priv={
						.Value=&AlarmAssociatedDo,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u32
				},
				.Set = CommonSet,
				.Get = CommonGet
			}
	},
	.TerminalParSet={
		.WorkingAgreement={
				.priv={
						.Value=&WorkingAgreement,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u32
				},
				.Set = CommonSet,
				.Get = CommonGet
		},
		.TelemetryStationAddress={
				.priv={
						.Value=TelemetryStationAddress,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_str32
				},
				.Set = CommonSet,
				.Get = CommonGet
		},
		.OperatingMode={
				.priv={
						.Value=&OperatingMode,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u32
				},
				.Set = CommonSet,
				.Get = CommonGet
		},
		.DebugLevel={
				.priv={
						.Value=&DebugLevel,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u32
				},
				.Set = CommonSet,
				.Get = CommonGet
		},
		.TimingInterval={
				.priv={
						.Value=&TimingInterval,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u16
				},
				.Set = CommonSet,
				.Get = CommonGet
		},
		.OverlapInterval={
				.priv={
						.Value=&OverlapInterval,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u16
				},
				.Set = CommonSet,
				.Get = CommonGet
		},
		.CommunicationStationNumber={
				.priv={
						.Value=&CommunicationStationNumber,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_str32
				},
				.Set = CommonSet,
				.Get = CommonGet
		},
		.UniformTimeInterval={
				.priv={
						.Value=&UniformTimeInterval,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u16
				},
				.Set = CommonSet,
				.Get = CommonGet
		}
	},
	.CenterParSet={
		.ApnDialNumber={
			.priv={
						.Value=&ApnDialNumber,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_str32
				},
				.Set = CommonSet,
				.Get = CommonGet
		},
		.APN={
			.priv={
						.Value=&APN,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_str32
				},
				.Set = CommonSet,
				.Get = CommonGet
		},
		.PppDialUsername={
			.priv={
						.Value=&PppDialUsername,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_str32
				},
				.Set = CommonSet,
				.Get = CommonGet
		},
		.PppDialPassword={
			.priv={
						.Value=&PppDialPassword,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_str32
				},
				.Set = CommonSet,
				.Get = CommonGet
		},
		.HeartbeatInterval={
			.priv={
						.Value=&HeartbeatInterval,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u16
				},
				.Set = CommonSet,
				.Get = CommonGet
		},
		.ReconnectionInterval={
			.priv={
						.Value=&ReconnectionInterval,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u16
				},
				.Set = CommonSet,
				.Get = CommonGet
		},
		.ServicesNumber={
			.priv={
						.Value=&ServicesNumber,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_u32
				},
				.Set = CommonSet,
				.Get = CommonGet
		},
	},
	.ServerParSet={
		.ServerNumber={
			.priv={
						.Value=&ServerNumber,
						.Listener=NULL,
						.ValuePath="0x001d",
						.SourceType = source_eerom,
						.CacheType = cache_cache,
						.ValueType = attr_str32
				},
				.Set = CommonSet,
				.Get = CommonGet
		},
		.ServerSite={
		.priv={
					.Value=&ServerSite,
					.Listener=NULL,
					.ValuePath="0x001d",
					.SourceType = source_eerom,
					.CacheType = cache_cache,
					.ValueType = attr_str32
			},
			.Set = CommonSet,
			.Get = CommonGet
	},
		.ServerType={
		.priv={
					.Value=&ServerType,
					.Listener=NULL,
					.ValuePath="0x001d",
					.SourceType = source_eerom,
					.CacheType = cache_cache,
					.ValueType = attr_u32
			},
			.Set = CommonSet,
			.Get = CommonGet
		},
		.serverAddress={
		.priv={
					.Value=&serverAddress,
					.Listener=NULL,
					.ValuePath="0x001d",
					.SourceType = source_eerom,
					.CacheType = cache_cache,
					.ValueType = attr_str32
			},
			.Set = CommonSet,
			.Get = CommonGet
		},
		.ServerPort={
		.priv={
					.Value=&ServerPort,
					.Listener=NULL,
					.ValuePath="0x001d",
					.SourceType = source_eerom,
					.CacheType = cache_cache,
					.ValueType = attr_u32
			},
			.Set = CommonSet,
			.Get = CommonGet
		},
	},
	.BeIDouParSet={
		.CommunicationID={
		.priv={
					.Value=&CommunicationID,
					.Listener=NULL,
					.ValuePath="0x001d",
					.SourceType = source_eerom,
					.CacheType = cache_cache,
					.ValueType = attr_str32
			},
			.Set = CommonSet,
			.Get = CommonGet
		},
		.Encoding={
		.priv={
					.Value=&Encoding,
					.Listener=NULL,
					.ValuePath="0x001d",
					.SourceType = source_eerom,
					.CacheType = cache_cache,
					.ValueType = attr_u32
			},
			.Set = CommonSet,
			.Get = CommonGet
		},
		.CommunicationInterface={
		.priv={
					.Value=&CommunicationInterface,
					.Listener=NULL,
					.ValuePath="0x001d",
					.SourceType = source_eerom,
					.CacheType = cache_cache,
					.ValueType = attr_u32
			},
			.Set = CommonSet,
			.Get = CommonGet
		},
		.CommunicationBaudRate={
		.priv={
					.Value=&CommunicationBaudRate,
					.Listener=NULL,
					.ValuePath="0x001d",
					.SourceType = source_eerom,
					.CacheType = cache_cache,
					.ValueType = attr_u32
			},
			.Set = CommonSet,
			.Get = CommonGet
		},
			.TargetingApplication={
		.priv={
					.Value=&TargetingApplication,
					.Listener=NULL,
					.ValuePath="0x001d",
					.SourceType = source_eerom,
					.CacheType = cache_cache,
					.ValueType = attr_u32
			},
			.Set = CommonSet,
			.Get = CommonGet
		},
		.CalibrationTimeInterval={
		.priv={
					.Value=&CalibrationTimeInterval,
					.Listener=NULL,
					.ValuePath="0x001d",
					.SourceType = source_eerom,
					.CacheType = cache_cache,
					.ValueType = attr_u8
			},
			.Set = CommonSet,
			.Get = CommonGet
		},
	},
	
};
  struct SIS_List* SerialReceivedList=0;
	
void VariableInit(void)
{
	SerialReceivedList=CreateSIS_List(20);
}