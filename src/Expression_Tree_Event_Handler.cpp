/* Copyright G. Hemingway @ 2019, All Rights Reserved */
#ifndef EXPRESSION_TREE_EVENT_HANDLER_CPP
#define EXPRESSION_TREE_EVENT_HANDLER_CPP

#include "Expression_Tree_Event_Handler.h"
#include "Options.h"
#include "Reactor.h"
#include <iostream>

Expression_Tree_Event_Handler* Expression_Tree_Event_Handler::make_handler(bool verbose)
{
    if (verbose)
        return new Verbose_Expression_Tree_Event_Handler;
    else
        return new Macro_Command_Expression_Tree_Event_Handler;
}

void Expression_Tree_Event_Handler::handle_input()
{
    prompt_user();
    std::string input;
    if (!get_input(input))
        Reactor::instance()->end_event_loop();

    Expression_Tree_Command command = make_command(input);
    try {
        if (!execute_command(command))
            Reactor::instance()->end_event_loop();
        else {
            last_valid_command = command;
            if (Options::instance()->verbose())
                tree_context.state()->print_valid_commands();
        }
    } catch (Expression_Tree::Invalid_Iterator& e) {
        std::cout << "\nERROR: Bad traversal type (" << e.what() << ")\n";
        tree_context.state()->print_valid_commands();
    } catch (Expression_Tree_State::Invalid_State& e) {
        std::cout << "\nERROR: " << e.what() << std::endl;
        tree_context.state()->print_valid_commands();
    }
}

bool Expression_Tree_Event_Handler::get_input(std::string& input)
{
    std::getline(std::cin, input);
    return !std::cin.fail();
}

bool Expression_Tree_Event_Handler::execute_command(Expression_Tree_Command& command)
{
    return command.execute();
}

Expression_Tree_Event_Handler::Expression_Tree_Event_Handler()
    : tree_context()
    , command_factory(tree_context)
    , last_valid_command(new Null_Command(tree_context))
{
}

Verbose_Expression_Tree_Event_Handler::Verbose_Expression_Tree_Event_Handler()
    : prompted(false)
{
}

void Verbose_Expression_Tree_Event_Handler::prompt_user()
{
    if (!prompted) {
        tree_context.state()->print_valid_commands();
        prompted = true;
    }
    std::cout << "> ";
    std::cout.flush();
}

Expression_Tree_Command Verbose_Expression_Tree_Event_Handler::make_command(
    const std::string& input)
{
    return command_factory.make_command(input);
}

void Macro_Command_Expression_Tree_Event_Handler::prompt_user()
{
    std::cout << "> ";
    std::cout.flush();
}

Expression_Tree_Command Macro_Command_Expression_Tree_Event_Handler::make_command(
    const std::string& input)
{
    return command_factory.make_macro_command(input);
}

#endif // EXPRESSION_TREE_EVENT_HANDLER_CPP
