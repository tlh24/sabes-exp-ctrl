#ifndef VISWINDOWSACTIONLOG_H
#define VISWINDOWSACTIONLOG_H

#define VISWIN_MAX_LOG_ACTIONS 50000
#define VISWIN_MAX_LOG_PARAMS  3
#define VISWIN_COUNTER_BITS    8

#define ACTION_LOGERR    -1
#define ACTION_DELETE     0
#define ACTION_CREATE     1
#define ACTION_SHOW       2
#define ACTION_POS        3
#define ACTION_Z          4
#define ACTION_COLOR      5
#define ACTION_ALPHA      6
#define ACTION_FILL       7
#define ACTION_POINTS     8
#define ACTION_RADIUS     9
#define ACTION_SCALE     10
#define ACTION_ANGLE     11
#define ACTION_EXACT     12
#define ACTION_IMAGE     13
#define ACTION_TEXT      14
#define ACTION_UNDERLINE 15
#define ACTION_ITALIC    16
#define ACTION_WEIGHT    17
#define ACTION_FONT      18
#define ACTION_ARRAYDATA 19
#define ACTION_LINESTIPPLE			20
#define ACTION_LINESTIPPLEFACTOR	21
#define ACTION_LINEWIDTH			22
#define ACTION_POINTSIZE			23
#define ACTION_DRAWMODE				24

#define logToFile(P) /*{							\
	FILE *f = fopen("C:\\vislog.txt", "a+");	\
	fprintf P;									\
	fclose(f);									\
}*/


#endif