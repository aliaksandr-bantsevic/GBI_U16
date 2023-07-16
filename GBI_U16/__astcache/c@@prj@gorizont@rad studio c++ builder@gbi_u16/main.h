//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ToolWin.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>

#include <System.Win.ScktComp.hpp>
#include <Vcl.Grids.hpp>
#include <tchar.h>
#include <VCLTee.Chart.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.Series.hpp>

#include <Vcl.Dialogs.hpp>

#include "defs.h"
#include "GBISystem.h"
#include "Protocol_211.h"
#include "ChartThread.h"

#include "About.h"
#include "PortAdjust.h"
#include "SensorAdjust.h"
#include "SystemAdjust.h"
#include "DepthAdjust.h"
#include "PlaceAdjust.h"
#include "DrillAdjust.h"
#include "MeasAdjust.h"
#include "Diagram.h"
#include "DataEnter.h"

//---------------------------------------------------------------------------
class TFMain : public TForm
{
__published:	// IDE-managed Components
	TStatusBar *MStatusBar;
	TToolBar *MToolBar;
	TPanel *Panel_tree;
	TSplitter *Splitter1;
	TPanel *Panel2;
	TPanel *Panel_work_area;
	TSplitter *Splitter2;
	TPanel *Panel_console_meas_control;
	TTreeView *TreeView_system;
	TMainMenu *MainMenu;
	TMenuItem *MMFile;
	TMenuItem *MMView;
	TMenuItem *MMTools;
	TMenuItem *MMHelp;
	TMenuItem *MManual;
	TMenuItem *MMAbout;
	TMenuItem *N_open_conf;
	TMenuItem *N_create_conf;
	TMenuItem *N_save_conf;
	TImageList *ImageList_Mtoolbar;
	TToolButton *ToolButton_test;
	TToolButton *ToolButton4;
	TToolButton *ToolButton7;
	TToolButton *ToolButton8;
	TToolButton *ToolButton9;
	TToolButton *ToolButton_Start;
	TToolButton *ToolButton11;
	TToolButton *ToolButton12;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *N_menu_test;
	TMenuItem *N_menu_data_save;
	TMenuItem *N_menu_tools;
	TMenuItem *N3;
	TImageList *ImageList_Mtree;
	TTimer *Timer_seconds_system_event;
	TTimer *Timer_system_run;
	TPageControl *MPageControl;
	TTabSheet *TabSheet_meas_table;
	TPanel *Panel_meas_table;
	TStringGrid *StringGrid_meas;
	TPageControl *LPageControl_console;
	TTabSheet *TabSheet_meas_control;
	TPanel *Panel_meas_control;
	TLabel *Label_X;
	TLabel *Label_Y;
	TButton *Button_record;
	TEdit *Edit_measX;
	TEdit *Edit_measY;
	TTabSheet *TabSheet_console;
	TListBox *ListBox_Console;
	TPopupMenu *PopupMenu_system;
	TMenuItem *N_system_adjust;
	TMenuItem *N_add_place;
	TMenuItem *N_port_adjust;
	TMenuItem *N_sensor_adjust;
	TMenuItem *N_create_meas;
	TMenuItem *N_place_delete;
	TMenuItem *N_place_adjust;
	TMenuItem *N_drill_add;
	TMenuItem *N_drill_delete;
	TMenuItem *N_meas_add;
	TMenuItem *N_meas_delete;
	TMenuItem *N_drill_adjust;
	TMenuItem *N_meas_adjust;
	TGroupBox *GroupBox_sko;
	TTrackBar *TrackBar_sko;
	TEdit *Edit_sko;
	TLabel *Label_skomin;
	TLabel *Label_skomax;
	TLabel *Label_place;
	TLabel *Label_drill;
	TLabel *Label_end;
	TEdit *Edit_meas_place;
	TEdit *Edit_meas_drill;
	TEdit *Edit_meas_time;
	TButton *Button_finish;
	TLabel *Label_tstart;
	TEdit *Edit_time_create;
	TTimer *Timer_set_screen;
	TTabSheet *TabSheet_charts_v;
	TPanel *Panel_charts_v;
	TPanel *Panel_chart_x_v;
	TSplitter *Splitter4;
	TPanel *Panel_chart_y_v;
	TSplitter *Splitter5;
	TPanel *Panel_chart_r;
	TChart *Chart_x_v;
	TChart *Chart_y_v;
	TChart *Chart_r;
	TOpenDialog *OpenDialog;
	TSaveDialog *SaveDialog;
	TTimer *Timer_excel_export_progress;
	TTabSheet *TabSheet_charts;
	TPanel *Panel_chats;
	TPanel *Panel_chartx_h;
	TPanel *Panel_charty_h;
	TSplitter *Splitter6;
	TChart *Chart_x_h;
	THorizLineSeries *Series1;
	TLineSeries *Series2;
	TLineSeries *Series3;
	TLineSeries *Series4;
	TLineSeries *Series5;
	TLineSeries *Series6;
	TLineSeries *Series7;
	TLineSeries *Series8;
	TLineSeries *Series9;
	TLineSeries *Series10;
	TLineSeries *Series21;
	TChart *Chart_y_h;
	TLineSeries *Series11;
	TLineSeries *Series12;
	TLineSeries *Series13;
	TLineSeries *Series14;
	TLineSeries *Series15;
	TLineSeries *Series16;
	TLineSeries *Series17;
	TLineSeries *Series18;
	TLineSeries *Series19;
	TLineSeries *Series20;
	TLineSeries *Series22;
	TToolButton *ToolButton_save;
	TToolButton *ToolButton_save_as;
	TToolButton *ToolButton_create;
	TToolButton *ToolButton_open;
	TToolButton *ToolButton_collapse;
	TToolButton *ToolButton1;
	void __fastcall MMFileDrawItem(TObject *Sender, TCanvas *ACanvas, TRect &ARect,
		  bool Selected);
	void __fastcall MMPropDrawItem(TObject *Sender, TCanvas *ACanvas, TRect &ARect,
          bool Selected);
	void __fastcall MMViewDrawItem(TObject *Sender, TCanvas *ACanvas, TRect &ARect,
		  bool Selected);
	void __fastcall MMToolsDrawItem(TObject *Sender, TCanvas *ACanvas, TRect &ARect,
		  bool Selected);
	void __fastcall MMHelpDrawItem(TObject *Sender, TCanvas *ACanvas, TRect &ARect,
		  bool Selected);
	void __fastcall ToolButton_createClick(TObject *Sender);
	void __fastcall ToolButton9Click(TObject *Sender);
	void __fastcall ToolButton8Click(TObject *Sender);
	void __fastcall ToolButton4Click(TObject *Sender);
	void __fastcall ToolButton_StartClick(TObject *Sender);
	void __fastcall Timer_seconds_system_eventTimer(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Timer_system_runTimer(TObject *Sender);
	void __fastcall StringGrid_measDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
          TGridDrawState State);
	void __fastcall Button_recordClick(TObject *Sender);
	void __fastcall StringGrid_measDblClick(TObject *Sender);
	void __fastcall PopupMenu_systemPopup(TObject *Sender);
	void __fastcall N_system_adjustClick(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall N_add_placeClick(TObject *Sender);
	void __fastcall N_port_adjustClick(TObject *Sender);
	void __fastcall N_sensor_adjustClick(TObject *Sender);
	void __fastcall N_place_adjustClick(TObject *Sender);
	void __fastcall N_place_deleteClick(TObject *Sender);
	void __fastcall TreeView_systemDblClick(TObject *Sender);
	void __fastcall MMAboutClick(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N_drill_addClick(TObject *Sender);
	void __fastcall N_drill_adjustClick(TObject *Sender);
	void __fastcall N_drill_deleteClick(TObject *Sender);
	void __fastcall N_meas_addClick(TObject *Sender);
	void __fastcall N_meas_adjustClick(TObject *Sender);
	void __fastcall N_meas_deleteClick(TObject *Sender);
	void __fastcall TrackBar_skoChange(TObject *Sender);
	void __fastcall TreeView_systemClick(TObject *Sender);
	void __fastcall Button_finishClick(TObject *Sender);
	void __fastcall TabSheet_charts_oldShow(TObject *Sender);
	void __fastcall TabSheet_meas_tableShow(TObject *Sender);
	void __fastcall Timer_set_screenTimer(TObject *Sender);
	void __fastcall Panel_chats_oldResize(TObject *Sender);
	void __fastcall Chart_x_hDblClick(TObject *Sender);
	void __fastcall Panel_chartx_h_oldDblClick(TObject *Sender);
	void __fastcall TabSheet_charts_vShow(TObject *Sender);
	void __fastcall N_create_confClick(TObject *Sender);
	void __fastcall N_open_confClick(TObject *Sender);
	void __fastcall N_save_confClick(TObject *Sender);
	void __fastcall ToolButton11Click(TObject *Sender);
	void __fastcall ToolButton12Click(TObject *Sender);
	void __fastcall Timer_excel_export_progressTimer(TObject *Sender);
	void __fastcall Panel1DblClick(TObject *Sender);
	void __fastcall Chart_y_hDblClick(TObject *Sender);
	void __fastcall ToolButton_testClick(TObject *Sender);
	void __fastcall Chart_x_vDblClick(TObject *Sender);
	void __fastcall Chart_y_vDblClick(TObject *Sender);
	void __fastcall Chart_rDblClick(TObject *Sender);
	void __fastcall Chart_x_hMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall Chart_x_vMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall Chart_y_vMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall Chart_rMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall MManualClick(TObject *Sender);
	void __fastcall ToolButton7Click(TObject *Sender);
	void __fastcall ToolButton_saveClick(TObject *Sender);
	void __fastcall ToolButton_openClick(TObject *Sender);
	void __fastcall ToolButton_collapseClick(TObject *Sender);
	void __fastcall ToolButton1Click(TObject *Sender);
	void __fastcall TreeView_systemMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);

private:	// User declarations
	void Test1();
	void CurrentTimeView();
	void ApplicationInit();
	void Console(WideString obj, WideString msg);
	void SystemInit();
	void SetMenuFont(TRect &ARect, TCanvas* ACanvas, WideString text);
public:		// User declarations
	__fastcall TFMain(TComponent* Owner);

	void ViewSelectedMeas(void);
	void ViewSelectedDrill(void);
	void SetWindowSize(int par);
	void DevideScreen(int par);
	void UnselectMeas(void);
	void UnselectDrill(void);
	int ClearTable(void);

	TGBISystem* GBISystem;

	void ShowChartHint_v(TChart* chart, int X, int Y);
	void VirtKey_TouchIn_On(void);
	void VirtKey_TouchIn_Off(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TFMain *FMain;
//---------------------------------------------------------------------------
#endif
