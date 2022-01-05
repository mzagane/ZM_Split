/*******************************************************************************
*      Fichier            : About_Unit.cpp                                      *
*      Programmeur        : ZAAGANE Mohammed                                   *
*      Email              : zagmoh2005@yahoo.fr                                *
*      site web           : http://zaagane-mohammed.ifrance.com                *
*      Date source        : mardi 05 février 2008                              *
*      Version source     : 1.07.02.2008                                       *
*      Langage            : C++ Builder                                        *
*      Type licence       : libre.                                             *
*      Modification       : dimenche 17 février 2008                           *
*******************************************************************************/

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "About_Unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAbout_Form *About_Form;
//---------------------------------------------------------------------------
__fastcall TAbout_Form::TAbout_Form(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAbout_Form::Ok_ButtonClick(TObject *Sender)
{
         Close();
}
//---------------------------------------------------------------------------
void __fastcall TAbout_Form::Label6Click(TObject *Sender)
{
         ShellExecute(0,"open","http://zaagane-mohammed.ifrance.com",0,0,SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TAbout_Form::Label7Click(TObject *Sender)
{
         ShellExecute(0,"open","mailto:zagmoh2005@yahoo.fr",0,0,SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

