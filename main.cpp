
#include <iostream>

#include "App/App.h"

const int WIDTH = 224;
const int HEIGHT = 288;
const int MAG = 3;

using namespace std;

int main(int argc, char *argv[])
{
    if (App::Singleton().Init(WIDTH, HEIGHT, MAG)) {
        App::Singleton().Run();
    }


    return 0;
}

