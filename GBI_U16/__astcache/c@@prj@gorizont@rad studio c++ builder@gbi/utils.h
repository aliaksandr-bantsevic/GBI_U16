//---------------------------------------------------------------------------

#ifndef utilsH
#define utilsH
//---------------------------------------------------------------------------
#endif

#include <vcl.h>
#include <iostream>
#include <string.h>


/*
	Set icon for tree item
*/

#define SYSTEM_ICON_STATES_WIDE         3
#define SYSTEM_ICON_TYPES_WIDE          6

#define SYSTEM_NODE_STATE_NORMAL        0
#define SYSTEM_NODE_STATE_OFFLINE       1
#define SYSTEM_NODE_STATE_ALARM  	    2

#define SYSTEM_NODE_SYSTEM		        0
#define SYSTEM_NODE_PLACE		        1
#define SYSTEM_NODE_DRILL		        2
#define SYSTEM_NODE_MEAS		        3
#define SYSTEM_NODE_PORT                4
#define SYSTEM_NODE_SENSOR              5

extern int utils_set_tree_node_view(TTreeNode* node, int node_type, int node_state);

/*
	Different useful tools
*/

extern AnsiString utils_int_to_str(int i, int d);
extern bool utils_confirm_operation_save_adjust(void);
extern void utils_ShowMessage(AnsiString s);

extern WORD Calc_CRC(WORD start, WORD stop, int n,BYTE *b);
extern WORD Calc_CRC16(int n,BYTE *b);
extern WORD Calc_CITT16(int n,BYTE *b);
extern WORD Calc_CSum(int n,BYTE *b);
extern WORD CRC16CCITT(WORD n,BYTE *b);
