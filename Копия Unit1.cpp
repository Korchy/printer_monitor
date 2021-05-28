//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
AllJobs = 0;
}
//---------------------------------------------------------------------------
void TForm1::OnSp(TWMSpoolerStatus &Parametr)
{
/*        // Обработчик сообщения WM_SPOOLERSTATUS, которое посылается
        // всем программам в момент, когда принтеру
        // добавляется/удаляется новое задание на печать

        // Получить список доступных принтеров
DWORD ByteRez;
        // Получить в byteRez кол-во памяти нужное под список стуктур принтеров
EnumPrinters(PRINTER_ENUM_LOCAL|PRINTER_ENUM_CONNECTIONS,NULL,2,NULL,0,&ByteRez,&PrintersCount);
        // Выделить нужную память
PrintersInfo = (PRINTER_INFO_2*)malloc(ByteRez);
        // Повторным вызовом получить список структур принтеров
bool Rez = EnumPrinters(PRINTER_ENUM_LOCAL|PRINTER_ENUM_CONNECTIONS,NULL,2,(LPBYTE)PrintersInfo,ByteRez,&ByteRez,&PrintersCount);
if(Rez==0) ShowMessage("EnumPrinter Err1");

        // Проверить пришло задание или ушло
if(Parametr.JobsLeft<AllJobs) {   // Ушло
        AllJobs =  Parametr.JobsLeft;   // занести в AllJobs
        // Для каждого из принтеров получить списки заданий
        for(unsigned int i=0; i<PrintersCount; i++) {
                HANDLE hPrinter;
                DWORD BytesRez;
        // Открыть принтер
                OpenPrinter(PrintersInfo[i].pPrinterName,&hPrinter,NULL);
        // Двойным вызовом функции получить список его заданий
                EnumJobs(hPrinter,0,PrintersInfo[i].cJobs,1,NULL,0,&BytesRez,&JobsCount);
                JobsInfo = (JOB_INFO_2*)malloc(BytesRez);
                bool Rez1 = EnumJobs(hPrinter,0,PrintersInfo[i].cJobs,1,(LPBYTE)JobsInfo,BytesRez,&BytesRez,&JobsCount);
                if(Rez1==0) ShowMessage("EnumJobs Err");
        // Если для данного принтера кол-во заданий стало меньше
                if(OnePrinterJobs[i]>JobsCount) {
                        // Занести оставшееся кол-во заданий в массив заданий принтера
                        OnePrinterJobs[i] = JobsCount;
                        }
        // Закрыть принтер и освободить память
                ClosePrinter(hPrinter);
                free(JobsInfo);
                }
        }
else {  // Пришло
        AllJobs =  Parametr.JobsLeft;   // Если пришло - занести в AllJobs и обработать
        // Для каждого из принтеров получить списки заданий
        for(unsigned int i=0; i<PrintersCount; i++) {
                HANDLE hPrinter;
                DWORD BytesRez;
        // Открыть принтер
                OpenPrinter(PrintersInfo[i].pPrinterName,&hPrinter,NULL);
        // Двойным вызовом функции получить список его заданий
                EnumJobs(hPrinter,0,PrintersInfo[i].cJobs,1,NULL,0,&BytesRez,&JobsCount);
                JobsInfo = (JOB_INFO_2*)malloc(BytesRez);
                bool Rez1 = EnumJobs(hPrinter,0,PrintersInfo[i].cJobs,1,(LPBYTE)JobsInfo,BytesRez,&BytesRez,&JobsCount);
                if(Rez1==0) ShowMessage("EnumJobs Err");
        // Если для данного принтера кол-во заданий увеличилось
                if(OnePrinterJobs[i]<JobsCount) {
                        // Занести последнее задание принтера в лог
                        Memo1->Lines->Add("Компьютер: "+(AnsiString)JobsInfo[i].pMachineName);
                        Memo1->Lines->Add("Принтер: "+(AnsiString)JobsInfo[i].pPrinterName);
                        Memo1->Lines->Add("------------------------------");
                        Memo1->Lines->Add("Пользователь: "+(AnsiString)JobsInfo[i].pUserName);
                        Memo1->Lines->Add("Документ: "+(AnsiString)JobsInfo[i].pDocument);
                        Memo1->Lines->Add("Страниц: "+(AnsiString)IntToStr(JobsInfo[i].TotalPages));
                        Memo1->Lines->Add("******************************");
                        }
        // Закрыть принтер и освободить память
                ClosePrinter(hPrinter);
                free(JobsInfo);
                }
        }

        // Очистить память выд. под принтеры
*/
free(PrintersInfo);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
        // При создании формы
        // Получить список доступных принтеров
DWORD ByteRez;
        // Получить в byteRez кол-во памяти нужное под список стуктур принтеров
EnumPrinters(PRINTER_ENUM_CONNECTIONS,NULL,1,NULL,0,&ByteRez,&PrintersCount);
        // Выделить нужную память
PrintersInfo = (PRINTER_INFO_1*)malloc(ByteRez);
        // Повторным вызовом получить список структур принтеров
bool Rez = EnumPrinters(PRINTER_ENUM_CONNECTIONS,NULL,1,(LPBYTE)PrintersInfo,ByteRez,&ByteRez,&PrintersCount);
if(Rez==0) ShowMessage("EnumPrinter Err");
        // Создать дерево доступных принтеров и получить общее
        // кол-во уже имеющихся заданий? и распределение заданий по
        // принтерам
TreeView->Items->Clear();
if(PrintersCount<1) TreeView->Items->Add(NULL,"!! ДОСТУПНЫХ ПРИНТЕРОВ НЕТ !!");
else {
//        TreeView->Items->Add(NULL,"Локальные принтеры");
        TreeView->Items->Add(NULL,"Спринтеры");
        int TempItem = 1;
//        OnePrinterJobs = new unsigned int[PrintersCount];    // Массив заданий по принтерам
        for(unsigned int i=0; i<PrintersCount; i++) {
                // Добавить в дерево сетевые принтеры
//                if(PrintersInfo[i].pServerName) TreeView->Items->AddChild(TreeView->Items->Item[TempItem],(AnsiString)PrintersInfo[i].pPrinterName+" на "+(AnsiString)PrintersInfo[i].pServerName);
                // Добавить в дерево локальные принтеры
//                else {
                        TreeView->Items->AddChild(TreeView->Items->Item[0],PrintersInfo[i].pDescription);
//                        TempItem++;
//                        }
//                // Получить общее кол-во уже имеющихся заданий
//                HANDLE hPrinter;
//                DWORD BytesRez;
//                // Открыть принтер
//                OpenPrinter(PrintersInfo[i].pPrinterName,&hPrinter,NULL);
//                // Двойным вызовом функции получить список его заданий
//                EnumJobs(hPrinter,0,PrintersInfo[i].cJobs,1,NULL,0,&BytesRez,&JobsCount);
//                JobsInfo = (JOB_INFO_2*)malloc(BytesRez);
//                bool Rez1 = EnumJobs(hPrinter,0,PrintersInfo[i].cJobs,1,(LPBYTE)JobsInfo,BytesRez,&BytesRez,&JobsCount);
//                if(Rez1==0) ShowMessage("EnumJobs Err");
//                // Для каждого задания занести в массив для конкретного принтера и добавить в общее кол-во заданий
//                OnePrinterJobs[i] = JobsCount;
//                AllJobs+=JobsCount;
//                // Закрыть принтер и освободить память
//                ClosePrinter(hPrinter);
//                free(JobsInfo);
                }
        }
        // Освободить память выд. под структуры принтеров
free(PrintersInfo);

/*
PRINTER_INFO_2 *Pr;
Pr = new PRINTER_INFO_2[PrintersCount];
Pr = PrintersInfo;
//ShowMessage(Pr[0].pPrinterName);
*/

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        // При закрытии формы
//delete [] OnePrinterJobs;

//free(PrintersInfo);
//free(JobsInfo);
}
//---------------------------------------------------------------------------

