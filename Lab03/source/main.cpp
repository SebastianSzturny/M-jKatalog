#include <Windows.h>
#include <Windowsx.h>
#include <stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include "res.h"
#include "main.h"

#define ID_TIMER_MUCHA 2018

HINSTANCE hInst;
int iMuchaX;
int iMuchaY;

int iMuchaWidth;
int iMuchaHeight;

bool bIsMuchaZywa;

int iMuchaPredkoscX;
int iMuchaPredkoscY;

int iMuchaAngle;
int iMuchaPredkosc;

double dt = 0.1;

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

  switch (uMsg)
  {
  case WM_INITDIALOG:
    srand(time(NULL));
    iMuchaX = rand() % 600;
    iMuchaY = rand() % 400;
    iMuchaWidth = 100;
    iMuchaHeight = 100;

    bIsMuchaZywa = true;

    iMuchaAngle = 21; // kierunek o stopni
    iMuchaPredkosc = 20; //pkt na sek



    return TRUE;

  case WM_COMMAND:
    switch (HIWORD(wParam))
    {

    }
    return FALSE;

 

  case WM_PAINT:
  {
    HDC hDC;
    hDC = GetDC(hwndDlg);
    HBITMAP hBitmap;
    hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3)); // T£O

    HDC hDC1;
    hDC1 = GetDC(hwndDlg);
    HBITMAP hBitmap1;
    hBitmap1 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1)); // ¯YWA MRÓWKA

    HDC hDC2;
    hDC2 = GetDC(hwndDlg);
    HBITMAP hBitmap2;
    hBitmap2 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2)); // TRUP MRÓWKA

    HDC hDCBitmap, hDCBitmap1;// hDCBitmap2;
    
    hDCBitmap = CreateCompatibleDC(hDC);
    SelectObject(hDCBitmap, hBitmap);
    hDCBitmap1 = CreateCompatibleDC(hDC1);
    SelectObject(hDCBitmap1, hBitmap1);
    //hDCBitmap2 = CreateCompatibleDC(hDC2);
    //SelectObject(hDCBitmap2, hBitmap2);
    SelectObject(hDC, GetStockObject(NULL_PEN));
    
    Rectangle(hDC, iMuchaX - 20, iMuchaY - 20, iMuchaX + iMuchaWidth + 20, iMuchaY + iMuchaHeight + 20);
    Rectangle(hDC,0,0,1000,1000);
    RECT prostokat;
    GetWindowRect(hwndDlg, &prostokat);

    BITMAP bmInfo, bmInfo1, bmInfo2;                              //
    GetObject(hBitmap, sizeof(bmInfo), &bmInfo);                  // POBIERANIE INFO O OBRAZACH
    GetObject(hBitmap1, sizeof(bmInfo1), &bmInfo1);               //
    GetObject(hBitmap2, sizeof(bmInfo2), &bmInfo2);               //

    int width = prostokat.right - prostokat.left;
    int height = prostokat.bottom - prostokat.top;

    
    //StretchBlt(hDC, 0, 0, width, height, hDCBitmap, 0, 0, bmInfo.bmWidth, bmInfo.bmHeight, SRCCOPY);


    if (bIsMuchaZywa)
    {
      SelectObject(hDCBitmap1, hBitmap1);
    }
    else
    {
      SelectObject(hDCBitmap1, hBitmap2);
    }
    
    BitBlt(hDC1, iMuchaX, iMuchaY, bmInfo1.bmWidth, bmInfo1.bmHeight, hDCBitmap1, 0, 0, SRCCOPY);

    DeleteDC(hDCBitmap);
    DeleteObject(hBitmap);
    DeleteObject(hBitmap1);
    DeleteObject(hBitmap2);
    SelectObject(hDC, GetStockObject(ANSI_VAR_FONT));
    SetTextColor(hDC, RGB(255, 0, 0));
    TextOut(hDC, 0, 0, TEXT("Text output to client area."), 27);
    ReleaseDC(hwndDlg, hDC);
    break;
  }

  case WM_LBUTTONDOWN:
  {
    int iMouseX = GET_X_LPARAM(lParam);
    int iMouseY = GET_Y_LPARAM(lParam);
    if ((iMouseX > iMuchaX) &&(iMouseX < iMuchaX + iMuchaWidth) && (iMouseY > iMuchaY) && (iMouseY < iMuchaY + iMuchaHeight))
    {
      bIsMuchaZywa = false;
    }
  }
  RedrawWindow(hwndDlg, NULL, NULL, RDW_INVALIDATE);
  return TRUE;

  case WM_TIMER:
    switch (wParam) {
      case ID_TIMER_MUCHA:
        if (bIsMuchaZywa) {
          iMuchaX += iMuchaPredkosc * cos(iMuchaAngle*3.1415 / 180)*30*dt;
          iMuchaY += iMuchaPredkosc * sin(iMuchaAngle*3.1415 / 180)*30*dt;
          //Bound
          if (iMuchaX > 600 - iMuchaWidth) iMuchaAngle =(iMuchaAngle+180)%360;
          if (iMuchaX < 0) iMuchaAngle = (iMuchaAngle + 180)%360;
          if (iMuchaY > 400 - iMuchaHeight) iMuchaAngle = (iMuchaAngle + 180)%360;
          if (iMuchaY < 0) iMuchaAngle = (iMuchaAngle + 180)%360;
          
          RedrawWindow(hwndDlg, NULL, NULL, RDW_INVALIDATE);
        }
        break;
    }
    return TRUE;

  case WM_CLOSE:
    DestroyWindow(hwndDlg);
    PostQuitMessage(0);
    return TRUE;
  }
  return FALSE;
}

int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevinstance, PSTR szCmdLine, int iCmdShow)
{

  hInst = hlnstance;
  HBRUSH brush = CreateSolidBrush(RGB(0,0,255));


  HWND hwndMainWindow = CreateDialog(hlnstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);

  SetTimer(hwndMainWindow, ID_TIMER_MUCHA, dt*1000, NULL);

  ShowWindow(hwndMainWindow, iCmdShow);

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}