//---------------------------------------------------------------------------

#ifndef Main_UnitH
#define Main_UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TMain_Form : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *Fichier1;
        TMenuItem *Dcomposer1;
        TMenuItem *Recomposer1;
        TMenuItem *Quitter1;
        TMenuItem *Aide1;
        TMenuItem *Apropos1;
        TPanel *Main_Panel;
        TImage *Image1;
        TLabel *Label1;
        TLabel *Label2;
        TPanel *Split_Build_Btn_Panel;
        TButton *Left_Split_Button;
        TButton *Left_Build_Button;
        TPanel *Close_Btn_Panel;
        TButton *Close_Button;
        TOpenDialog *Split_OpenDialog;
        TOpenDialog *Build_OpenDialog;
        TStatusBar *StatusBar1;
        TGroupBox *Build_GroupBox;
        TPanel *Panel1;
        TLabel *Label3;
        TEdit *ZMSB_File_Path_Edit;
        TButton *Build_Brows_Button;
        TGroupBox *Split_GroupBox;
        TGroupBox *GroupBox1;
        TCheckBox *Bat_File_CheckBox;
        TCheckBox *Name_Part_CheckBox;
        TGroupBox *GroupBox2;
        TLabel *Part_Size_Label;
        TLabel *Label4;
        TEdit *Part_Size_Edit;
        TComboBox *Size_Unit_ComboBox;
        TPanel *Panel2;
        TButton *Hid_Build_GroupBox_Button;
        TButton *Build_Button;
        TPanel *Panel3;
        TButton *Split_Button;
        TButton *Hid_Split_GroupBox_Button;
        TPanel *Panel4;
        TLabel *Src_File_Label;
        TEdit *Src_File_Name_Edit;
        TButton *Split_Brows_Button;
        void __fastcall Build_Brows_ButtonClick(TObject *Sender);
        void __fastcall Build_ButtonClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Left_Split_ButtonClick(TObject *Sender);
        void __fastcall Left_Build_ButtonClick(TObject *Sender);
        void __fastcall Split_ButtonClick(TObject *Sender);
        void __fastcall Split_Brows_ButtonClick(TObject *Sender);
        void __fastcall Hid_Split_GroupBox_ButtonClick(TObject *Sender);
        void __fastcall Hid_Build_GroupBox_ButtonClick(TObject *Sender);
        void __fastcall Apropos1Click(TObject *Sender);
        void __fastcall Quitter1Click(TObject *Sender);
        void __fastcall Close_ButtonClick(TObject *Sender);
        void __fastcall Dcomposer1Click(TObject *Sender);
        void __fastcall Recomposer1Click(TObject *Sender);

private:	// User declarations
        // méthodes
        void __fastcall On_Start_Split();
        void __fastcall On_End_Split();
        void __fastcall On_Start_Build();
        void __fastcall On_End_Build();
public:		// User declarations
        __fastcall TMain_Form(TComponent* Owner);



};
//---------------------------------------------------------------------------
extern PACKAGE TMain_Form *Main_Form;
//---------------------------------------------------------------------------
#endif
