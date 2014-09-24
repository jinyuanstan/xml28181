// XmlParser.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "XmlParser.h"
#include "tinyxml.h"

typedef enum {
	R_String = 0,
	R_Container,
	R_Wrapper,
	R_Unknown
} XMLReflectType;

typedef struct xmlReflect{
	int index;
	int parent;
	std::string name;
	XMLReflectType  type;
	int   offset;
	struct xmlReflect* reflect;
} XMLReflect;

const XMLReflect ControlInfoReflect[] = {
	{1, 0, "ControlPriority", R_String, offsetof(ControlInfo, ControlPriority)},
	{-1, 0, "", R_Unknown, 0}
};

const XMLReflect PTZControlReflect[] = {
	{1, 0, "PTZCmd", R_String, offsetof(PTZControl, PTZCmd), NULL},
	{2, 0, "RecordCmd", R_String, offsetof(PTZControl, RecordCmd), NULL},
	{3, 0, "GuardCmd", R_String, offsetof(PTZControl, GuardCmd), NULL},
	{4, 0, "AlarmCmd", R_String, offsetof(PTZControl, AlarmCmd), NULL},
	{5, 0, "Info", R_Wrapper, offsetof(PTZControl, Info), NULL},
	{-1, 0, "", R_Unknown, 0}
};

const XMLReflect AlarmNotifyReflect[] = {
	{1, 0, "AlarmPriority", R_String, offsetof(AlarmNotify, AlarmPriority), NULL},
	{2, 0, "AlarmMethod", R_String, offsetof(AlarmNotify, AlarmMethod), NULL},
	{3, 0, "AlarmTime", R_String, offsetof(AlarmNotify, AlarmTime), NULL},
	{4, 0, "AlarmDescription", R_String, offsetof(AlarmNotify, AlarmDescription), NULL},
	{5, 0, "Longitude", R_String, offsetof(AlarmNotify, Longitude), NULL},
	{6, 0, "Latitude", R_String, offsetof(AlarmNotify, Latitude), NULL},
	{-1, 0, "", R_Unknown, 0}
};

const XMLReflect CatalogQueryReflect[] = {
	{1, 0, "StartTime", R_String, offsetof(CatalogQuery, StartTime), NULL},
	{2, 0, "EmdTime", R_String, offsetof(CatalogQuery, EmdTime), NULL},
	{-1, 0, "", R_Unknown, 0}
};

const XMLReflect CatalogItemReflect[] = {
	{1, 0, "DeviceID", R_String, offsetof(CatalogItem, DeviceID), NULL},
	{2, 0, "Name", R_String, offsetof(CatalogItem, Name), NULL},
	{3, 0, "Manufacture", R_String, offsetof(CatalogItem, Manufacture), NULL},
	{4, 0, "Model", R_String, offsetof(CatalogItem, Model), NULL},
	{5, 0, "Owner", R_String, offsetof(CatalogItem, Owner), NULL},
	{6, 0, "CivilCode", R_String, offsetof(CatalogItem, CivilCode), NULL},
	{7, 0, "Block", R_String, offsetof(CatalogItem, Block), NULL},
	{8, 0, "Address", R_String, offsetof(CatalogItem, Address), NULL},
	{9, 0, "Parental", R_String, offsetof(CatalogItem, Parental), NULL},
	{10,0, "ParentID", R_String, offsetof(CatalogItem, ParentID), NULL},
	{11,0, "SaftyWay", R_String, offsetof(CatalogItem, SaftyWay), NULL},
	{12,0, "RegisterWay", R_String, offsetof(CatalogItem, RegisterWay), NULL},
	{13,0, "CertNum", R_String, offsetof(CatalogItem, CertNum), NULL},
	{14,0, "Certifiable", R_String, offsetof(CatalogItem, Certifiable), NULL},
	{15,0, "ErrCode", R_String, offsetof(CatalogItem, ErrCode), NULL},
	{16,0, "EndTime", R_String, offsetof(CatalogItem, EndTime), NULL},
	{17,0, "Secrecy", R_String, offsetof(CatalogItem, Secrecy), NULL},
	{18,0, "IPAddress", R_String, offsetof(CatalogItem, IPAddress), NULL},
	{19,0, "Port", R_String, offsetof(CatalogItem, Port), NULL},
	{20,0, "Password", R_String, offsetof(CatalogItem, Password), NULL},
	{21,0, "Status", R_String, offsetof(CatalogItem, Status), NULL},
	{22,0, "Longitude", R_String, offsetof(CatalogItem, Longitude), NULL},
	{23,0, "Latitude", R_String, offsetof(CatalogItem, Latitude), NULL},
	{-1, 0, "", R_Unknown, 0}
};

const XMLReflect CatalogResponseReflect[] = {
	{1, 0, "SumNum", R_String, offsetof(CatalogResponse, SumNum), NULL},
	{2, 0, "DeviceList", R_Container, offsetof(CatalogResponse, DeviceList), NULL},
	{3, 2, "Item", R_Wrapper, offsetof(CatalogResponse, Item), (XMLReflect*)CatalogItemReflect},
	{-1, 0, "", R_Unknown, 0}
};

const XMLReflect DeviceInfoResponseReflect[] = {
	{1, 0, "DeviceType", R_String, offsetof(DeviceInfoResponse, DeviceType), NULL},
	{2, 0, "Manufacturer", R_String, offsetof(DeviceInfoResponse, Manufacturer), NULL},
	{3, 0, "Model", R_String, offsetof(DeviceInfoResponse, Model), NULL},
	{4, 0, "Firmware", R_String, offsetof(DeviceInfoResponse, Firmware), NULL},
	{5, 0, "MaxCamera", R_String, offsetof(DeviceInfoResponse, MaxCamera), NULL},
	{6, 0, "MaxAlarm", R_String, offsetof(DeviceInfoResponse, MaxAlarm), NULL},
	{-1, 0, "", R_Unknown, 0}
};

const XMLReflect DeviceStatusItemReflect[] = {
	{1, 0, "DeviceID", R_String, offsetof(DeviceStatusItem, DeviceID), NULL},
	{2, 0, "DutyStatus", R_String, offsetof(DeviceStatusItem, DutyStatus), NULL},
	{-1, 0, "", R_Unknown, 0}
};

const XMLReflect DeviceStatusResponseReflect[] = {
	{1, 0, "Online", R_String, offsetof(DeviceStatusResponse, Online), NULL},
	{2, 0, "Status", R_String, offsetof(DeviceStatusResponse, Status), NULL},
	{3, 0, "Encode", R_String, offsetof(DeviceStatusResponse, Encode), NULL},
	{4, 0, "Record", R_String, offsetof(DeviceStatusResponse, Record), NULL},
	{5, 0, "Alarmstatus", R_Container, offsetof(DeviceStatusResponse, Alarmstatus), NULL},
	{6, 5, "Item", R_Wrapper, offsetof(DeviceStatusResponse, Item), (XMLReflect*)DeviceStatusItemReflect},
	{-1, 0, "", R_Unknown, 0}
};

const XMLReflect KeepaliveNotifyReflect[] = {
	{1, 0, "Status", R_String, offsetof(KeepaliveNotify, Status), NULL},
	{-1, 0, "", R_Unknown, 0}
};

const XMLReflect RecordInfoQueryReflect[] = {
	{1, 0, "StartTime", R_String, offsetof(RecordInfoQuery, StartTime), NULL},
	{2, 0, "EndTime", R_String, offsetof(RecordInfoQuery, EndTime), NULL},
	{3, 0, "FilePath", R_String, offsetof(RecordInfoQuery, FilePath), NULL},
	{4, 0, "Address", R_String, offsetof(RecordInfoQuery, Address), NULL},
	{5, 0, "Secrecy", R_String, offsetof(RecordInfoQuery, Secrecy), NULL},
	{6, 0, "Type", R_String, offsetof(RecordInfoQuery, Type), NULL},
	{7, 0, "RecorderID", R_String, offsetof(RecordInfoQuery, RecorderID), NULL},
	{-1, 0, "", R_Unknown, 0}
};

const XMLReflect RecordInfoItemReflect[] = {
	{1, 0, "DeviceID", R_String, offsetof(RecordInfoItem, DeviceID), NULL},
	{2, 0, "Name", R_String, offsetof(RecordInfoItem, Name), NULL},
	{3, 0, "FilePath", R_String, offsetof(RecordInfoItem, FilePath), NULL},
	{4, 0, "Address", R_String, offsetof(RecordInfoItem, Address), NULL},
	{5, 0, "StartTime", R_String, offsetof(RecordInfoItem, StartTime), NULL},
	{6, 0, "EndTime", R_String, offsetof(RecordInfoItem, EndTime), NULL},
	{7, 0, "Secrecy", R_String, offsetof(RecordInfoItem, Secrecy), NULL},
	{8, 0, "Type", R_String, offsetof(RecordInfoItem, Type), NULL},
	{9, 0, "RecorderID", R_String, offsetof(RecordInfoItem, RecorderID), NULL},
	{-1, 0, "", R_Unknown, 0}
};

const XMLReflect RecordInfoResponseReflect[] = {
	{1, 0, "Name", R_String, offsetof(RecordInfoResponse, Name), NULL},
	{2, 0, "SumNum", R_String, offsetof(RecordInfoResponse, SumNum), NULL},
	{3, 0, "RecordList", R_Container, offsetof(RecordInfoResponse, RecordList), NULL},
	{4, 3, "Item", R_Wrapper, offsetof(RecordInfoResponse, Item), (XMLReflect*)RecordInfoItemReflect},
	{-1, 0, "", R_Unknown, 0}
};

const XMLReflect AlarmQueryReflect[] = {
	{1, 0, "StartAlarmPriority", R_String, offsetof(AlarmQuery, StartAlarmPriority), NULL},
	{2, 0, "EndAlarmPriority", R_String, offsetof(AlarmQuery, EndAlarmPriority), NULL},
	{3, 0, "AlarmMethod", R_String, offsetof(AlarmQuery, AlarmMethod), NULL},
	{4, 0, "StartTime", R_String, offsetof(AlarmQuery, StartTime), NULL},
	{5, 0, "EmdTime", R_String, offsetof(AlarmQuery, EmdTime), NULL},
	{-1, 0, "", R_Unknown, 0}
};

const XMLReflect BroadcastQueryReslect[] = {
	{1, 0, "SourceID", R_String, offsetof(BroadcastQuery, SourceID), NULL},
	{1, 0, "TargetID", R_String, offsetof(BroadcastQuery, TargetID), NULL}
};


// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 XmlParser.h
CXmlParser::CXmlParser()
{
	AlarmQuery alarm = {"0","1","2","lll","mmm"};
	int p = sizeof(AlarmQueryReflect)/sizeof(XMLReflect);

	for (int i = 0 ; i < p ; i++)
	{
		if (AlarmQueryReflect[i].type == R_String) {
			int k = *(int*)((int)&alarm + AlarmQueryReflect[i].offset);
			int j = 0;
		} 
		
	}


	MessageCommon req = {
		Query,
		"DeviceControl",
		"111",
		"1234567"
	};

	MessageCommon res = {
		Response,
		"RecordInfo",
		"1111",
		"2222",
		""
	};

	RecordInfoResponse info;
	info.Name = "Camera1";
	info.SumNum = "100";
	info.RecordList = "2";
	info.Item = new RecordInfoItem*[2];
	info.Item[0] = new RecordInfoItem;
	info.Item[0]->DeviceID = "64010000001310000001";
	info.Item[0]->Name = "Camera1";
	info.Item[0]->FilePath = "64010000002100000001";
	info.Item[0]->Address = "Address 1";
	info.Item[0]->StartTime = "2010-11-12T10:10:00";
	info.Item[0]->EndTime = "2010-11-12T10:20:00";
	info.Item[0]->Secrecy = "0";
	info.Item[0]->Type = "time";
	info.Item[0]->RecorderID = "64010000003000000001";

	info.Item[1] = new RecordInfoItem;
	info.Item[1]->DeviceID = "64010000001310000001";
	info.Item[1]->Name = "Camera1";
	info.Item[1]->FilePath = "64010000002100000001";
	info.Item[1]->Address = "Address 1";
	info.Item[1]->StartTime = "2010-11-12T10:10:00";
	info.Item[1]->EndTime = "2010-11-12T10:20:00";
	info.Item[1]->Secrecy = "0";
	info.Item[1]->Type = "time";
	info.Item[1]->RecorderID = "64010000003000000001";

	
	std::string result = CreateMessage((MessageCommon*)&res, &info);

	printf("%s", result.c_str());
	
	return;
}

void* CXmlParser::BuildDetail(void* root, const void* detail, void* reflect)
{
	XMLReflect* r = (XMLReflect*)reflect;
	TiXmlElement  *Root = (TiXmlElement  *)root;
	int size = 0;

	while(r->index > 0)
	{
		size++;
		r = (XMLReflect*)((int)r + sizeof(XMLReflect));
	}

	r = (XMLReflect*)reflect;

	for (int i = 0 ; i < size ; i++)
	{
		if (r[i].type == R_String) {
			Root->LinkEndChild(new TiXmlElement(r[i].name.c_str()))->LinkEndChild(new TiXmlText(*(char**)((int)detail + r[i].offset)));
		} 

		if (r[i].type == R_Container) {
			TiXmlElement  *Sub = new TiXmlElement(r[i].name.c_str());

			int asize = atoi(*(char**)((int)detail + r[i].offset));
			Sub->SetAttribute("NUM", asize);
			Root->LinkEndChild(Sub);
			
			for (int j = 0 ; j < size; j++) {
				if (r[j].type == R_Wrapper && r[j].parent == r[i].index) {
					for (int k = 0; k < asize; k++) {
						TiXmlElement  *Resub = new TiXmlElement(r[j].name.c_str());
						Sub->LinkEndChild(Resub); 
						BuildDetail((void*)Resub, 
							(void*)(*(int*)(*(int*)((int)detail + r[j].offset) + sizeof(void*) * k)), 
							(void*)r[j].reflect);
					}
				}
			}
			
		}

		if (r[i].type == R_Wrapper && r[i].parent == 0) {
			TiXmlElement  *Sub = new TiXmlElement(r[i].name.c_str());
			Root->LinkEndChild(Sub);
			BuildDetail((void*)Sub, (void*)(*(int*)((int)detail + r[i].offset)), (void*)r[i].reflect);
		}
		
	}

	return (void*)Root;
}

void* CXmlParser::CreateCommon(const MessageCommon* common, void** reflect)
{

	MessageCommon *req = (MessageCommon*)common;
	TiXmlDocument *xml = new TiXmlDocument();
	TiXmlElement  *Root;

	*reflect = NULL;
	

	switch(req->Type) 
	{
		case Query:
			if (!strcmp(req->CmdType, "DeviceControl")) {
				*reflect = (void*)PTZControlReflect;
			}
			if (!strcmp(req->CmdType, "Catalog")) {
				*reflect = (void*)CatalogQueryReflect;
			}
			if (!strcmp(req->CmdType, "RecordInfo")) {
				*reflect = (void*)RecordInfoQueryReflect;
			}
			if (!strcmp(req->CmdType, "AlarmQuery")) {
				*reflect = (void*)AlarmQueryReflect;
			}
			if (!strcmp(req->CmdType, "Broadcast")) {
				*reflect = (void*)BroadcastQueryReslect;			}
			Root = new TiXmlElement("Query");
			break;
		case Notify:
			if (!strcmp(req->CmdType, "Alarm")) {
				*reflect = (void*)AlarmNotifyReflect;
			}
			if (!strcmp(req->CmdType, "Keepalive")) {
				*reflect = (void*)KeepaliveNotifyReflect;
			}
			Root = new TiXmlElement("Notify");
			break;
		case Response:
			if (!strcmp(req->CmdType, "Catalog")) {
				*reflect = (void*)CatalogResponseReflect;
			}
			if (!strcmp(req->CmdType, "DeviceInfo")) {
				*reflect = (void*)DeviceInfoResponseReflect;
			}
			if (!strcmp(req->CmdType, "DeviceStatus")) {
				*reflect = (void*)DeviceStatusResponseReflect;
			}
			if (!strcmp(req->CmdType, "RecordInfo")) {
				*reflect = (void*)RecordInfoResponseReflect;
			}
			Root = new TiXmlElement("Response");
			break;
		default:
			delete xml;
			return NULL;
	}

	TiXmlNode* root = xml->LinkEndChild(Root);

	root->LinkEndChild(new TiXmlElement("CmdType"))->LinkEndChild(new TiXmlText(req->CmdType));
	root->LinkEndChild(new TiXmlElement("SN"))->LinkEndChild(new TiXmlText(req->SN));
	root->LinkEndChild(new TiXmlElement("DeviceID"))->LinkEndChild(new TiXmlText(req->DeviceID));
	if (req->Type == Response) {
		if ( ((MessageCommon*)req)->Result != "") {
			root->LinkEndChild(new TiXmlElement("Result"))->LinkEndChild(new TiXmlText(((MessageCommon*)req)->Result));
		}
	}

	return (void*)xml;

}	

std::string CXmlParser::CreateMessage(const MessageCommon* common, const void* detail)
{
	if (!common || !detail) { return ""; }
	
	XMLReflect *reflect;
	
	TiXmlDocument* xml = (TiXmlDocument*)CreateCommon(common, (void**)&reflect);
	if (!xml) {
		return "";
	}

	if (reflect) {
		BuildDetail(xml->FirstChildElement(), detail, reflect);
	}
	
	TiXmlPrinter printer;
	xml->Accept(&printer);

	return printer.CStr();
}

