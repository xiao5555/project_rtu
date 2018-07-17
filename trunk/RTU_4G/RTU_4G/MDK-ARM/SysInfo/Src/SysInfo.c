#include "Inc/sysinfo.h"
#include <stdint.h>
#include <stdio.h>


	static float  RainData;
	static float  RainHour;
	static float  WaterData;
	static uint8_t  Number;//���
	static uint16_t Id;//ID
	static HARD_ENUM HardInterface;//Ӳ���ӿ�
	static TYPE_ENUM Type;//����
	static IMAGE_ENUM ImageSize;//ͼ���С
	static uint16_t ReportInterval;//�ϱ����
	static uint8_t PassNumber;//ͨ����
	static IDEN_ENUM  Identification;//��ʶ
	static UNIT_ENUM  Unit;//��λ
	static float  Precision;// ���� 
	static SWITCH_ENUM  AcquisitionSwitch;//�ɼ�����
	static HARD_ENUM HardInterface;// Ӳ���ӿ� 
	static uint8_t PowerOnTime;//�ϵ�ʱ�� 
	static float SamplingBaseValue;//������ֵ 
	static uint16_t SamplingInterval;//������� 
	static uint16_t AlarmUpLimitValue;//��������ֵ 
	static uint16_t AlarmDownLimitValue;//��������ֵ 
	static float AlarmThreshold;//������ֵ 
	static uint16_t AlarmCaptureInterval;//����ץ�ļ�� 
	static RELAY_ENUM AlarmAssociatedRelay;//���������̵��� 
	static DO_ENUM AlarmAssociatedDo;//��������DO
	static PROTOCOL_ENUM WorkingAgreement;//����Э��
	static MODE_ENUM OperatingMode;//����ģʽ
	static char TelemetryStationAddress[10];//ң��վ��ַ
	static LEVEL_ENUM DebugLevel;//���Եȼ�
	static uint16_t TimingInterval;//��ʱ�ϱ����
	static uint16_t OverlapInterval;//�ұ����
	static char CommunicationStationNumber[22];//ͨ��վʶ���
	static uint16_t UniformTimeInterval;//����ʱ�μ��
	static char ApnDialNumber[24];//APN���ź���
	static char APN[10];//APN
	static char PppDialUsername[24];//PPP �����û���
	static char PppDialPassword[24];//PPP ��������
	static uint16_t HeartbeatInterval;//�������
	static uint16_t ReconnectionInterval;//�������
	static SERVER_NUM_ENUM ServicesNumber; //�������
	static char ServerNumber;//���������?????????????????????????????????????????
	static char ServerSite[15];//������վַ
	static SERVER_TYPE_ENUM ServerType;//����������
	static char serverAddress[15];//��������ַ
	static uint32_t ServerPort;//�������˿�
	static char CommunicationID[10];//ͨ��ID
	static ENCODING_ENUM Encoding;//���뷽ʽ
	static COMMUNICATION_ENUM CommunicationInterface;//ͨ�Žӿ�
	static BAUDRATE_ENUM CommunicationBaudRate;//ͨ�Ų�����
	static POSITION_ENUM TargetingApplication;//��λ����
	static uint8_t  CalibrationTimeInterval;//Уʱ���

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
		*(void**)(val) = ReadAttr(c_this,&err);//����ʱ��ʵ�ʴ���valӦΪ����ָ��
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