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
#include <Menus.hpp>   // Для получения информации о принтерах
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
        void OnSp(TWMSpoolerStatus& Message);   // Функция отлавливает задания на печать
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);

        // Переменные
        PRINTER_INFO_5 *PrintersInfo;   // Указатель на массив структур с принтерами
        JOB_INFO_2 *JobsInfo;           // Указатель на массив структур с заданиями конкретного принтера
        DWORD PrintersCount;            // Кол-во принтеров (структур)
        DWORD JobsCount;                // Кол-во заданий одного принтера (структур)

        int AllJobs;             // Всего заданий на текущий момент
        unsigned int *OnePrinterJobs;     // Массив размером в кол-во принтеров хранит кол-во заданий для каждого принтера

        // Карта сообщений
BEGIN_MESSAGE_MAP
        MESSAGE_HANDLER(WM_SPOOLERSTATUS,TWMSpoolerStatus,OnSp);  // Задание принтеру на печать
END_MESSAGE_MAP(TComponent)
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
 