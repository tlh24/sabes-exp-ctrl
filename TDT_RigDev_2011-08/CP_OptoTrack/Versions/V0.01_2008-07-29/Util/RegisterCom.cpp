#include <objbase.h>
BOOL AddKey(const char* pszPath, const char* szSubkey, const char* szValue);
BOOL SetKey(const char* szKey, const char* szNamedValue, const char* szValue);
void GuidToStr(REFCLSID clsid, char* szCLSID, int length);
LONG DeleteKey(HKEY hKeyParent, const char* szKeyChild);


//--------------------------------------------------------------------------
void GuidToStr(REFCLSID clsid, char* szCLSID, int length)
{
	LPOLESTR wszCLSID = NULL;
	HRESULT hr = StringFromCLSID(clsid, &wszCLSID);
	wcstombs(szCLSID, wszCLSID, length);
	CoTaskMemFree(wszCLSID);
}

//--------------------------------------------------------------------------
LONG DeleteKey(HKEY hKeyParent, const char* lpszKeyChild)
{
	HKEY hKeyChild;
	LONG lRes = RegOpenKeyEx(hKeyParent, lpszKeyChild, 0, KEY_ALL_ACCESS, &hKeyChild);
	if(lRes != ERROR_SUCCESS) return lRes;
	FILETIME time;
	char szBuffer[256];
	DWORD dwSize = 256;
	while(RegEnumKeyEx(hKeyChild, 0, szBuffer, &dwSize, NULL, NULL, NULL, &time) == S_OK)
	{
		lRes = DeleteKey(hKeyChild, szBuffer);
		if(lRes != ERROR_SUCCESS)
		{
			RegCloseKey(hKeyChild);
			return lRes;
		}
		dwSize = 256;
	}
	RegCloseKey(hKeyChild);
	return RegDeleteKey(hKeyParent, lpszKeyChild);
}

//--------------------------------------------------------------------------
BOOL AddKey(const char* szKey, const char* szSubkey, const char* szValue)
{
	HKEY hKey;
	char szKeyBuf[1024];
	strcpy(szKeyBuf, szKey);
	if(szSubkey != NULL)
	{
		strcat(szKeyBuf, "\\");
		strcat(szKeyBuf, szSubkey );
	}
	long lResult = RegCreateKeyEx(HKEY_CLASSES_ROOT, szKeyBuf, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	if(lResult != ERROR_SUCCESS) return FALSE;
	if(szValue != NULL)
		RegSetValueEx(hKey, NULL, 0, REG_SZ, (BYTE *)szValue, strlen(szValue)+1);
	RegCloseKey(hKey);
	return TRUE;
}

//--------------------------------------------------------------------------
BOOL SetKey(const char* szKey, const char* szNamedValue, const char* szValue)
{
	HKEY hKey;
	char szKeyBuf[1024];
	strcpy(szKeyBuf, szKey);
	long lResult = RegOpenKeyEx(HKEY_CLASSES_ROOT, szKeyBuf, 0, KEY_SET_VALUE, &hKey);
	if(lResult != ERROR_SUCCESS) return FALSE;
	if(szValue != NULL)
		RegSetValueEx(hKey, szNamedValue, 0, REG_SZ, (BYTE*)szValue, strlen(szValue)+1);
	RegCloseKey(hKey);
	return TRUE;
}


//==========================================================================
HRESULT g_RegisterServer(const char* szModuleName, REFCLSID clsid, const char* szFriendlyName,
   const char* szVerIndProgID, const char* szProgID, const char* szThreadingModel)
{
	char szModule[512];
	HMODULE hModule = GetModuleHandle(szModuleName);
	DWORD dwResult = GetModuleFileName(hModule, szModule, sizeof(szModule)/sizeof(char));
	char szCLSID[39];
	GuidToStr(clsid, szCLSID, sizeof(szCLSID));
	char szKey[64];
	strcpy(szKey, "CLSID\\");
	strcat(szKey, szCLSID);
	AddKey(szKey, NULL, szFriendlyName);
	if(strstr(szModuleName, ".exe") == NULL)
	{
		AddKey(szKey, "InprocServer32", szModule);
		char szInproc[64];
		strcpy(szInproc, szKey);
		strcat(szInproc, "\\InprocServer32");
		SetKey(szInproc, "ThreadingModel", szThreadingModel);
	}
	else
		AddKey(szKey, "LocalServer32", szModule);
	AddKey(szKey, "ProgID", szProgID);
	AddKey(szKey, "VersionIndependentProgID", szVerIndProgID);
	AddKey(szVerIndProgID, NULL, szFriendlyName);
	AddKey(szVerIndProgID, "CLSID", szCLSID);
	AddKey(szVerIndProgID, "CurVer", szProgID);
	AddKey(szProgID, NULL, szFriendlyName);
	AddKey(szProgID, "CLSID", szCLSID);
	return S_OK;
}

//==========================================================================
LONG g_UnregisterServer(REFCLSID clsid, const char* szVerIndProgID, const char* szProgID)
{
	char szCLSID[39];
	GuidToStr(clsid, szCLSID, sizeof(szCLSID));
	char szKey[64];
	strcpy(szKey, "CLSID\\");
	strcat(szKey, szCLSID);
	LONG lResult = DeleteKey(HKEY_CLASSES_ROOT, szKey);
	lResult = DeleteKey(HKEY_CLASSES_ROOT, szVerIndProgID);
	lResult = DeleteKey(HKEY_CLASSES_ROOT, szProgID);
	return S_OK;
}
