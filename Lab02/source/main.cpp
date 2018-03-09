#include <Windows.h>
#include "res.h"
int WINAPI WinMain(HINSTANCE hlnstance , HINSTANCE hPrevinstance , PSTR szCmdLine , int iCmdShow)
{
 

  HWND hwndMainWindow = CreateDialog(hlnstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, NULL);
  ShowWindow(hwndMainWindow, iCmdShow);
  
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}