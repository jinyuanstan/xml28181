// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� XMLPARSER_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// XMLPARSER_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#include "stdafx.h"
#include <string>
#include "types.h"

// �����Ǵ� XmlParser.dll ������

class CXmlParser {
public:
	CXmlParser(void);
	// TODO: �ڴ�������ķ�����
	std::string CreateMessage(const MessageCommon* common, const void* detail);
private:
	void* CreateCommon(const MessageCommon* common, void** reflect);
	void* BuildDetail(void* root, const void* detail, void* reflect);
};