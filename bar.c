#include "bar.h"
static char* arr = NULL; static char* fmtStr_info = NULL;
static char* fmtStr_bar = NULL;
static char* bar = NULL;
static char* label = "-\\|/";

static unsigned long g_total = 0;
static unsigned long g_block = 0;

struct Termsize getTermSize() {
	struct winsize size;
	struct Termsize out;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
	out.row = size.ws_row;
	out.col = size.ws_col;
	return out;
}

/*
 *	The first time invoke the function, it is going to initializeby itself.
 *	@ param info:		information
 *	@ param block:		The amount of data processed at one time
 *	@ param total:      The total amount of data to be processed
 *	@ return
 */
void programBar(char* info, unsigned long block, unsigned long total) {
	if(g_total == 0)
		g_total = total;
	g_block += block;

	//printf("%d, %d\n", g_block, g_total);
	Termsize size = getTermSize();
	if(size.col <= 11) {
		return;
	}else {
		if(size.col >= 111)
			size.col = 111;

	int chunk = ((double)g_block / (double)g_total) * (size.col - 11);
	//printf("%d\n", chunk);

		// Initialize arr & fmtStr.
		if(arr == NULL || fmtStr_info == NULL || fmtStr_bar == NULL || bar == NULL) {
			arr = (char*)malloc(size.col * sizeof(char));
			fmtStr_info = (char*)malloc(size.col * sizeof(char));
			fmtStr_bar = (char*)malloc(size.col * sizeof(char));
			bar = (char*)malloc(size.col * sizeof(char));

			memset(arr, 0, size.col * sizeof(char));
			memset(fmtStr_info, 0, size.col * sizeof(char));
			memset(fmtStr_bar, 0, size.col * sizeof(char));
			memset(bar, 0, (size.col - 10) * sizeof(char));

			sprintf(fmtStr_info, "%%-%ds\n", size.col);
			sprintf(fmtStr_bar, "[%%-%ds][%%d%%%%][%%c]\r", size.col - 11);
		}

		// Display info.
		printf(fmtStr_info, info);

		// Display program bar.
		for(int i = 0; i < chunk; i++) {
			bar[i] = '#';
		}
		// e.g. fmtStr_bar: "[%-100s][%d%%][%c]"
		int process = (double)chunk / (size.col-11) * 100;
		printf(fmtStr_bar, bar, process, label[chunk % 4]);
		fflush(stdout);

		if(process >= 100)
			printf("\n");

		return;
	}
}

/*
 *	Free the memory which used draw program bar.
 */
void freeProgramBar() {
	if(arr != NULL) {
		free(arr);
		arr = NULL;
	}
	if(fmtStr_info != NULL) {
		free(fmtStr_info);
		fmtStr_info = NULL;
	}
	if(fmtStr_bar != NULL) {
		free(fmtStr_bar);
		fmtStr_bar = NULL;
	}
	if(bar != NULL) {
		free(bar);
		bar = NULL;
	}
}
