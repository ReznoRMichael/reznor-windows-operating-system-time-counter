//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <string>
#include <fstream>
#include <iostream>

#include "Unit1.h"
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

// ilosc sekund
unsigned int s=0;
int godzin, minut, sekund;
AnsiString godz, mins, sek;
string txt_line;

void SaveTxtTimer()
{
    fstream textfile_save;
    textfile_save.open("counter.txt", ios::out);

    textfile_save << s << endl;
    textfile_save
    << "Total time counted: " << endl
    << godz.c_str() << " h : "
    << mins.c_str() << " min : "
    << sek.c_str() << " sec";

    textfile_save.close();
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
    fstream textfile_read;
    textfile_read.open("counter.txt", ios::in);

    if (textfile_read.good()==true)
    {
        /*char c;
        unsigned int cc=0;
        while (textfile_read.get(c)) cc++;
            if (cc>0)
            {   */
                getline(textfile_read,txt_line);
                s = StrToInt(txt_line.c_str());
            /*}
            else textfile_read.close();*/
    }
    textfile_read.close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
    s++;

    godzin = s / 3600;
    godz = IntToStr(godzin);
    if(godzin<10) godz = "0"+godz;
    minut = (s - godzin * 3600) / 60;
    mins = IntToStr(minut);
    if(minut<10) mins = "0"+mins;
    sekund = s - godzin * 3600 - minut * 60;
    sek = IntToStr(sekund);
    if(sekund<10) sek = "0"+sek;

    // Label1 -> Caption = godz+":"+mins+":"+sek;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
    SaveTxtTimer();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    CanClose = false;
    if (CanClose==false)
    {
    SaveTxtTimer();
    CanClose = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
    SaveTxtTimer();
}
//---------------------------------------------------------------------------
