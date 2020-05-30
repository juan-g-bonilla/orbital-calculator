#ifndef CONSOLEHANDLER_HPP
#define CONSOLEHANDLER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>

#include "Enviroment.hpp"

enum CommArgType {STRING, NUMBER};

/// Outputs to @param os the name of the enum in the format "[type_name]
std::ostream& operator<<(std::ostream& os, CommArgType t);

class CommArgument
{
    public:
    CommArgument(CommArgType type, std::string userInput);
    CommArgument(CommArgType type, double userInput);

    /** Return value stored in the argument as a String.
     *  @throw std::invalid_argument if getType() != STRING
     */
    std::string getString();

    /** Return value stored in the argument as a double.
     *  @throw std::invalid_argument if getType() != NUMBER
     */
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
    /** @param command The non-argument part of the command
     *  @param argTypes The argument types that are accepted in order of specification
     *  @param help A brief description of the command functionality
     *  @param function The functionality of the command
     */
    Command(std::string command, std::vector<CommArgType> argTypes, std::string help,
            std::function<std::string (Enviroment&, std::vector<CommArgument>)> function);

    /// @return The non-argument part of the command
    std::string getCommand();

    /// @return The argument types that are accepted in order of specification
    std::vector<CommArgType> getArgumentTypes();

    /// @return A brief description of the command functionality
    std::string getHelp();

    /// @return A user friendly representation of the correct usage of the command
    std::string getUsage();

    /// @return Calls the actual function in the given enviroment with passed arguments
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