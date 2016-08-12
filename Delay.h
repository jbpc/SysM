/*	#include <sys/select.h>
 */
char Delay(unsigned short Second, unsigned short uSecond){
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ Write
	struct timeval Timer;
	Timer.tv_sec	= Second;
	Timer.tv_usec	= uSecond;
	if (select(0, NULL, NULL, NULL, &Timer) == -1){
		return 'X';
	}
	return 'V';
}
