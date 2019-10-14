/* Copyright G. Hemingway @ 2019, All Rights Reserved */
#ifndef PRINT_VISITOR_H
#define PRINT_VISITOR_H

#include "Visitor.h"

/**
 * @class Print_Visitor
 * @brief This class serves as a visitor for printing the contents of
 *        nodes to std::cout.
 */

class Print_Visitor : public Visitor {
public:
    // Visits a Leaf_Node and prints it contents to std::cout.
    virtual void visit(const Leaf_Node& node);

    // Visit a Composite_Negate_Node and prints its contents to std::cout.
    virtual void visit(const Composite_Negate_Node& node);

    // Visit a Composite_Add_Node and prints its contents to std::cout.
    virtual void visit(const Composite_Add_Node& node);

    // Visit a Composite_Subtract_Node and prints its contents to @a
    // std::cout.
    virtual void visit(const Composite_Subtract_Node& node);

    // Visit a Composite_Divide_Node and prints its contents to std::cout.
    virtual void visit(const Composite_Divide_Node& node);

    // visit function - prints Composite_Multiply_Node contents to std::cout
    virtual void visit(const Composite_Multiply_Node& node);
};

#endif // PRINT_VISITOR_H
