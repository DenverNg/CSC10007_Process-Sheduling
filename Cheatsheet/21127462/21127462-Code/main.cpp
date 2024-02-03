#include "Schedule.h"


int main(int argc, char** argv)
{
	if (argc > 1)  //command line arguments
	{
		
		Schedule* s = new Schedule(argv[1]);
		s->run();
		s->exportOutput(argv[2]);

		delete s;

	}
	else  //run exe
	{
		
		Schedule* s = new Schedule("input.txt");

		s->run();

		s->printCpuChart();
		s->printIoChart();
		s->printTT();
		s->printWT();

		delete s;
	}

	return 0;
}