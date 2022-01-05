//---------------------------------------------------------------------------

#ifndef About_UnitH
#define About_UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TAbout_Form : public TForm
{
__published:	// IDE-managed Components
        TButton *Ok_Button;
        TImage *Image1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TMemo *Memo1;
        void __fastcall Ok_ButtonClick(TObject *Sender);
        void __fastcall Label6Click(TObject *Sender);
        void __fastcall Label7Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TAbout_Form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAbout_Form *About_Form;
//---------------------------------------------------------------------------
#endif
