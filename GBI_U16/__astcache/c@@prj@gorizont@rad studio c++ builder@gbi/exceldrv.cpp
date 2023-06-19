//---------------------------------------------------------------------------

#pragma hdrstop

#include "ExcelDrv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


//Excel report table
Variant mExcel;
Variant mSheet;

bool ShowExcel = false;
bool FormatCellsOn = false;

char* XCOL[]={

(char*)"-",
(char*)"A",(char*)"B",(char*)"C",(char*)"D",(char*)"E",(char*)"F",(char*)"G",(char*)"H",(char*)"I",(char*)"J",(char*)"K",(char*)"L",(char*)"M",(char*)"N",(char*)"O",(char*)"P",(char*)"Q",(char*)"R",(char*)"S",(char*)"T",(char*)"U",(char*)"V",(char*)"W",(char*)"X",(char*)"Y",(char*)"Z",
(char*)"AA",(char*)"AB",(char*)"AC",(char*)"AD",(char*)"AE",(char*)"AF",(char*)"AG",(char*)"AH",(char*)"AI",(char*)"AJ",(char*)"AK",(char*)"AL",(char*)"AM",(char*)"AN",(char*)"AO",(char*)"AP",(char*)"AQ",(char*)"AR",(char*)"AS",(char*)"AT",(char*)"AU",(char*)"AV",(char*)"AW",(char*)"AX",
(char*)"AY",(char*)"AZ",(char*)"BA",(char*)"BB",(char*)"BC",(char*)"BD",(char*)"BE",(char*)"BF",(char*)"BG",(char*)"BH",(char*)"BI",(char*)"BJ",(char*)"BK",(char*)"BL",(char*)"BM",(char*)"BN",(char*)"BO",(char*)"BP",(char*)"BQ",(char*)"BR",(char*)"BS",(char*)"BT",(char*)"BU",(char*)"BV",
(char*)"BW",(char*)"BX",(char*)"BY",(char*)"BZ",(char*)"CA",(char*)"CB",(char*)"CC",(char*)"CD",(char*)"CE",(char*)"CF",(char*)"CG",(char*)"CH",(char*)"CI",(char*)"CJ",(char*)"CK",(char*)"CL",(char*)"CM",(char*)"CN",(char*)"CO",(char*)"CP",(char*)"CQ",(char*)"CR",(char*)"CS",(char*)"CT",
(char*)"CU",(char*)"CV",(char*)"CW",(char*)"CX",(char*)"CY",(char*)"CZ",
};


bool OpenExcelReportTable(int sheets)
{

		bool bres = true;

		try
		{
				mExcel = CreateOleObject("Excel.Application");

				if (ShowExcel)  mExcel.OlePropertySet("Visible", True);
				else            mExcel.OlePropertySet("Visible", False);

				mExcel.OlePropertySet("SheetsInNewWorkbook",sheets);
				mExcel.OlePropertyGet("WorkBooks").OleProcedure("Add");

				//Variant mSheet;
				//mSheet = mExcel.OlePropertyGet("Worksheets").OlePropertyGet("Item",1);

				//Sleep(1);

				//mSheet.OlePropertySet("Name",WideString("Æåëòûé ëèñò"));

		}
		catch(...)
		{
				bres = false;
		}


		return bres;
}


bool OpenExcelReportSheet(AnsiString sheetname, int sheet)
{

		bool bres = true;

		try
		{
				//mExcel.OlePropertyGet("WorkBooks").OleProcedure("Add");

				//mExcel.OlePropertyGet("WorkBooks").OlePropertyGet("WorkSheets").OleProcedure("Add");
				//mSheet = mExcel.OlePropertyGet("ActiveSheet");

				mSheet = mExcel.OlePropertyGet("Worksheets").OlePropertyGet("Item",sheet);
				mSheet.OlePropertySet("Name",WideString(sheetname));
				mSheet.OleProcedure("Activate");

		}
		catch(...)
		{
				bres = false;
		}


		return bres;
}


bool WriteExcelReportCell(int row, int col, AnsiString sval)
{
		//TODO: Add your source code here
		bool bres = true;

		try
		{
				//mExcel.OlePropertyGet("ActiveSheet").OlePropertyGet("Cells", row, WideString(XCOL[col])).OlePropertySet(WideString("NumberFormat"),WideString("@"));

				mExcel.OlePropertyGet("ActiveSheet").OlePropertyGet("Cells", row, WideString(XCOL[col])).OlePropertySet(WideString("NumberFormat"),WideString("0,00"));

				mExcel.OlePropertyGet("ActiveSheet").OlePropertyGet("Cells", row, WideString(XCOL[col])).OlePropertySet(WideString("Value"),WideString(sval));

				/*
				AnsiString s1 = "Value";
				AnsiString s2 = "1234567890";

				AnsiString& ss1 = s1;
				AnsiString& ss2 = s2;


		Variant v1, v2, v3;
		v1 = mExcel.OlePropertyGet("ActiveSheet");
		v2 = v1.OlePropertyGet("Cells", 2,2);
		v2.OlePropertySet(WideString("NumberFormat"),WideString("@"));
		v2.OlePropertySet(WideString("Value"),WideString("123456"));
				  */


		 //v1 = v.OlePropertyGet("Cells", 2, 2);
		 //v2 = v1.OlePropertySet("Value", "sdfasdggdf");


		}
		catch(...)
		{
				 bres = false;
		}

		return bres;

}

bool SaveExcelReport(AnsiString spath)
{
		//TODO: Add your source code here
		bool bres=true;

		try
		{
		  mExcel.OlePropertyGet("WorkBooks", 1).OleProcedure(WideString("SaveAs"),WideString(spath));
		  mExcel.OlePropertyGet("ActiveWindow").OleProcedure("Close");
		  mExcel.OleProcedure(WideString("Quit"));
		}
		catch(...)
		{

		}


		AnsiString s("");
		s.printf("Îò÷åò ñîõðàíåí â ôàéëå %s",spath.c_str());
		//WideChar mes[1024];
		//StringToWideChar(s.c_str(),mes,1024);
		utils_ShowMessage(s);

		return bres;
}


bool SetExcelColumnWidth(int row, int col, int w)
{
        //TODO: Add your source code here
		bool res = true;

        try
        {
			 mExcel.OlePropertyGet("ActiveSheet").OlePropertyGet("Cells", row, XCOL[col]).OlePropertySet("ColumnWidth",w);
        }
        catch(...)
        {
              res=false;
        }

        return res;
}

bool SetExcelCellFontBold(int row, int col)
{
		if (FormatCellsOn == false) return false;

        //TODO: Add your source code here
        bool res=true;

        try
        {
             mExcel.OlePropertyGet("ActiveSheet").OlePropertyGet("Cells", row, XCOL[col]).OlePropertyGet("Font").OlePropertySet("Bold",true);
        }
        catch(...)
        {
              res=false;
        }

        return res;

}

//https://docs.microsoft.com/en-us/office/vba/api/excel.colorindex
bool SetExellCellColor(int row, int col, int color)
{
		if (FormatCellsOn == false) return false;

        //TODO: Add your source code here
        bool res=true;

        try
        {
             mExcel.OlePropertyGet("ActiveSheet").OlePropertyGet("Cells", row, XCOL[col]).OlePropertyGet("Interior").OlePropertySet("ColorIndex",color);
        }
        catch(...)
        {
              res=false;
        }

        return res;

}

bool SetExcelRangeBorder(int row1, int col1, int row2, int col2, int line)
{
		if (FormatCellsOn == false) return false;

        //TODO: Add your source code here
        bool res=false;

        Variant vVarCell;
        AnsiString srange("");
        AnsiString s1=XCOL[col1];
        AnsiString s2=XCOL[col2];
		srange.printf("%s%d:%s%d",s1.c_str(),row1,s2.c_str(),row2);

              try
              {
                      vVarCell=mExcel.OlePropertyGet("ActiveSheet").OlePropertyGet("Range",srange.c_str());
                      for (int b=7; b<=10; b++)
                      {
                        vVarCell.OlePropertyGet("Borders",b).OlePropertySet("Weight",line);
                      }
              }
              catch(...)
              {
                      res=false;
              }

              return res;
}

bool ExcelMergeAndWrite(int row1, int col1, int row2, int col2, AnsiString s)
{
        //TODO: Add your source code here
        bool res=true;

        try
        {
                Variant vVarCell;
                AnsiString srange("");
                AnsiString s1=XCOL[col1];
                AnsiString s2=XCOL[col2];
				srange.printf("%s%d:%s%d",s1.c_str(),row1,s2.c_str(),row2);

                vVarCell=mExcel.OlePropertyGet("ActiveSheet").OlePropertyGet("Range",srange.c_str());
                vVarCell.OleProcedure("Merge");

                WriteExcelReportCell(row1,col1,s);
		}
		catch(...)
        {
                res=false;
        }

        return res;
}

