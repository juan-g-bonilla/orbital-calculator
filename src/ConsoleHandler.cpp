#include "ConsoleHandler.hpp"
#include <sstream>
#include <stdexcept>
#include <limits>
#include <ios>

/* ConsoleHandler */
ConsoleHandler::ConsoleHandler(Enviroment& env, std::istream& input, std::ostream& output) 
: env(env), input(input), output(output) 
{
    
}

void ConsoleHandler::emplace(std::string command, vector<CommArgType> argTypes, std::string help, 
        std::function<std::string (Enviroment&, std::vector<CommArgument>)> function)
{
    commands.emplace(command, Command{command, std::move(argTypes), help, std::move(function)});
}

void ConsoleHandler::startQuery()
{
    output << "Enter command \"help\" for help" << std::endl << std::endl;;

    while(1)
    {
        std::string userInput, commandString, s;

        //input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(input, userInput);

        std::stringstream  sstream(userInput), scommand(commandString); 
        vector<CommArgument> args;

        bool helpCommand{false};

        while(sstream >> s) 
        {
            char fC = s.front();

            if (fC == '"' && s.back() == '"') // String input
            {
                s.erase(s.begin());
                s.pop_back();
                args.emplace_back(CommArgType::STRING, s);
            }
            else if (fC >= '0' && fC <= '9') // Is number
            {
                std::istringstream sstreamdouble(s);
                double number;
                sstreamdouble >> number;
                args.emplace_back(CommArgType::NUMBER, number);
            }
            else if (s == "help" && scommand.str().empty()) // Requesting help
            {
                helpCommand = true;
            }
            else if (s == "exit" && scommand.str().empty()) // Exit program
            {
                output << "Exiting Orbital Calculator" << std::endl;
                return;
            }
            else
            {
                scommand << s << " ";
            }
        }
        
        commandString = scommand.str();
        if (!commandString.empty())
            commandString.pop_back(); // Remove trailing " "

        if (helpCommand) // If requesting help
        {
            bool printAll{false};
            if (!commandString.empty()) // Requesting help about command
            { 
                try
                {
                    Command command = commands.at(commandString);

                    output << "Usage: " << command.getCommand();
                    for (auto type : command.getArgumentTypes())
                    {
                        output << " " << type;
                    }
                    output << std::endl << "Description: " << command.getHelp() << std::endl;
                }
                catch (std::out_of_range& ex) // Command does not exist
                {
                    output << "The command \"" << commandString << "\" is not recognized." << std::endl;
                    printAll = true;
                }
            }
            else
            {
                printAll = true;
            }

            if (printAll) // print all commands
            {
                output << "Do \"help\" and any of the following commands for more information:" << std::endl;
                for (auto pair : commands)
                {
                    output << "  " << pair.second.getCommand() << std::endl;
                }
            }
        }
        else // Not requesting help: rest of commands
        {
            try
            {
                Command command = commands.at(commandString);
                vector<CommArgType> types = command.getArgumentTypes();

                bool argsCorrect{true}; // Check if number and type of arguments is correct
                if (types.size() != args.size())
                {
                    argsCorrect = false;
                }
                else
                {
                    for (int i = 0; i < types.size(); i ++)
                    {
                        if (types[i] != args[i].getType())
                        {   
                            argsCorrect = false;
                            break;
                        }
                    }
                }

                if (argsCorrect)
                {
                    output << command.call(env, std::move(args)) << std::endl;
                }
                else
                {
                    output << "Usage: " << command.getUsage() << std::endl;
                }
            }
            catch (std::out_of_range& ex) // Command could not be found: does not exist
            {
                output << "Command \"" << commandString << "\" not found" << std::endl;
                output << "Do \"help\" for a list of commands" << std::endl;
            }
        }
        
        output << std::endl;
    }
}

/* Command */
Command::Command(
    std::string command, std::vector<CommArgType> argTypes, std::string help,
    std::function<std::string (Enviroment&, std::vector<CommArgument>)> function) :
    command(command), argTypes(std::move(argTypes)), help(help), function(std::move(function)) {};

std::string Command::getCommand()
{
    return command;
}

std::vector<CommArgType> Command::getArgumentTypes()
{
    return argTypes;
}

std::string Command::getHelp()
{
    return help;
}

std::string Command::getUsage()
{
    std::stringstream usage;
    usage << command;
    for (auto type : argTypes)
    {
        usage << " " << type;
    }
    return usage.str();
}

std::string Command::call(Enviroment& env, std::vector<CommArgument> arguments)
{
    return function(env, arguments);
}

/* CommArgType */
std::ostream& operator<<(std::ostream& os, CommArgType t)
{
    switch(t)
    {
        case STRING: os << "[string]"; break;
        case NUMBER: os << "[number]"; break;
    }
    return os;
}

/* CommArgument */
CommArgument::CommArgument(CommArgType type, std::string userInput)
: type(type), inputString(userInput) {};

CommArgument::CommArgument(CommArgType type, double userInput)
: type(type), inputNumber(userInput) {};

std::string CommArgument::getString()
{
    if (type != STRING)
        throw std::invalid_argument("Argument is not supposed to be a string");

    return inputString;
}

double CommArgument::getNumber()
{
    if (type != NUMBER)
        throw std::invalid_argument("Argument is not supposed to be a number");

    return inputNumber;
}

CommArgType CommArgument::getType()
{
    return type;
}

