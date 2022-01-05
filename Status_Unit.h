//---------------------------------------------------------------------------

#ifndef Status_UnitH
#define Status_UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TStatus_Form : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TGroupBox *GroupBox1;
        TLabel *Start_Time_Label;
        TLabel *Elabsed_Time_Label;
        TLabel *End_Time_Label;
        TPanel *Panel2;
        TLabel *Status_Label;
        TProgressBar *ProgressBar1;
        TTimer *Timer1;
        TButton *Close_Button;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Close_ButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        // variables
        TTime Start_Time,End_Time;// le temps de démarrage et d'arret (split / build)
        __fastcall TStatus_Form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TStatus_Form *Status_Form;
//---------------------------------------------------------------------------
#endif
