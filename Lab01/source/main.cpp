#include <Windows.h>
#include <cstdio>
#include <iostream>
int WINAPI WinMain(HINSTANCE hlnstance , HINSTANCE hPrevinstance , PSTR szCmdLine , int iCmdShow)
{
  char tab[200];
  int a = 40;
  int b = 1;
  MessageBox(0, "Wybierz liczbe 1-40", "Aplikacja", MB_OK);

  sprintf(tab,"Mniejsza od ");
  int iRetKey = MessageBox(0, "Mniejsza od 20?", "Aplikacja", MB_YESNO);
  MessageBox(0, tab, "Aplikacja", MB_OK);

  
  
  return 0;
}