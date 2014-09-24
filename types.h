#ifndef __TYPES_H__
#define __TYPES_H__

#define DeviceCode int

typedef enum {
	Query,
	Notify,
	Response
} XMLType;

typedef struct {
	XMLType Type;
	char* CmdType;
	char* SN;
	char* DeviceID;
	char* Result;
} MessageCommon;

/** J.6 */
typedef struct {
	char* ControlPriority;
} ControlInfo;

typedef struct {
	char* PTZCmd;
	char* RecordCmd;
	char* GuardCmd;
	char* AlarmCmd;
	ControlInfo Info;
}PTZControl;

/** J.7 */

/** J.8 */
typedef struct {
	char* AlarmPriority;
	char* AlarmMethod;
	char* AlarmTime;
	char* AlarmDescription;
	float* Longitude;
	float* Latitude;
} AlarmNotify;

/** J.9 */
typedef struct {
	char* StartTime;
	char* EmdTime;
} CatalogQuery;

typedef struct {
	char* DeviceID;
	char* Name;
	char* Manufacture;
	char* Model;
	char* Owner;
	char* CivilCode;
	char* Block;
	char* Address;
	char* Parental;
	char* ParentID;
	char* SaftyWay;
	char* RegisterWay;
	char* CertNum;
	char* Certifiable;
	char* ErrCode;
	char* EndTime;
	char* Secrecy;
	char* IPAddress;
	char* Port;
	char* Password;
	char* Status;
	float Longitude;
	float Latitude;
} CatalogItem;

typedef struct {
	char* SumNum;
	char* DeviceList;
	CatalogItem **Item;
} CatalogResponse;

/** J.10 */
typedef struct {
	char* DeviceType;
	char* Manufacturer;
	char* Model;
	char* Firmware;
	char* MaxCamera;
	char* MaxAlarm;
} DeviceInfoResponse;

/** J.11 */
typedef struct {
	char* DeviceID;
	char* DutyStatus;
} DeviceStatusItem;

typedef struct {
	char* Online;
	char* Status;
	char* Encode;
	char* Record;
	char* DeviceTime;
	char* Alarmstatus;
	DeviceStatusItem **Item;
} DeviceStatusResponse;

/** J.12 */
typedef struct {
	char* Status;
} KeepaliveNotify;

/** J.13 */
typedef struct {
	char* StartTime;
	char* EndTime;
	char* FilePath;
	char* Address;
	char* Secrecy;
	char* Type;
	char* RecorderID;
} RecordInfoQuery;

typedef struct {
	char* DeviceID;
	char* Name;
	char* FilePath;
	char* Address;
	char* StartTime;
	char* EndTime;
	char* Secrecy;
	char* Type;
	char* RecorderID;
} RecordInfoItem;

typedef struct {
	char* Name;
	char* SumNum;
	char* RecordList;
	RecordInfoItem **Item;
} RecordInfoResponse;

/** J.18 */
typedef struct {
	char* StartAlarmPriority;
	char* EndAlarmPriority;
	char* AlarmMethod;
	char* StartTime;
	char* EmdTime;
} AlarmQuery;

/** A.2 Boardcast */
typedef struct {
	char* SourceID;
	char* TargetID;
} BroadcastQuery;

/** J.22 */
typedef struct {
	char* Status;
	char* SumNum;
	char* DeviceList;
	CatalogItem **Item;
} CatalogNotify;

#endif
