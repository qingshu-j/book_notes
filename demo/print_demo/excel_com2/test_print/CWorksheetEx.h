// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ����

//#import "D:\\WPS Office\\12.1.0.17147\\office6\\wpsapiex.dll" no_namespace
// CWorksheetEx ��װ����

class CWorksheetEx : public COleDispatchDriver
{
public:
	CWorksheetEx() {} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CWorksheetEx(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CWorksheetEx(const CWorksheetEx& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// WorksheetEx ����
public:
	LPDISPATCH InsertCamera(LPDISPATCH SourceRange, float Left, float Top)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_DISPATCH VTS_R4 VTS_R4;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, SourceRange, Left, Top);
		return result;
	}
	void SetCircleInvalidCell(BOOL IsSetCircle)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, IsSetCircle);
	}
	BOOL get_IsMarkCircles()
	{
		BOOL result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}

	// WorksheetEx ����
public:

};
