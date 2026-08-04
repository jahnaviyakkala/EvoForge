#ifndef EXPRESSIONPARSER_H
#define EXPRESSIONPARSER_H

typedef struct {
    char** (*parse)(const char* expression, int* size);
} ExpressionParser;

#endif // EXPRESSIONPARSER_H
