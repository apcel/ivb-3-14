//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
	//устанавливаем первоначальный адрес в строке запроса
	MainForm->URL->Text = "http://www.yandex.ru/";
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::Button1Click(TObject *Sender)
{

	//Для автоматического перехода на перенаправляемую страницу необходимо установить свойство
        //IdHTTP1->HandleRedirects= true;
        //Иначе будет генерироватся исключения с кодом 301,302 идр..
        //IdHTTP1->HandleRedirects=true; не всегда помогает при перенаправлении,
        // поэтому возникает необходимость обрабатывать перенаправление вручную.
        //С помощью IdHTTP1->Response->Location можно получить url куда нас собственно перенаправляют.
        //ErrorCode - код состояния (ответа) HTTP сервера
	if(MainForm->URL->Text != "")
        {
                try
                {
                    //делаем запрос Get

                    TStringList* head_list = new TStringList;
                    head_list->Text = IdHTTP1->Get(URL->Text);
                    //Возвращенные заголовки (после ответа сервера) можно посмотреть так:
                    head_list->Text = IdHTTP1->Response->RawHeaders->GetText();
                    //
                    int count_lines = head_list->Count;//количество заголовков
                    for(int i = 0; i<count_lines; i++)
                    {
                        String tmp_str = head_list->Strings[i];

                        //определяем заголовки
                        //заголовок кэша
                        if(tmp_str.Pos("Cache-Control"))
                        {
                        	AnswerServer->Lines->Add("Cache-Control");
                                AnswerServer->Lines->Add("Основные директивы для управления кэшированием.");
                                AnswerServer->Lines->Add(tmp_str);
                                AnswerServer->Lines->Add("");
                        }
                        //заголовок соединения
                        if(tmp_str.Pos("Connection"))
                        {
                        	AnswerServer->Lines->Add("Connection");
                                AnswerServer->Lines->Add("Сведения о проведении соединения.");
                                AnswerServer->Lines->Add(tmp_str);
                                AnswerServer->Lines->Add("");
                        }
                        //заголовок даты
                        if(tmp_str.Pos("Date"))
                        {
                        	AnswerServer->Lines->Add("Date");
                                AnswerServer->Lines->Add("Дата генерации отклика.");
                                AnswerServer->Lines->Add(tmp_str);
                                AnswerServer->Lines->Add("");
                        }
                        //Pragma
                        if(tmp_str.Pos("Pragma"))
                        {
                        	AnswerServer->Lines->Add("Pragma");
                                AnswerServer->Lines->Add("Особенные опции выполнения операции.");
                                AnswerServer->Lines->Add(tmp_str);
                                AnswerServer->Lines->Add("");
                        }
                        //Transfer-Encoding
                        if(tmp_str.Pos("Transfer-Encoding"))
                        {
                        	AnswerServer->Lines->Add("Transfer-Encoding");
                                AnswerServer->Lines->Add("Список способов кодирования, которые были применены к сообщению для передачи.");
                                AnswerServer->Lines->Add(tmp_str);
                                AnswerServer->Lines->Add("");
                        }
                        //Upgrade
                        if(tmp_str.Pos("Upgrade"))
                        {
                        	AnswerServer->Lines->Add("Upgrade");
                                AnswerServer->Lines->Add("Список предлагаемых клиентом протоколов.");
                                AnswerServer->Lines->Add(tmp_str);
                                AnswerServer->Lines->Add("");
                        }
                        //Warning
                        if(tmp_str.Pos("Warning"))
                        {
                        	AnswerServer->Lines->Add("Warning");
                                AnswerServer->Lines->Add("Код, агент, сообщение и дата, если возникла критическая ситуация.");
                                AnswerServer->Lines->Add(tmp_str);
                                AnswerServer->Lines->Add("");
                        }
                    }
                }
                catch(EIdHTTPProtocolException &E)
                {
                    if(E.ErrorCode == 302)
                    {
                        AnswerServer->Text = IdHTTP1->Get(IdHTTP1->Response->Location);//переход
                    };
                }
                catch(EIdException &E)// Другие исключения Indy
                {
                	ShowMessage("Ошибка:\n\""+E.Message+"\"");
                }
		catch(Exception &E)   // Другие НЕ Indy исключения
                {
                	ShowMessage("Ошибка:\n\""+ E.Message+"\"");
                }



        }
                //отключаемся от сервера
        IdHTTP1->Disconnect();
}
//---------------------------------------------------------------------------
