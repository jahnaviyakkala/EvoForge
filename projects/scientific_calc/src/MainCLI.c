#include <stdio.h>
#include <stdlib.h>
#include "CalculatorService.h"
#include "ExpressionParser.h"

typedef struct {
    CalculatorService* calculator;
    ExpressionParser* parser;
} MainCLI;

MainCLI* create_main_cli(CalculatorService* calc, ExpressionParser* exprParser) {
    MainCLI* cli = (MainCLI*)malloc(sizeof(MainCLI));
    cli->calculator = calc;
    cli->parser = exprParser;
    return cli;
}

void destroy_main_cli(MainCLI* cli) {
    free(cli);
}

double evaluate_expression(MainCLI* cli, const char* expression) {
    int size;
    char** tokens = cli->parser->parse(expression, &size);
    // Dummy evaluation logic for demonstration purposes
    double result = 0.0;
    if (size > 0) {
        result = atof(tokens[0]);
    }
    free(tokens);
    return result;
}

void run(MainCLI* cli) {
    char input[256];
    while (1) {
        printf("Enter expression: ");
        fgets(input, sizeof(input), stdin);
        // Remove newline character
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0) {
            break;
        }

        try {
            double result = evaluate_expression(cli, input);
            printf("Result: %f\n", result);
        } catch (const char* msg) {
            fprintf(stderr, "%s\n", msg);
        }
    }
}
