HRESULT g_RegisterServer(const char* szModuleName, REFCLSID clsid, 
                       const char* szFriendlyName, const char* szVerIndProgID, 
                       const char* szProgID, const char* szThreadingModel);
LONG g_UnregisterServer(REFCLSID clsid, const char* szVerIndProgID, const char* szProgID);

