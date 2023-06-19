//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <IniFiles.hpp>
//---------------------------------------------------------------------------
USEFORM("PortAdjust.cpp", Form_PortAdjust);
USEFORM("MeasAdjust.cpp", Form_MeasAdjust);
USEFORM("PlaceAdjust.cpp", Form_PlaceAdjust);
USEFORM("SystemAdjust.cpp", Form_SystemAdjust);
USEFORM("SensorAdjust.cpp", Form_SensorAdjust);
USEFORM("DataEnter.cpp", Form_data_enter);
USEFORM("DepthAdjust.cpp", Form_DepthAdjust);
USEFORM("Diagram.cpp", Form_diagram);
USEFORM("About.cpp", Form_about);
USEFORM("Main.cpp", FMain);
USEFORM("DrillAdjust.cpp", Form_DrillAdjust);
USEFORM("ExcelWait.cpp", Form_excel_progress);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{

	AnsiString cap("");

	AnsiString scname;
	TIniFile *ini=new TIniFile(ChangeFileExt(Application->ExeName,".gcf"));
	scname = ini->ReadString("GENERAL","CONFNAME","GBI");

	char dir [1024];

	GetCurrentDirectory(1029,dir);
	strcat(dir,"\\Config\\");
	strcat(dir,scname.c_str());
	strcat(dir,".ini");

	cap.printf("GBI [%s]",dir);

	char ccap[1024];
	strcpy(ccap,cap.c_str());

	HWND h=FindWindow("TFMain",cap.c_str());

	if(h!=NULL)
	{
	   MessageBox(NULL,"Ïðîãðàììà c âûáðàííîé êíôèãóðàöèåé ñèñòåìû óæå îòêðûòà!","ÂÍÈÌÀÍÅ!",0);
	   exit(0);
	}


	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TFMain), &FMain);
		Application->CreateForm(__classid(TForm_about), &Form_about);
		Application->CreateForm(__classid(TForm_SystemAdjust), &Form_SystemAdjust);
		Application->CreateForm(__classid(TForm_SensorAdjust), &Form_SensorAdjust);
		Application->CreateForm(__classid(TForm_PortAdjust), &Form_PortAdjust);
		Application->CreateForm(__classid(TForm_PlaceAdjust), &Form_PlaceAdjust);
		Application->CreateForm(__classid(TForm_MeasAdjust), &Form_MeasAdjust);
		Application->CreateForm(__classid(TForm_DrillAdjust), &Form_DrillAdjust);
		Application->CreateForm(__classid(TForm_DepthAdjust), &Form_DepthAdjust);
		Application->CreateForm(__classid(TForm_diagram), &Form_diagram);
		Application->CreateForm(__classid(TForm_excel_progress), &Form_excel_progress);
		Application->CreateForm(__classid(TForm_data_enter), &Form_data_enter);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
