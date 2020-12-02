#include "../include/AgendaUI.hpp"
#include <signal.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
using namespace std;
AgendaUI agenda;

int main() {
    agenda.OperationLoop();
    return 0;
}