#include "ConsoleHandler.hpp"
#include <sstream>
#include <stdexcept>
#include <limits>
#include <ios>
#include <fstream>

/* ConsoleHandler */
ConsoleHandler::ConsoleHandler(Enviroment& env, std::istream& input, std::ostream& output) 
: env(env), input(input), output(output) 
{
    emplace("initial x", {NUMBER}, "Sets initial x-coordinate of orbiting body in km",
        [](Enviroment& env, std::vector<CommArgument> args) 
        {
            env.getEphemerisEntryBuilder().setX(args[0].getNumber());
            if (env.getEphemerisEntryBuilder().isValid())
            {
                env.getEphemeris().setInitialEntry(env.getEphemerisEntryBuilder().build());
                return "Initial conditions are now fully defined";
            }
            else return "Coordinate set";
        });

    emplace("initial y", {NUMBER}, "Sets initial y-coordinate of orbiting body in km",
        [](Enviroment& env, std::vector<CommArgument> args) 
        {
            env.getEphemerisEntryBuilder().setY(args[0].getNumber());
            if (env.getEphemerisEntryBuilder().isValid())
            {
                env.getEphemeris().setInitialEntry(env.getEphemerisEntryBuilder().build());
                return "Initial conditions are now fully defined";
            }
            else return "Coordinate set";
        });

    emplace("initial z", {NUMBER}, "Sets initial z-coordinate of orbiting body in km",
        [](Enviroment& env, std::vector<CommArgument> args) 
        {
            env.getEphemerisEntryBuilder().setZ(args[0].getNumber());
            if (env.getEphemerisEntryBuilder().isValid())
            {
                env.getEphemeris().setInitialEntry(env.getEphemerisEntryBuilder().build());
                return "Initial conditions are now fully defined";
            }
            else return "Coordinate set";
        });

    emplace("initial vx", {NUMBER}, "Sets initial x-coordinate of velocity of orbiting body in km/s",
        [](Enviroment& env, std::vector<CommArgument> args) 
        {
            env.getEphemerisEntryBuilder().setVx(args[0].getNumber());
            if (env.getEphemerisEntryBuilder().isValid())
            {
                env.getEphemeris().setInitialEntry(env.getEphemerisEntryBuilder().build());
                return "Initial conditions are now fully defined";
            }
            else return "Coordinate set";
        });

    emplace("initial vy", {NUMBER}, "Sets initial y-coordinate of velocity of orbiting body in km/s",
        [](Enviroment& env, std::vector<CommArgument> args) 
        {
            env.getEphemerisEntryBuilder().setVy(args[0].getNumber());
            if (env.getEphemerisEntryBuilder().isValid())
            {
                env.getEphemeris().setInitialEntry(env.getEphemerisEntryBuilder().build());
                return "Initial conditions are now fully defined";
            }
            else return "Coordinate set";
        });

    emplace("initial vz", {NUMBER}, "Sets initial z-coordinate of velocity of orbiting body in km/s",
        [](Enviroment& env, std::vector<CommArgument> args) 
        {
            env.getEphemerisEntryBuilder().setVz(args[0].getNumber());
            if (env.getEphemerisEntryBuilder().isValid())
            {
                env.getEphemeris().setInitialEntry(env.getEphemerisEntryBuilder().build());
                return "Initial conditions are now fully defined";
            }
            else return "Coordinate set";
        });

    emplace("initial coord", {NUMBER, NUMBER, NUMBER, NUMBER, NUMBER, NUMBER}, 
        "Sets initial coordinates of orbiting body and velocity in km and km/s in this order: x, y, z, vx, vy, vz",
        [](Enviroment& env, std::vector<CommArgument> args) 
        {   
            env.getEphemerisEntryBuilder().setX(args[0].getNumber());
            env.getEphemerisEntryBuilder().setY(args[1].getNumber());
            env.getEphemerisEntryBuilder().setZ(args[2].getNumber());
            env.getEphemerisEntryBuilder().setVx(args[3].getNumber());
            env.getEphemerisEntryBuilder().setVy(args[4].getNumber());
            env.getEphemerisEntryBuilder().setVz(args[5].getNumber());

            if (env.getEphemerisEntryBuilder().isValid())
            {
                env.getEphemeris().setInitialEntry(env.getEphemerisEntryBuilder().build());
                return "Initial conditions are now fully defined";
            }
            else return "Coordinate set";
        });

    emplace("initial a", {NUMBER}, "Sets initial semi-major axis of orbiting body in km",
        [](Enviroment& env, std::vector<CommArgument> args) 
        {
            try
            {
                env.getEphemerisEntryBuilder().setA(args[0].getNumber());
            }
            catch(std::invalid_argument& ex)
            {
                return ex.what();
            }

            if (env.getEphemerisEntryBuilder().isValid())
            {
                env.getEphemeris().setInitialEntry(env.getEphemerisEntryBuilder().build());
                return "Initial conditions are now fully defined";
            }
            else return "Element set";
        });

    emplace("initial e", {NUMBER}, "Sets initial eccentricity of orbiting body",
        [](Enviroment& env, std::vector<CommArgument> args) 
        {
            try
            {
                env.getEphemerisEntryBuilder().setE(args[0].getNumber());
            }
            catch(std::invalid_argument& ex)
            {
                return ex.what();
            }            
            
            if (env.getEphemerisEntryBuilder().isValid())
            {
                env.getEphemeris().setInitialEntry(env.getEphemerisEntryBuilder().build());
                return "Initial conditions are now fully defined";
            }
            else return "Element set";
        });

    emplace("initial i", {NUMBER}, "Sets initial inclination axis of orbiting body in degrees",
        [](Enviroment& env, std::vector<CommArgument> args) 
        {
            env.getEphemerisEntryBuilder().setA(args[0].getNumber());
            if (env.getEphemerisEntryBuilder().isValid())
            {
                env.getEphemeris().setInitialEntry(env.getEphemerisEntryBuilder().build());
                return "Initial conditions are now fully defined";
            }
            else return "Element set";
        });

    emplace("initial lon", {NUMBER}, "Sets initial longitude of ascending node of orbiting body in degrees",
        [](Enviroment& env, std::vector<CommArgument> args) 
        {
            env.getEphemerisEntryBuilder().setLongitudeAscendingNode(args[0].getNumber());
            if (env.getEphemerisEntryBuilder().isValid())
            {
                env.getEphemeris().setInitialEntry(env.getEphemerisEntryBuilder().build());
                return "Initial conditions are now fully defined";
            }
            else return "Element set";
        });

    emplace("initial arg", {NUMBER}, "Sets initial argument of the perigee of orbiting body in degrees",
        [](Enviroment& env, std::vector<CommArgument> args) 
        {
            env.getEphemerisEntryBuilder().setArgumentPerigee(args[0].getNumber());
            if (env.getEphemerisEntryBuilder().isValid())
            {
                env.getEphemeris().setInitialEntry(env.getEphemerisEntryBuilder().build());
                return "Initial conditions are now fully defined";
            }
            else return "Element set";
        });

    emplace("initial anom", {NUMBER}, "Sets true anomaly of orbiting body in degrees",
        [](Enviroment& env, std::vector<CommArgument> args) 
        {
            env.getEphemerisEntryBuilder().setTrueAnomaly(args[0].getNumber());
            if (env.getEphemerisEntryBuilder().isValid())
            {
                env.getEphemeris().setInitialEntry(env.getEphemerisEntryBuilder().build());
                return "Initial conditions are now fully defined";
            }
            else return "Element set";
        });

    emplace("initial display", {}, "Displays the currently set parameters of initial conditions",
        [](Enviroment& env, std::vector<CommArgument> args) 
        {
            std::stringstream stream;
            env.getEphemerisEntryBuilder().output(stream);
            return stream.str();
        });

    emplace("env tf", {NUMBER}, "Sets final reference time of the enviroment in seconds",
        [](Enviroment& env, std::vector<CommArgument> args) 
        {
            try
            {
                env.setFinalTime(args[0].getNumber());
            }
            catch(std::invalid_argument& ex)
            {
                return ex.what();
            }

            return "Final time set";
        });

    emplace("env dt", {NUMBER}, "Sets time step of integration in seconds",
        [](Enviroment& env, std::vector<CommArgument> args) 
        {
            try
            {
                env.setTimeStep(args[0].getNumber());
            }
            catch(std::invalid_argument& ex)
            {
                return ex.what();
            }

            return "Time step set";
        });

    emplace("central grav", {NUMBER}, "Sets standard gravitational paramater of the central body in km^3/s^2",
        [](Enviroment& env, std::vector<CommArgument> args) 
        {
            try
            {
                env.getCentralBody().setGravitationalParameter(args[0].getNumber());
            }
            catch(std::invalid_argument& ex)
            {
                return ex.what();
            }

            return "Gravitational paramater set";
        });

    emplace("propagate", {}, "Propagates the orbit",
        [](Enviroment& env, std::vector<CommArgument> args) 
        {
            int code = env.propagate();
            return env.getPropagator()->getExitMessage(code);
        });

    emplace("results to file", {STRING}, "Sets position and velocity data of ephemeris in file with given name",
        [](Enviroment& env, std::vector<CommArgument> args) 
        {
            std::ofstream file{args[0].getString(), std::ios::trunc};

            if (file.is_open())
            {
                env.getEphemeris().output(file, false);
                file.close();
                return "Succesfully output results to file";
            }

            return "Unable to open file";
        });

    emplace("results at", {NUMBER}, "Outputs position and velocity data at closest time calculated to the console",
        [](Enviroment& env, std::vector<CommArgument> args) 
        {
            EphemerisEntry entry;
            try
            {
                entry = env.getEphemeris().when(args[0].getNumber());
            }
            catch(std::invalid_argument& ex)
            {
                std::string message{ex.what()};
                return message;
            }

            std::stringstream ss;
            entry.output(ss, true);
            return ss.str();
        });

    emplace("results reset", {}, "Deletes propagated orbit",
        [](Enviroment& env, std::vector<CommArgument> args) 
        {
            env.getEphemeris().reset();
            return "Deleted propagated orbit";
        });
    
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
            else if ((fC >= '0' && fC <= '9') || fC == '-') // Is number
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

