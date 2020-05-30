#ifndef CONSOLEHANDLER_HPP
#define CONSOLEHANDLER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>

#include "Enviroment.hpp"

enum CommArgType {STRING, NUMBER};

std::ostream& operator<<(std::ostream& os, CommArgType t);

class CommArgument
{
    public:
    CommArgument(CommArgType type, std::string userInput);
    CommArgument(CommArgType type, double userInput);

    std::string getString();
    double getNumber();
    CommArgType getType();

    private:
    CommArgType type;
    std::string inputString;
    double inputNumber;
};

class Command
{
    public:
    Command(std::string command, std::vector<CommArgType> argTypes, std::string help,
            std::function<std::string (Enviroment&, std::vector<CommArgument>)> function);


    std::string getCommand();
    std::vector<CommArgType> getArgumentTypes();
    std::string getHelp();
    std::string getUsage();
    std::string call(Enviroment& env, std::vector<CommArgument> arguments);

    private:
    std::string command;
    std::vector<CommArgType> argTypes;
    std::string help;
    std::function<std::string (Enviroment&, std::vector<CommArgument>)> function;
};

class ConsoleHandler
{
    public:
    ConsoleHandler(Enviroment& env, std::istream& input, std::ostream& output);

    /// Start infinite loop where user is asked for commands
    void startQuery();

    private:
    void emplace(std::string command, vector<CommArgType> argTypes, std::string help, 
        std::function<std::string (Enviroment&, std::vector<CommArgument>)> function);

    Enviroment& env;
    std::istream& input;
    std::ostream& output;
    std::map<std::string, Command> commands;
};

#endif