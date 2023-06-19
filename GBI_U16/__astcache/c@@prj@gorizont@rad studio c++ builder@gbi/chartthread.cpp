//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "ChartThread.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TChartThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TChartThread::TChartThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{

/*
	TChartThread::TChartThread()
	{

	}

	TChartThread::TChartThread(TChart* c)
	{

	}

	TChartThread::~TChartThread()
	{

	}
*/

}


__fastcall TChartThread::TChartThread(bool CreateSuspended, TChart* c, int ds, int num): TThread(CreateSuspended)
{

	chart = c;
	redraw_flag = false;
	data_source = ds;
	thread_num = num;
	drill = NULL;

	unsigned char r,g,b = 0;

	r = 85;

	for (int i = 0; i < 100; i++) {

		TLineSeries * Ser = new TLineSeries(chart);

		Ser->Pointer->Style = psRectangle;

		Ser->DrawStyle = dsSegments;
		Ser->Active = true;

		//Ser->SortByLabels(0);
		//Ser->

		Ser->Pointer->Visible = true;

		Ser->Legend->Text = " ";
		Ser->Legend->Visible = false;
		Ser->Pen->Width = 1;

		//Ser->YValues->Order = loAscending;
		//Ser->YValues->Order = loDescending;
		//Ser->XValues->Order = loNone;

		Ser->YValues->Order = loDescending;
		Ser->XValues->Order = loNone;

		//Ser->Color =  (TColor)(RGB(r,g,b));

		Ser->Color = ChartColorsTable[i%20];

		chart->AddSeries(Ser);



		if (r == 255) {

			//b = 255;
			b+=85;
			r = 0;
			g = 0;
		}
		else if (b == 255) {

				b = 0;
				//g = 255;
				g+=85;
				r  = 0;

			 }
			 else if (g == 255) {
					  g = 0;
					  //r = 255;
					  r+=85;
					  b = 0;
				  }
				  else
				  {
					 r+=85;
                  }

	}

}

//---------------------------------------------------------------------------
void __fastcall TChartThread::Execute()
{
	//---- Place thread code here ----

	//SetName();

	while (Terminated == false)
	{

		Sleep(1);

		if ( redraw_flag == true) {
				 redraw_flag = false;
				//StartRedraw();
				//chart->Refresh();
				//chart->Update();
				Synchronize(StartRedraw);
		}

		Sleep(1);
	}

}
//---------------------------------------------------------------------------
void __fastcall TChartThread::StartRedraw(void)
{
	//redraw_flag = false;
	chart->LeftAxis->LabelsSize=5;

	if (drill != NULL) {

		AnsiString ss("");

		if (data_source == DATA_SOURCE_X)
		{
		 ss.printf("Ñìåùåíèå X, ìì [%s][%s]", drill->pname.c_str(), drill->name.c_str());
		}

		if (data_source == DATA_SOURCE_Y)
		{
		 ss.printf("Ñìåùåíèå Y, ìì [%s][%s]", drill->pname.c_str(), drill->name.c_str());
		}

		if (data_source == DATA_SOURCE_R)
		{
		 ss.printf("Ñìåùåíèå Res, ìì [%s][%s]", drill->pname.c_str(), drill->name.c_str());
		}

		chart->Title->Caption = ss.c_str();

	}


	AnsiString s("");

	for (int i = 0 ; i < 100; i++)
	{
		chart->Series[i]->Clear();
		chart->Series[i]->Legend->Text = " ";
		chart->Series[i]->Legend->Visible = false;
		chart->Series[i]->Pen->Width = 1;

		if (drill != NULL)
		{

			if (i<drill->meas_list_idx)
			{
				chart->Series[i]->Legend->Visible = true;
				TMeas* m = drill->meas_list[i];

				if (m->finalized == true)
				{

					s = FormatDateTime("dd-mm-yyyy hh:nn:ss", m->finalize_time);

				}
				else
				{
				  s.printf("Èçìåðåíèå_%d", i+1);
				}

				chart->Series[i]->Legend->Text = s;
				chart->Series[i]->Visible = true;
				//chart->Series[i+1]->Legend->Text = " ";
				//chart->Series[i+1]->Color = clWhite;
			}
			else
			{
			   	chart->Series[i]->Legend->Text = " ";
			}
		}
	}

	/*
	if (drill != NULL)
	{

			if (drill->meas_list_idx < 2) {

		chart->Series[2]->Legend->Text = " ";
		chart->Series[2]->Color = clWhite;
		chart->Series[2]->Legend->Visible = false;

		chart->Series[3]->Legend->Text = " ";
		chart->Series[3]->Color = clWhite;
		chart->Series[3]->Legend->Visible = false;

		}
	}
    */

	/*
	chart->Series[drill->meas_list_idx]->Legend->Text = " ";
	chart->Series[drill->meas_list_idx]->Color = clWhite;
	chart->Series[drill->meas_list_idx]->Legend->Visible = false;
	*/


	/*
	chart->Series[100]->Legend->Text = " ";
	chart->Series[100]->Color = clWhite;
	chart->Series[100]->Legend->Visible = false;

	if (drill->meas_list_idx<2) {

			chart->Series[100]->Legend->Visible = true;

	}
    */

//------
	if (drill == NULL)
	{

		chart->Series[0]->Legend->Visible = true;
		chart->Series[1]->Legend->Visible = true;
		chart->Series[2]->Legend->Visible = true;

		chart->BottomAxis->Maximum = 7*5;
		chart->BottomAxis->Minimum = 0;

		for (double a = 0; a < 3600; a+= 0.1) {

			chart->Series[0]->AddXY(a, sin(a)*10, "", chart->Series[0]->Color);

		}

		for (double a = 0; a < 3600; a+= 0.1) {

			chart->Series[5]->AddXY(a, cos(a)*10, "", chart->Series[5]->Color);

		}


		for (double a = 0; a < 3600; a+= 0.1) {

			chart->Series[6]->AddXY(a, cos(a)*10+10, "", chart->Series[6]->Color);

		}

	}

//---------

		double ymax = 0;
		double ymin = 0;

		double xmax = 0;
		double xmin = 0;


	if (drill != NULL)
	{
		//Ñêîëüêî èçìåðåíèé íàõîäèòñÿ â áàçå äëÿ äàííîé ñêâàæèíû
		int cnum = drill->meas_list_idx;
		//Ñêîëüêî óðîâíåé (îòñ÷åòîâ ïî îñè X) çàäàíî äëÿ äàííîé ñêâàæèíû
		int tnum = drill->records_cnt;


		TMeas* m = NULL;
		double d = 0;

		for (int i = 0; i < cnum; i++) {

			//chart->Series[i]->Marks->Visible = true;
			//chart->Pointe->Visible = true;

			m = drill->meas_list[i];

			for (int j = 0; j < tnum; j++) {

				//Ìàêñèìàëüíàÿ ãëóáèíà è ìàêñ ïî îñè X
				d = m->records[j].depth;

				if (d > xmax) xmax = d;

				//Ìàêñèìàëüíîå çíà÷åíèå ñìåùåíèÿ
				//Åñëè îòðèñîâûâàåì X
				if (data_source == DATA_SOURCE_X) d = m->records[j].LX;
				//Åñëè îòðèñîâûâàåì Y
				if (data_source == DATA_SOURCE_Y) d = m->records[j].LY;
				//Åñëè îòðèñîâûâàåì Res
				if (data_source == DATA_SOURCE_R) d = m->records[j].LR;//!!!sqrt(((m->records[j].LY)*(m->records[j].LY))+((m->records[j].LX)*(m->records[j].LX)));

				//Ìàêñ ïî îñè Y
				if (d>ymax) ymax = d;
				//Ìèí ïî îñè Y
				if (d<ymin) ymin = d;

			}

		}


		if (drill -> drill_orient == DRILL_ORIENT_HORIZONT)
		{
			chart->BottomAxis->Maximum = xmax;
			chart->BottomAxis->Minimum = 0;

			double dd = 0;
			dd = abs(ymax-ymin);
			dd*=0.2;

			ymax+=dd;
			ymin-=dd;

			chart->LeftAxis->Maximum = ymax;
			chart->LeftAxis->Minimum = ymin;
		}

		if (drill -> drill_orient == DRILL_ORIENT_VERTICAL)
		{
			chart->LeftAxis->Maximum = xmax;
			chart->LeftAxis->Minimum = 0;

			double dd = 0;
			dd = abs(ymax-ymin);
			dd*=0.2;

			ymax+=dd;
			ymin-=dd;

			chart->BottomAxis->Maximum = ymax;
			chart->BottomAxis->Minimum = ymin;
		}


			//TMeas* m = NULL;
			double datay = 0;
			double datax = 0;
			double dtmp = 0;


		for (int i = 0; i < drill->meas_list_idx; i++)
		{
			if (i>99)
			{
				break;
			}

			m = drill->meas_list[i];
			datay = 0;
			datax = 0;
			dtmp=0;

			/*
			if (drill -> drill_orient == DRILL_ORIENT_VERTICAL) {

				   m->Sort(0);
			}
			else
			{
				   m->Sort(-1);
			}
			*/

				   m->Sort(-1);

			for (int j = 0; j < m->records_cnt; j++) {

							if (m->finalized == false) {

								continue;
							}

							if (j>0)
							{
								//if (m->records_sort[j].depth<m->records_sort[j-1].depth)
								//{
								//	break;
								//}
							}

				datax = m->records_sort[j].depth;

				//Åñëè îòðèñîâûâàåì X
				if (data_source == DATA_SOURCE_X)
				{
					//m->records[j].LX = i+1;//dtmp; dtmp+=i;
					datay = m->records_sort[j].LX;

				}
				//Åñëè îòðèñîâûâàåì Y
				if (data_source == DATA_SOURCE_Y)
				{
					datay = m->records_sort[j].LY;
				}

				//Åñëè îòðèñîâûâàåì Res
				if (data_source == DATA_SOURCE_R)
				{
					datay = m->records_sort[j].LR;//!!!sqrt(((m->records_sort[j].LY)*(m->records_sort[j].LY))+((m->records_sort[j].LX)*(m->records_sort[j].LX)));
				}

				if (drill -> drill_orient == DRILL_ORIENT_HORIZONT)
				{
					chart->Series[i]->AddXY(datax,datay,"",chart->Series[i]->Color);
				}

				if (drill -> drill_orient == DRILL_ORIENT_VERTICAL)
				{
					chart->Series[i]->AddXY(datay,datax,"",chart->Series[i]->Color);
				}

			}
		}

	}


//---------

	chart->Refresh();
	chart->Update();

	if (data_source == DATA_SOURCE_R)
	{
	   g_xmax = xmax;
	   g_xmin = xmin;
	   g_ymax = ymax;
	   g_ymin = ymin;
	}

	//redraw_flag = true;
}

//---------------------------------------------------------------------------
void TChartThread::Redraw(void)
{
	redraw_flag = true;
	//StartRedraw();
}

//---------------------------------------------------------------------------
void TChartThread::SetDrill(TDrill* d)
{
	drill = d;
}

//---------------------------------------------------------------------------

typedef struct tagTHREADNAME_INFO
{
    DWORD dwType; // Must be 0x1000.
	LPCSTR szName; // Pointer to name (in user addr space).
	DWORD dwThreadID; // Thread ID (-1=caller thread).
	DWORD dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;

void TChartThread::SetName()
{

		//SetThreadDescription(::GetCurrentThread(),"ThisIsMyThreadName!");

		AnsiString s("");
		s.printf("Thread_%d",thread_num);

		THREADNAME_INFO info;

		info.dwType = 0x1000;
//		info.szName = "TChartThread"+thread_num;

		info.szName = s.c_str();

		info.dwThreadID = -1;
		info.dwFlags = 0;

		__try
		{
				 RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(DWORD),(DWORD*)&info );
		}
		__except (EXCEPTION_CONTINUE_EXECUTION)
		{
                 Sleep(1);
		}

}

