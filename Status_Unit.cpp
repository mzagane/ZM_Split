/*******************************************************************************
*      Fichier            : Status_Unit.cpp                                    *
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

#include "Status_Unit.h"
#include "Main_Unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TStatus_Form *Status_Form;
//---------------------------------------------------------------------------
__fastcall TStatus_Form::TStatus_Form(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TStatus_Form::Timer1Timer(TObject *Sender)
{

        Elabsed_Time_Label->Caption="Temps écoulé : "+ TimeToStr(Time()-Start_Time);

}
//---------------------------------------------------------------------------

/*-----------------------------------------------------------------------------*
*                      Click sur le bouton "fermer"                            *
*-----------------------------------------------------------------------------*/
void __fastcall TStatus_Form::Close_ButtonClick(TObject *Sender)
{
       Main_Form->Enabled=true;// activer la fenêtre principale
       Main_Form->Src_File_Name_Edit->Text="";
       Main_Form->Part_Size_Edit->Text="";
       Main_Form->ZMSB_File_Path_Edit->Text="";

       Main_Form->Show();// afficher la fenêtre principale

}
//------------------------------------------------------------------------------

