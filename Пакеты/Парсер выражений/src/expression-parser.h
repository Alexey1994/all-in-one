#ifndef EXPRESSION_PARSER_H_INCLUDED
#define EXPRESSION_PARSER_H_INCLUDED


#include <data-structures/buffer.h>
#include <input.h>


#define OPEN_BRACE  0


typedef enum
{
    BINARY_OPERATION = 1,
    UNARY_OPERATION  = 2,
    OPERAND          = 3
}
Expression_Node_Type;


typedef struct
{
    N_32  type; //BINARY_OPERATION, UNARY_OPERATION
    char* name;
    N_32  priority;
}
Operation;


typedef struct
{
    Expression_Node_Type type;
    Byte*                data;

}
Expression_Node;


import Boolean parse_expression (
    Buffer*    expression,
    Input*     input,
    Operation* operations,
    N_32       operations_length,
    Byte*      language_parser,

    Byte* (*read_operand)(Byte* language_parser)
);

void print_expression_in_postfix_notation (Buffer* expression, void (*print_operand)(Byte* operand));


#endif // EXPRESSION_PARSER_H_INCLUDED
