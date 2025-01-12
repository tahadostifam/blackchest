#include <stdio.h>
#include <stdarg.h>

typedef enum
{
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING,
    TYPE_UNKNOWN
} PrintfArgType;

void cyrus_builtin__printf(PrintfArgType types[], int count, ...)
{
    va_list args;
    va_start(args, count);

    const char *fmt = va_arg(args, const char *);

    for (int i = 0; i < count; i++)
    {
        switch (types[i])
        {
        case TYPE_INT:
        {
            int arg_int = va_arg(args, int); // Retrieve as int
            printf("number: %d\n", arg_int);
            break;
        }
        case TYPE_DOUBLE:
        {
            double arg_double = va_arg(args, double); // Retrieve as double
            printf("double: %f\n", arg_double);
            break;
        }
        case TYPE_STRING:
        {
            char *arg_string = va_arg(args, char *); // Retrieve as char*
            printf("string: %s\n", arg_string);
            break;
        }
        default:
            printf("unknown\n");
            break;
        }
    }

    va_end(args);
}

int main()
{
    cyrus_builtin__printf((PrintfArgType[]){TYPE_INT, TYPE_INT}, 2, "fmt is here", 5, 6);
    return 0;
}