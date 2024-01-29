#include"function.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cerr << "Usage: " << argv[0] << " <inputFile> <outputFile>\n";
        return EXIT_FAILURE;
    }

    string inputFile = argv[1];
    string outputFile = argv[2];

    Scheduler scheduler(inputFile, outputFile);

    cout << "\nProcess scheduling complete. Output written to " << outputFile << endl;

    return EXIT_SUCCESS;
}