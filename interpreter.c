#include "interpreter.h"
#include "shellmemory.h"
#include "kernel.h"
#include "statusCode.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char **tokenize(char *str, size_t* numTokens)
{
    size_t num_tokens = 1;
    int flag = 0;
    for (size_t i = 0; i < strlen(str); i++)
    {
        if (flag == 0 && str[i] == ' ')
        {
            num_tokens = num_tokens + 1;
            flag = 1;
        }
        if (str[i] != ' ')
        {
            flag = 0;
        }
    }
    char **ret_arr =
            (char **)malloc(sizeof(char *) * (num_tokens + 1));

    if (ret_arr == NULL)
    {
        perror("malloc");
        return NULL;
    }
    flag = 0;
    int ignore_flag = 0;
    char *modified_str = (char *)str;
    size_t counter = 0;
    const size_t length_str = strlen(str);
    for (size_t i = 0; i < length_str; i++)
    {
        if (modified_str[i] == '\n' || modified_str[i] == '\r')
            modified_str[i] = ' ';
        if (modified_str[i] == '"')
        {
            ignore_flag = ignore_flag ^ 0x1;
        }
        if (flag == 0 && modified_str[i] != ' ')
        {
            ret_arr[counter] = &(modified_str[i]);
            counter = counter + 1;
            flag = 1;
        }
        if (modified_str[i] == '\\' && modified_str[i + 1] == ' ')
        {
            i++;
            continue;
        }
        if (flag == 1 && modified_str[i] == ' ' && ignore_flag == 0)
        {
            modified_str[i] = '\0';
            flag = 0;
            continue;
        }
    }
    ret_arr[counter] = NULL;

    for (size_t i = 0; i < counter; ++i)
    {
        if (ret_arr[i][0] == '\"' &&
            ret_arr[i][strlen(ret_arr[i] - 1)] == '\"')
        {
            ret_arr[i][strlen(ret_arr[i]) - 1] = '\0';
            ret_arr[i] = ret_arr[i] + 1;
        }
    }

    *numTokens = counter;
    return ret_arr;
}

int help(const size_t numParameter)
{
    if (numParameter > 0) {
        return TOO_MANY_ARGUMENTS;
    }

    printf(""
           "COMMAND         DESCRIPTION\n"
           "help            Displays all the commands\n"
           "quit            Exits / terminates the shell with \"Bye!\"\n"
           "set VAR STRING  Assigns a value to shell memory\n"
           "print VAR       Displays the STRING assigned to VAR\n"
           "run SCRIPT.TXT  Executes the file SCRIPT.TXT\n"
           "exec p1 p2 p3   Executes concurrent programs\n"
           "                $ exec prog.txt prog2.txt\n");
    return 0;
}

int quit(bool isFromScript, const size_t numParameter) {
    if (numParameter > 0) {
        return TOO_MANY_ARGUMENTS;
    }

    printf("Bye!\n");

    if (!isFromScript) {
        shell_memory_destory();
        exit(EXIT_SUCCESS);
    } else {
        return QUIT_FROM_SCRIPT;
    }
}

static int run(const char *path, const size_t numParameter)
{
    if (numParameter > 1) {
        return TOO_MANY_ARGUMENTS;
    }

    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        return SCRIPT_NOT_FOUND;
    }

    while (!feof(file))
    {
        char *line = NULL;
        size_t linecap = 0;
        getline(&line, &linecap, file);

        int errCode = interpret(line, true);
        free(line);
        if (errCode != 0)
        {
            return errCode;
        }
    }
    fclose(file);
    return 0;
}

int set(const char *key, const char *value, const size_t numParameter)
{
    if (numParameter > 2) {
        return TOO_MANY_ARGUMENTS;
    }

    int status = shell_memory_set(key, value);
    return status;
}

int print(const char *key, const size_t numParameter)
{
    if (numParameter > 1) {
        return TOO_MANY_ARGUMENTS;
    }

    const char *value = shell_memory_get(key);
    if (value == NULL)
    {
        printf("print: Undefiend value.\n");
        return 1;
    }
    printf("%s\n", value);
    return 0;
}

int exec(const char **script, const size_t numscript) {

    if (numscript > 3) {
        return EXEC_TOO_MANY_SCRIPTS;
    }

    for (int i = 0; i < numscript; i++) {
        for (int j = i + 1; j < numscript; j++) {
            if (strcmp(script[i], script[j]) == 0) {
                printf("Error: Script %s already loaded \n", script[i]);
                return EXEC_SCRIPT_LOADED;
            }
        }
    }

    for (int i = 0; i < numscript; i++) {
        int errCode = myinit(script[i]);
        if (errCode != 0)
        {
            return errCode;
        }
    }

    return scheduler();
}

int interpret(char* raw_input, bool isFromScript) {
//    printf("debug: enter interpret %s", raw_input);
    int errCode = 0;

    size_t numArgument = 0;
    char** tokens = tokenize(raw_input, &numArgument);
    numArgument --;

    if (tokens[0] == NULL) {
        return 0;
    }

    if (strcmp(tokens[0], "help") == 0) { help(numArgument); }
    else if (strcmp(tokens[0], "quit") == 0) { errCode = quit(isFromScript, numArgument); }
    else if (strcmp(tokens[0], "set") == 0) { errCode = set(tokens[1], tokens[2], numArgument); }
    else if (strcmp(tokens[0], "print") == 0) { errCode = print(tokens[1], numArgument); }
    else if (strcmp(tokens[0], "run") == 0) {
        errCode = run(tokens[1], numArgument);
        if (isFromScript) {
            printErrorMessage(errCode);
        }
        errCode = 0;
    }
    else if (strcmp(tokens[0], "exec") == 0) { errCode = exec((const char **) (tokens + 1), numArgument); }
    else { errCode = SYNTAX_ERROR; }

    free(tokens);

    return errCode;
}



//int interpret(char *raw_input)
//{
//    char **tokens = tokenize(raw_input);
//
//    if (tokens[0] == NULL)
//        return 0; // empty command
//
//    if (strcmp(tokens[0], "help") == 0)
//    {
//        if (tokens[1] != NULL)
//        {
//            printf("help: Malformed command\n");
//            free(tokens);
//            return 1;
//        }
//        free(tokens);
//        return help();
//    }
//
//    if (strcmp(tokens[0], "quit") == 0)
//    {
//        if (tokens[1] != NULL)
//        {
//            printf("quit: Malformed command\n");
//            free(tokens);
//            return 1;
//        }
//        if (in_file_flag) {
//            free(raw_input);
//        }
//        free(tokens);
//        return quit();
//    };
//
//    if (strcmp(tokens[0], "set") == 0)
//    {
//        if (!(tokens[1] != NULL && tokens[2] != NULL && tokens[3] == NULL))
//        {
//            printf("set: Malformed command\n");
//            free(tokens);
//            return 1;
//        }
//        int status = set(tokens[1], tokens[2]);
//        free(tokens);
//        return status;
//    }
//
//    if (strcmp(tokens[0], "print") == 0)
//    {
//        if (!(tokens[1] != NULL && tokens[2] == NULL))
//        {
//            printf("print: Malformed command\n");
//            free(tokens);
//            return 1;
//        }
//        int status = print(tokens[1]);
//        free(tokens);
//        return status;
//    }
//
//    if (strcmp(tokens[0], "run") == 0)
//    {
//        if (!(tokens[1] != NULL && tokens[2] == NULL))
//        {
//            printf("run: Malformed command\n");
//            free(tokens);
//            return 1;
//        }
//        int result = run(tokens[1]);
//        free(tokens);
//        return result;
//    }
//
//    if (strcmp(tokens[0], "exec") == 0)
//    {
//        char* scripts[3] = {NULL, NULL, NULL};
//        for (int i = 0; i < 3; i++)
//        {
//            if (tokens[1 + i] == NULL)
//            {
//                break;
//            }
//            scripts[i] = tokens[1 + i];
//        }
//
//        if (scripts[0] == NULL)
//        {
//            printf("exec: Malformed command\n");
//            free(tokens);
//            return 1;
//        }
//        if (tokens[4] != NULL && scripts[2] != NULL)
//        {
//            printf("exec: Provide more than 3 scripts\n");
//            free(tokens);
//            return 1;
//        }
//
//        int result = exec(scripts[0], scripts[1], scripts[2]);
//        free(tokens);
//        return result;
//    }
//
//    printf("Unrecognized command \"%s\"\n", tokens[0]);
//    free(tokens);
//    return 1;
//}