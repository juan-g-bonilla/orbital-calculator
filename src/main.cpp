#include "ConsoleHandler.hpp"

int main() 
{
    Enviroment enviroment;
    ConsoleHandler handler{enviroment, std::cin, std::cout};
    handler.startQuery();
}