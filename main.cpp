#include "main.h"
#include "parameters.h"
#include "functions.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printInstructions();
        return 0;
    }
    CompressionParams params = parseCommandLine(argc, argv);
    solve(params);
    return 0;
}