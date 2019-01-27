#include <system.h>
#include "expression-parser.h"


Operation* get_stack_operation (Buffer* stack)
{
    N_32        length;
    Operation** data;

    data = stack->data;
    length = stack->length / sizeof(Operation*);

    return data[length - 1];
}


void add_operation_in_stack (Buffer* stack, Operation* operation)
{
    cycle(0, sizeof(Operation*), 1)
        write_in_buffer(stack, ((Byte*)&operation)[i]);
    end
}


Operation* remove_operation_from_stack (Buffer* stack)
{
    N_32        length;
    Operation** data;

    data = stack->data;
    length = stack->length / sizeof(Operation*);
    stack->length -= sizeof(Operation*);

    return data[length - 1];
}


Boolean stack_contains_open_brace (Buffer* stack)
{
    N_32        i;
    N_32        length;
    Operation** data;

    data = stack->data;
    length = stack->length / sizeof(Operation*);
    i = length;

    for(; i; --i)
        if(data[i - 1] == OPEN_BRACE)
            return 1;

    return 0;
}


void add_expression_node (Buffer* expression, Expression_Node_Type type, Byte* data)
{
    Expression_Node node;

    node.type = type;
    node.data = data;

    cycle(0, sizeof(Expression_Node), 1)
        write_in_buffer(expression, ((Byte*)&node)[i]);
    end
}


export Boolean parse_expression (
    Buffer*    expression,
    Input*     input,
    Operation* operations,
    N_32       operations_length,
    Byte*      language_parser,

    Byte* (*read_operand)(Byte* language_parser)
)
{
    Buffer     stack;
    Boolean    is_expression;
    Boolean    is_operation;
    Operation *operation;
    Byte      *operand;
    N_32       i;

    initialize_buffer(&stack, 4);
    initialize_buffer(expression, 20);
    is_expression  = 1;
    is_operation   = 0;

    while(!end_of_input(input) && is_expression)
    {
read_unary_operation:
        skip_spaces(input);

        for(i = 0; i < operations_length; ++i)
        {
            operation = operations + i;

            if(operation->type != UNARY_OPERATION)
                continue;

            if(read_if(input, operation->name))
            {
                add_operation_in_stack(&stack, operation);
                goto read_unary_operation;
            }
        }

        skip_spaces(input);

        if(input_data(input) != '(')
        {
            operand = read_operand(language_parser);

            if(!operand)
                goto error;

            add_expression_node(expression, OPERAND, operand);
            is_operation = 0;
        }

read_operation:

        skip_spaces(input);

        if(end_of_input(input))
            break;

        switch(input_data(input))
        {
        case '(':
            add_operation_in_stack(&stack, OPEN_BRACE);
            read_input(input);

            is_operation = 1;
            break;

        case ')':
            if(!stack_contains_open_brace(&stack))
            {
                is_expression = 0;
                break;
            }

            if(get_stack_operation(&stack) == OPEN_BRACE)
            {
                printf("braces without expression\n");
                goto error;
            }

            do
            {
                if(!stack.length)
                {
                    printf("expected (\n");
                    goto error;
                }

                add_expression_node(expression, BINARY_OPERATION, remove_operation_from_stack(&stack));
            }
            while(get_stack_operation(&stack) != OPEN_BRACE);

            remove_operation_from_stack(&stack);
            read_input(input);

            is_operation = 0;
            goto read_operation;

        default:
            is_expression = 0;

            for(i = 0; i < operations_length; ++i)
            {
                operation = operations + i;

                if(operation->type != BINARY_OPERATION)
                    continue;

                if(read_if(input, operation->name))
                {
                    if(is_operation)
                    {
                        printf("2 operations without operand\n");
                        goto error;
                    }

                    while(stack.length)
                    {
                        Operation* next_operation = get_stack_operation(&stack);

                        if(next_operation == OPEN_BRACE || next_operation->priority > operation->priority)
                            break;

                        add_expression_node(expression, BINARY_OPERATION, remove_operation_from_stack(&stack));
                    }

                    add_operation_in_stack(&stack, operation);

                    is_operation = 1;
                    is_expression = 1;

                    break;
                }
            }
        }

        skip_spaces(input);
    }

    while(stack.length)
    {
        operation = remove_operation_from_stack(&stack);

        if(operation == OPEN_BRACE)
        {
            printf("expected )\n");
            goto error;
        }

        add_expression_node(expression, BINARY_OPERATION, operation);
    }

    deinitialize_buffer(&stack);
    return 1;

error:
    deinitialize_buffer(&stack);
    deinitialize_buffer(expression);
    return 0;
}


void print_expression_in_postfix_notation (Buffer* expression, void (*print_operand)(Byte* operand))
{
    Expression_Node* nodes;
    N_32             length;

    nodes = expression->data;
    length = expression->length / sizeof(Expression_Node);

    cycle(0, length, 1)
        Expression_Node* current_node = nodes + i;

        if(current_node->type == OPERAND)
            printf("%c ", current_node->data);

        if(current_node->type == BINARY_OPERATION)
            printf("%s ", ((Operation*)current_node->data)->name);
    end
}


////////////////////////////////////////////////////


N_32 read_operand (Input *input)
{
    N_32 number = input_data(input);
    read_input(input);
    skip_spaces(input);
    return number;

error:
    return 0;
}


Operation operations[] = {
    {BINARY_OPERATION, "*", 1},
    {BINARY_OPERATION, "+", 2},
    {UNARY_OPERATION, "-", 0}
};


int fgetc( Byte * filestream );
int feof ( Byte * filestream );


void print_operand (char operand)
{
    printf("%c", operand);
}


N_32 main ()
{
    Input   input;
    Byte*   input_file;
    Buffer  expression;
    N_32    is_success;

    input_file = fopen("test", "rb");
    initialize_input(&input, input_file, &fgetc);
    input.end_of_data = &feof;

    is_success = parse_expression (
        &expression,
        &input,
        operations,
        sizeof(operations) / sizeof(Operation),
        &input,
        &read_operand);

    if(!is_success)
        printf("error parsing\n");

    print_expression_in_postfix_notation(&expression, &print_operand);

    return 0;
}
