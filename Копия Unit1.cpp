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
/*        // ���������� ��������� WM_SPOOLERSTATUS, ������� ����������
        // ���� ���������� � ������, ����� ��������
        // �����������/��������� ����� ������� �� ������

        // �������� ������ ��������� ���������
DWORD ByteRez;
        // �������� � byteRez ���-�� ������ ������ ��� ������ ������� ���������
EnumPrinters(PRINTER_ENUM_LOCAL|PRINTER_ENUM_CONNECTIONS,NULL,2,NULL,0,&ByteRez,&PrintersCount);
        // �������� ������ ������
PrintersInfo = (PRINTER_INFO_2*)malloc(ByteRez);
        // ��������� ������� �������� ������ �������� ���������
bool Rez = EnumPrinters(PRINTER_ENUM_LOCAL|PRINTER_ENUM_CONNECTIONS,NULL,2,(LPBYTE)PrintersInfo,ByteRez,&ByteRez,&PrintersCount);
if(Rez==0) ShowMessage("EnumPrinter Err1");

        // ��������� ������ ������� ��� ����
if(Parametr.JobsLeft<AllJobs) {   // ����
        AllJobs =  Parametr.JobsLeft;   // ������� � AllJobs
        // ��� ������� �� ��������� �������� ������ �������
        for(unsigned int i=0; i<PrintersCount; i++) {
                HANDLE hPrinter;
                DWORD BytesRez;
        // ������� �������
                OpenPrinter(PrintersInfo[i].pPrinterName,&hPrinter,NULL);
        // ������� ������� ������� �������� ������ ��� �������
                EnumJobs(hPrinter,0,PrintersInfo[i].cJobs,1,NULL,0,&BytesRez,&JobsCount);
                JobsInfo = (JOB_INFO_2*)malloc(BytesRez);
                bool Rez1 = EnumJobs(hPrinter,0,PrintersInfo[i].cJobs,1,(LPBYTE)JobsInfo,BytesRez,&BytesRez,&JobsCount);
                if(Rez1==0) ShowMessage("EnumJobs Err");
        // ���� ��� ������� �������� ���-�� ������� ����� ������
                if(OnePrinterJobs[i]>JobsCount) {
                        // ������� ���������� ���-�� ������� � ������ ������� ��������
                        OnePrinterJobs[i] = JobsCount;
                        }
        // ������� ������� � ���������� ������
                ClosePrinter(hPrinter);
                free(JobsInfo);
                }
        }
else {  // ������
        AllJobs =  Parametr.JobsLeft;   // ���� ������ - ������� � AllJobs � ����������
        // ��� ������� �� ��������� �������� ������ �������
        for(unsigned int i=0; i<PrintersCount; i++) {
                HANDLE hPrinter;
                DWORD BytesRez;
        // ������� �������
                OpenPrinter(PrintersInfo[i].pPrinterName,&hPrinter,NULL);
        // ������� ������� ������� �������� ������ ��� �������
                EnumJobs(hPrinter,0,PrintersInfo[i].cJobs,1,NULL,0,&BytesRez,&JobsCount);
                JobsInfo = (JOB_INFO_2*)malloc(BytesRez);
                bool Rez1 = EnumJobs(hPrinter,0,PrintersInfo[i].cJobs,1,(LPBYTE)JobsInfo,BytesRez,&BytesRez,&JobsCount);
                if(Rez1==0) ShowMessage("EnumJobs Err");
        // ���� ��� ������� �������� ���-�� ������� �����������
                if(OnePrinterJobs[i]<JobsCount) {
                        // ������� ��������� ������� �������� � ���
                        Memo1->Lines->Add("���������: "+(AnsiString)JobsInfo[i].pMachineName);
                        Memo1->Lines->Add("�������: "+(AnsiString)JobsInfo[i].pPrinterName);
                        Memo1->Lines->Add("------------------------------");
                        Memo1->Lines->Add("������������: "+(AnsiString)JobsInfo[i].pUserName);
                        Memo1->Lines->Add("��������: "+(AnsiString)JobsInfo[i].pDocument);
                        Memo1->Lines->Add("�������: "+(AnsiString)IntToStr(JobsInfo[i].TotalPages));
                        Memo1->Lines->Add("******************************");
                        }
        // ������� ������� � ���������� ������
                ClosePrinter(hPrinter);
                free(JobsInfo);
                }
        }

        // �������� ������ ���. ��� ��������
*/
free(PrintersInfo);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
        // ��� �������� �����
        // �������� ������ ��������� ���������
DWORD ByteRez;
        // �������� � byteRez ���-�� ������ ������ ��� ������ ������� ���������
EnumPrinters(PRINTER_ENUM_CONNECTIONS,NULL,1,NULL,0,&ByteRez,&PrintersCount);
        // �������� ������ ������
PrintersInfo = (PRINTER_INFO_1*)malloc(ByteRez);
        // ��������� ������� �������� ������ �������� ���������
bool Rez = EnumPrinters(PRINTER_ENUM_CONNECTIONS,NULL,1,(LPBYTE)PrintersInfo,ByteRez,&ByteRez,&PrintersCount);
if(Rez==0) ShowMessage("EnumPrinter Err");
        // ������� ������ ��������� ��������� � �������� �����
        // ���-�� ��� ��������� �������? � ������������� ������� ��
        // ���������
TreeView->Items->Clear();
if(PrintersCount<1) TreeView->Items->Add(NULL,"!! ��������� ��������� ��� !!");
else {
//        TreeView->Items->Add(NULL,"��������� ��������");
        TreeView->Items->Add(NULL,"���������");
        int TempItem = 1;
//        OnePrinterJobs = new unsigned int[PrintersCount];    // ������ ������� �� ���������
        for(unsigned int i=0; i<PrintersCount; i++) {
                // �������� � ������ ������� ��������
//                if(PrintersInfo[i].pServerName) TreeView->Items->AddChild(TreeView->Items->Item[TempItem],(AnsiString)PrintersInfo[i].pPrinterName+" �� "+(AnsiString)PrintersInfo[i].pServerName);
                // �������� � ������ ��������� ��������
//                else {
                        TreeView->Items->AddChild(TreeView->Items->Item[0],PrintersInfo[i].pDescription);
//                        TempItem++;
//                        }
//                // �������� ����� ���-�� ��� ��������� �������
//                HANDLE hPrinter;
//                DWORD BytesRez;
//                // ������� �������
//                OpenPrinter(PrintersInfo[i].pPrinterName,&hPrinter,NULL);
//                // ������� ������� ������� �������� ������ ��� �������
//                EnumJobs(hPrinter,0,PrintersInfo[i].cJobs,1,NULL,0,&BytesRez,&JobsCount);
//                JobsInfo = (JOB_INFO_2*)malloc(BytesRez);
//                bool Rez1 = EnumJobs(hPrinter,0,PrintersInfo[i].cJobs,1,(LPBYTE)JobsInfo,BytesRez,&BytesRez,&JobsCount);
//                if(Rez1==0) ShowMessage("EnumJobs Err");
//                // ��� ������� ������� ������� � ������ ��� ����������� �������� � �������� � ����� ���-�� �������
//                OnePrinterJobs[i] = JobsCount;
//                AllJobs+=JobsCount;
//                // ������� ������� � ���������� ������
//                ClosePrinter(hPrinter);
//                free(JobsInfo);
                }
        }
        // ���������� ������ ���. ��� ��������� ���������
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
        // ��� �������� �����
//delete [] OnePrinterJobs;

//free(PrintersInfo);
//free(JobsInfo);
}
//---------------------------------------------------------------------------

