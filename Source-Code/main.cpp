#include"Scheduler.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <inputFile> <outputFile>\n";
        return EXIT_FAILURE;
    }

    string inputFile = argv[1];
    string outputFile = argv[2];

    Scheduler *s = new Scheduler(argv[1]);
    s->run();
    s->exportOutput(argv[2]);

    delete s;

    cout << "\nProcess scheduling complete. Output written to " << outputFile << endl;

    return EXIT_SUCCESS;
}