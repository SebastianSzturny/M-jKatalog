#include <Windows.h>
#include <stdio.h>
#include "res.h"
#include "main.h"

HINSTANCE hInst;

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM IParam)
{
  
  switch (uMsg)
  {
  
    case WM_COMMAND:
      switch (HIWORD(wParam))
      {
      
      case BN_CLICKED:
        switch (LOWORD(wParam))
        {
       
        case IDC_BUTTON1:
          
         
          HWND hwndEditBox = GetDlgItem(hwndDlg, IDC_EDIT1);
          int iTextLength = GetWindowTextLength(hwndEditBox);
          CHAR szText[500];
          GetWindowText(hwndEditBox, szText, iTextLength + 1);
         
          
          return TRUE;
        }

      
      }
      return FALSE;

    case WM_PAINT:
      HDC hDC;
      hDC = GetDC(hwndDlg);
      HBITMAP hBitmap;
      hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));

      HDC hDCBitmap;;
      hDCBitmap = CreateCompatibleDC(hDC);
      SelectObject(hDCBitmap, hBitmap);
      BitBlt(hDC, 0, 0, 900, 400, hDCBitmap, 0, 0, SRCCOPY);
      DeleteDC(hDCBitmap);
      DeleteObject(hBitmap);

      SelectObject(hDC, GetStockObject(ANSI_VAR_FONT));
      SetTextColor(hDC, RGB(255, 0, 0));
      TextOut(hDC, 0, 0, TEXT("Text output to client area."), 27);
      ReleaseDC(hwndDlg, hDC);
      break;

   
  case WM_CLOSE:
    DestroyWindow(hwndDlg);
      PostQuitMessage(0);
    return TRUE;
  }
  return FALSE;
}

int WINAPI WinMain(HINSTANCE hlnstance , HINSTANCE hPrevinstance , PSTR szCmdLine , int iCmdShow)
{
 
  hInst = hlnstance;

  HWND hwndMainWindow = CreateDialog(hlnstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);
  
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}