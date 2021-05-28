//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <winspool.h>
#include <ComCtrls.hpp>
#include <Menus.hpp>   // ��� ��������� ���������� � ���������
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TMemo *Memo1;
        TTreeView *TreeView;
        TMainMenu *MainMenu;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N3;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
        void OnSp(TWMSpoolerStatus& Message);   // ������� ����������� ������� �� ������
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);

        // ����������
        PRINTER_INFO_5 *PrintersInfo;   // ��������� �� ������ �������� � ����������
        JOB_INFO_2 *JobsInfo;           // ��������� �� ������ �������� � ��������� ����������� ��������
        DWORD PrintersCount;            // ���-�� ��������� (��������)
        DWORD JobsCount;                // ���-�� ������� ������ �������� (��������)

        int AllJobs;             // ����� ������� �� ������� ������
        unsigned int *OnePrinterJobs;     // ������ �������� � ���-�� ��������� ������ ���-�� ������� ��� ������� ��������

        // ����� ���������
BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_SPOOLERSTATUS,TWMSpoolerStatus,OnSp);  // ������� �������� �� ������
END_MESSAGE_MAP(TComponent)
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
 