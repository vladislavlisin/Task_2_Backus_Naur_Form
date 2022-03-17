#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define W 256

void find_and_replace(char *source, char *pattern, char *replacement, char *result) {

    unsigned int patternLength = strlen(pattern);
    unsigned int replacementLength = strlen(replacement);

    char *tail = source;
    char *temp = result;
    char *next = strstr(tail, pattern);

    while(next != NULL) {
        long long int k = next - tail;

        if (tail[k + patternLength] == '+' || tail[k + patternLength] == '-' || tail[k + patternLength] == '/' ||
            tail[k + patternLength] == '*' || tail[k + patternLength] == ')') {

            if (tail[k - 1] == '+' || tail[k - 1] == '-' || tail[k - 1] == '/' ||
                tail[k - 1] == '*' || tail[k - 1] == '(') {

                strncpy(result, tail, next - tail); // копируем в result из tail (next-tail) символов
                strcpy(result += next - tail, replacement); // копируем в result[next - tail] подстроку replace
                result = result + replacementLength; // result[next - tail + replacementLength]
                tail = next + patternLength; // tail[next + patternLength]
                next = strstr(tail, pattern);
            }
            else {
                strncpy(result, tail, 1); // копируем в result из tail (next-tail) символов
                next = strstr(&next[1], pattern);
            }
        }
        else {
            strncpy(result, tail, 1); // копируем в result из tail (next-tail) символов
            next = strstr(&next[1], pattern);
        }
    }
    strcpy(result, tail);
    strcpy(source, temp);
}

int main() {
    char oldstr[W]; // проверяемая строка
    char newstr[W]; // новая строчка
    int lines_count; // количество строк
    char numb_array[W][W]; // массив индентификаторов
    char ids_array[W][W]; // массив чисел
    int left = 1; // количество скобок "("
    int right = 0; // количество скобок ")"
    unsigned int oldstrlen;
    unsigned int realstr;

    FILE *input, *output;
    output = fopen("output.txt", "w");
    input = fopen("input.txt", "r");


    fscanf(input, "%i", &lines_count);
    for(int i = 0; i < lines_count; i++) {
        fscanf(input, "%s", &ids_array[i][W]);
        fscanf(input, "%s", &numb_array[i][W]);
    }
    fscanf(input, "%s", oldstr);
    oldstrlen = strlen(oldstr) - 1;
    // Проверка на простое выражение

    if(oldstr[0] == '(') {
        int i = 1;
        while ((oldstr[i] <= 'z' && oldstr[i] >= 'a') || (oldstr[i] >= '0' && oldstr[i] <= '9') ||
               (oldstr[i] <= 'Z' && oldstr[i] >= 'A') || oldstr[i] == '_') {
            i++;
            if (oldstr[i] == '+' || oldstr[i] == '-' || oldstr[i] == '/' || oldstr[i] == '*') {
                i++;
                if (oldstr[i] == '(') {
                    left++;
                    i++;
                }
                else {
                    while ((oldstr[i] <= 'z' && oldstr[i] >= 'a') || (oldstr[i] >= '0' && oldstr[i] <= '9') ||
                           (oldstr[i] <= 'Z' && oldstr[i] >= 'A') || oldstr[i] == '_') {
                        i++;
                        while (oldstr[i] == ')' && right < left) {
                            i++;
                            right++;
                            if (oldstr[i] != 0 && oldstr[i] != ')') {
                                fprintf(output, "INCORRECT\n");
                                exit(0);
                            }
                        }
                    }
                }
            }
        }
    }
    else for(int i = 0; ((oldstr[i] <= 'z' && oldstr[i] >= 'a') || (oldstr[i] >= '0' && oldstr[i] <= '9') ||
                         (oldstr[i] <= 'Z' && oldstr[i] >= 'A') || oldstr[i] == '_') && oldstr[i] != 0 ; i++) {
            realstr = i;
        }

    // Простое выражение (да или нет) и замена идентификаторов
    if(right == left) {
        for(int i = 0; i < lines_count; i++) {
            find_and_replace(oldstr, &ids_array[i][W], &numb_array[i][W], newstr);
        }
        fprintf(output, "%s\n", newstr);
        exit(0);
    }

    if(oldstrlen == realstr) {
        for(int i = 0; i < lines_count; i++) {
            if (strstr(oldstr, &ids_array[i][W]) != NULL && strlen(&ids_array[i][W]) == strlen(oldstr)) {
                strcpy(newstr, &numb_array[i][W]);
                lines_count = 0;
            }
        }
        if(lines_count != 0) {
            strcpy(newstr, oldstr);
        }
    }
    else {
        fprintf(output, "INCORRECT\n");
        exit(0);
    }

    fprintf(output, "%s\n", newstr);

    fclose(input);
    fclose(output);
    return 0;
}