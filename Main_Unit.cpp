/*******************************************************************************
*      Fichier            : Main_Unit.cpp                                      *
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

#include "Main_Unit.h"
#include "Status_Unit.h"
#include "About_Unit.h"
#include "Split_c++_Builder_Version.h"
#include "Build_c++_Builder_Version.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMain_Form *Main_Form;
//---------------------------------------------------------------------------
__fastcall TMain_Form::TMain_Form(TComponent* Owner)
        : TForm(Owner)
{
}



void __fastcall TMain_Form::On_Start_Split()
{
       Status_Form->Start_Time_Label->Caption="L'houre de démarrage : "+Date()+" à "+Status_Form->Start_Time;
       Status_Form->End_Time_Label->Caption="L'houre d'arret : ";
       Status_Form->ProgressBar1->Position=0;
       Status_Form->Status_Label->Caption="Décomposition en cours veuillez patienter...";
       Status_Form->Show();
       Main_Form->Enabled=false;
}

void __fastcall TMain_Form::On_End_Split()
{
       Status_Form->End_Time_Label->Caption="L'houre d'arret : "+Date()+" à "+Status_Form->End_Time;
}

void __fastcall TMain_Form::On_Start_Build()
{
       Status_Form->Start_Time_Label->Caption="L'houre de démarrage : "+Date()+" à "+Status_Form->Start_Time;
       Status_Form->End_Time_Label->Caption="L'houre d'arret : ";
       Status_Form->ProgressBar1->Position=0;
       Status_Form->Status_Label->Caption="Recomposition en cours veuillez patienter...";
       Status_Form->Show();
       Main_Form->Enabled=false;
}

void __fastcall TMain_Form::On_End_Build()
{
       Status_Form->End_Time_Label->Caption="L'houre d'arret : "+Date()+" à "+Status_Form->End_Time;
}
//---------------------------------------------------------------------------



/*-----------------------------------------------------------------------------*
*  Click sur le bouton "parcourir" pour sélèctionner le fichier d'informations *
*-----------------------------------------------------------------------------*/
void __fastcall TMain_Form::Build_Brows_ButtonClick(TObject *Sender)
{
         Build_OpenDialog->Title="ouvrir le fichier d'informations ";
         Build_OpenDialog->Filter="fichier d'informations(*.zmsb) | *.zmsb";

         if(Build_OpenDialog->Execute())
         {
                ZMSB_File_Path_Edit->Text=Build_OpenDialog->FileName;
         }
}
//------------------------------------------------------------------------------

/*-----------------------------------------------------------------------------*
*  Click sur le bouton "recomposer" pour lancer la recomposition               *
*-----------------------------------------------------------------------------*/
void __fastcall TMain_Form::Build_ButtonClick(TObject *Sender)
{

        int Returned_Value;// la valeur retourner par la fonction "Build"

        if(ZMSB_File_Path_Edit->Text=="")// si l'edit est vide
        {
               MessageDlg("Veuillez sélèctionner le fichier d'informations (*.zmsb)",mtError,TMsgDlgButtons() << mbOK,0);
               goto end2;
        }

        Status_Form->Start_Time=Time();
        Status_Form->Timer1->Enabled=true;
        Status_Form->Close_Button->Enabled=false;

        On_Start_Build();

        Returned_Value=Build(ZMSB_File_Path_Edit->Text.c_str());

        switch (Returned_Value)
        {
                case 0:
                {
                         Status_Form->End_Time=Time();
                         Status_Form->Timer1->Enabled=false;
                         Status_Form->Status_Label->Caption="Fichier Recomposer avec succè.";
                         Status_Form->Status_Label->Font->Color=clGreen;
                         Status_Form->Close_Button->Enabled=true;
                         MessageDlg("Fichier Recomposer avec succè.",mtInformation,TMsgDlgButtons() << mbOK,0);
                         On_End_Build();
                }
                break;

                case 1:
                {
                         Status_Form->End_Time=Time();
                         Status_Form->Timer1->Enabled=false;
                         Status_Form->Status_Label->Caption="Erreur.";
                         Status_Form->Status_Label->Font->Color=clRed;
                         Status_Form->Close_Button->Enabled=true;
                         MessageDlg("impossible d'ouvrire le fichier d'informations '.zmsb'",mtError,TMsgDlgButtons() << mbOK,0);
                         On_End_Build();
                }
                break;

                case 2:
                {

                         Status_Form->End_Time=Time();
                         Status_Form->Timer1->Enabled=false;
                         Status_Form->Status_Label->Caption="Erreur.";
                         Status_Form->Status_Label->Font->Color=clRed;
                         Status_Form->Close_Button->Enabled=true;
                         MessageDlg(" le fichier sélectionné n'est pas de type '.zmsb'",mtError,TMsgDlgButtons() << mbOK,0);
                         On_End_Build();
                }
                break;

                case 3:
                {
                         Status_Form->End_Time=Time();
                         Status_Form->Timer1->Enabled=false;
                         Status_Form->Status_Label->Caption="Erreur.";
                         Status_Form->Status_Label->Font->Color=clRed;
                         Status_Form->Close_Button->Enabled=true;
                         MessageDlg("impossible de fermer le fichier d'informations",mtError,TMsgDlgButtons() << mbOK,0);
                         On_End_Build();
                }
                break;

                case 4:
                {

                         Status_Form->End_Time=Time();
                         Status_Form->Timer1->Enabled=false;
                         Status_Form->Status_Label->Caption="Erreur.";
                         Status_Form->Status_Label->Font->Color=clRed;
                         Status_Form->Close_Button->Enabled=true;
                         MessageDlg("impossible de créer le fichier déstination",mtError,TMsgDlgButtons() << mbOK,0);
                         On_End_Build();
                }

                break;

                case 5:
                {
                         Status_Form->End_Time=Time();
                         Status_Form->Timer1->Enabled=false;
                         Status_Form->Status_Label->Caption="Erreur.";
                         Status_Form->Status_Label->Font->Color=clRed;
                         Status_Form->Close_Button->Enabled=true;
                         MessageDlg("impossible d'ouvrire un fichier source (partition)",mtError,TMsgDlgButtons() << mbOK,0);
                         On_End_Build();
                }
                break;

                default :
                {

                         Status_Form->End_Time=Time();
                         Status_Form->Timer1->Enabled=false;
                         Status_Form->Status_Label->Caption="Erreur.";
                         Status_Form->Status_Label->Font->Color=clRed;
                         Status_Form->Close_Button->Enabled=true;
                         MessageDlg("erreur inconnu!!",mtError,TMsgDlgButtons() << mbOK,0);
                         On_End_Build();
                }
                break;
        }
        end2:
}
//---------------------------------------------------------------------------



void __fastcall TMain_Form::FormCreate(TObject *Sender)
{
          // pour Saisir que des chiffres dans Part_Size_Edit.
          SetWindowLong(Part_Size_Edit->Handle,GWL_STYLE,GetWindowLong(Part_Size_Edit->Handle,GWL_STYLE)| ES_NUMBER );
          //-----
          Split_GroupBox->Parent=Main_Form;
          Split_GroupBox->Top=Build_GroupBox->Top;
          Split_GroupBox->Left=Build_GroupBox->Left;
          Split_GroupBox->Width=Build_GroupBox->Width;
          Split_GroupBox->Height=Build_GroupBox->Height;
          Size_Unit_ComboBox->ItemIndex=1;
}
//----------------------------------



void __fastcall TMain_Form::Left_Split_ButtonClick(TObject *Sender)
{
         Build_GroupBox->Visible=false;
         Split_GroupBox->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Left_Build_ButtonClick(TObject *Sender)
{
         Split_GroupBox->Visible=false;
         Build_GroupBox->Visible=true;
}
//---------------------------------------------------------------------------



void __fastcall TMain_Form::Split_ButtonClick(TObject *Sender)
{
       int Returned_Value;
       int Part_Size=0;

       if(Src_File_Name_Edit->Text=="")
       {
              MessageDlg("Veuillez ouvrir un fichier à décomposer",mtError,TMsgDlgButtons() << mbOK,0);
              goto end;
       }

       if(Part_Size_Edit->Text=="")
       {
              MessageDlg("Veuillez choisir une taille de partitions valide",mtError,TMsgDlgButtons() << mbOK,0);
              goto end;
       }

       if(Size_Unit_ComboBox->Text=="Octet" || Size_Unit_ComboBox->Text=="")
       {
              Part_Size=StrToInt(Part_Size_Edit->Text);
       }
       else if(Size_Unit_ComboBox->Text=="Kilo octet")
       {
              Part_Size=StrToInt(Part_Size_Edit->Text)*1024;
       }
       else if(Size_Unit_ComboBox->Text=="Mega octet")
       {
              Part_Size=StrToInt(Part_Size_Edit->Text)*1024*1024;
       }

       Status_Form->Start_Time=Time();
       Status_Form->Timer1->Enabled=true;
       Status_Form->Close_Button->Enabled=false;

       On_Start_Split();

       if(Name_Part_CheckBox->Checked)
       {
                if(Bat_File_CheckBox->Checked)
                {
                         Returned_Value=Split_File(Src_File_Name_Edit->Text.c_str(),Part_Size,true,true);
                }
                else
                {
                         Returned_Value=Split_File(Src_File_Name_Edit->Text.c_str(),Part_Size,true,false);
                }
       }
       else
       {
                if(Bat_File_CheckBox->Checked)
                {
                         Returned_Value=Split_File(Src_File_Name_Edit->Text.c_str(),Part_Size,false,true);
                }
                else
                {
                         Returned_Value=Split_File(Src_File_Name_Edit->Text.c_str(),Part_Size,false,false);
                }
       }

      switch (Returned_Value)
      {
                case 0:
                {
                         Status_Form->End_Time=Time();
                         Status_Form->Timer1->Enabled=false;
                         Status_Form->Status_Label->Caption="Fichier Décomposer avec succè.";
                         Status_Form->Status_Label->Font->Color=clGreen;
                         Status_Form->Close_Button->Enabled=true;
                         MessageDlg("Fichier décomposé avec sucssè.",mtInformation,TMsgDlgButtons() << mbOK,0);
                         On_End_Split();
                }
                break;

                case 1:
                {
                         Status_Form->End_Time=Time();
                         Status_Form->Timer1->Enabled=false;
                         Status_Form->Status_Label->Caption="Erreur.";
                         Status_Form->Status_Label->Font->Color=clRed;
                         Status_Form->Close_Button->Enabled=true;
                         MessageDlg("impossile d'ouvrir le fichier source.",mtError,TMsgDlgButtons() << mbOK,0);
                         On_End_Split();
                }
                break;

                case 2:
                {
                         Status_Form->End_Time=Time();
                         Status_Form->Timer1->Enabled=false;
                         Status_Form->Status_Label->Caption="Erreur.";
                         Status_Form->Status_Label->Font->Color=clRed;
                         Status_Form->Close_Button->Enabled=true;
                         MessageDlg("impossible de céer un fichier déstination",mtError,TMsgDlgButtons() << mbOK,0);
                         On_End_Split();
                }
                break;

                case 3:
                {
                         Status_Form->End_Time=Time();
                         Status_Form->Timer1->Enabled=false;
                         Status_Form->Status_Label->Caption="Erreur.";
                         Status_Form->Status_Label->Font->Color=clRed;
                         Status_Form->Close_Button->Enabled=true;
                         MessageDlg("impossible de fermer un fichier déstination",mtError,TMsgDlgButtons() << mbOK,0);
                         On_End_Split();
                }
                break;

                case 4:
                {
                         Status_Form->End_Time=Time();
                         Status_Form->Timer1->Enabled=false;
                         Status_Form->Status_Label->Caption="Erreur.";
                         Status_Form->Status_Label->Font->Color=clRed;
                         Status_Form->Close_Button->Enabled=true;
                         MessageDlg("impossible de fermer le fichier source",mtWarning,TMsgDlgButtons() << mbOK,0);
                         On_End_Split();
                }
                break;

                default :
                {
                         Status_Form->End_Time=Time();
                         Status_Form->Timer1->Enabled=false;
                         Status_Form->Status_Label->Caption="Erreur.";
                         Status_Form->Status_Label->Font->Color=clRed;
                         Status_Form->Close_Button->Enabled=true;
                         MessageDlg("erreur inconnu!!",mtError,TMsgDlgButtons() << mbOK,0);
                         On_End_Split();
                }
      }

      On_End_Split();
      end:
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Split_Brows_ButtonClick(TObject *Sender)
{
         Split_OpenDialog->Title="ouvrir un fichier à décomposer ";
         Split_OpenDialog->Filter="Tous les fichier(*.*) | *.*";

         if(Split_OpenDialog->Execute())
         {
                Src_File_Name_Edit->Text=Split_OpenDialog->FileName;
         }
}
//---------------------------------------------------------------------------


void __fastcall TMain_Form::Hid_Split_GroupBox_ButtonClick(TObject *Sender)
{
         Build_GroupBox->Visible=false;
         Split_GroupBox->Visible=false;

         Src_File_Name_Edit->Text="";
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Hid_Build_GroupBox_ButtonClick(TObject *Sender)
{
         Build_GroupBox->Visible=false;
         Split_GroupBox->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Apropos1Click(TObject *Sender)
{
        About_Form->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Quitter1Click(TObject *Sender)
{
        Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Close_ButtonClick(TObject *Sender)
{
        Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Dcomposer1Click(TObject *Sender)
{
          Left_Split_ButtonClick(this);
}
//---------------------------------------------------------------------------

void __fastcall TMain_Form::Recomposer1Click(TObject *Sender)
{
          Left_Build_ButtonClick(this);
}
//---------------------------------------------------------------------------

