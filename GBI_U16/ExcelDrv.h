//---------------------------------------------------------------------------

#ifndef ExcelDrvH
#define ExcelDrvH
//---------------------------------------------------------------------------
#include      <ComObj.hpp>
#include      <utilcls.h>
#include 	  "defs.h"


bool OpenExcelReportTable(int sheets);
bool SaveExcelReport(AnsiString spath);
bool SetExcelColumnWidth(int row, int col, int w);
bool SetExcelCellFontBold(int row, int col);
bool SetExellCellColor(int row, int col, int color);
bool SetExcelRangeBorder(int row1, int col1, int row2, int col2, int line);
bool ExcelMergeAndWrite(int row1, int col1, int row2, int col2, AnsiString s);
bool WriteExcelReportCell(int row, int col, AnsiString sval);
bool OpenExcelReportSheet(AnsiString sheetname, int sheet);

#endif
