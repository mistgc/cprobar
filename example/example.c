#include "../bar.h"

int main() {
	int a = 0, b = 100;

	while(1) {
		programBar("Hello, world!", 1, b);
		usleep(80000);
		a++;
		if(a == 100) break;
	}
	freeProgramBar();
	
	return 0;
}
