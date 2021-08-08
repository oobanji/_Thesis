#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef CALC_PARSE_H
#define CALC_PARSE_H

struct index_num {
    int index;
    char *number_str;
};

struct index_expr {
    int index;
    char** expr_list;
};

struct index_num parse_num(char* s, int i);
struct index_expr parse_paren(char* s, int i);
struct index_expr parse_expr(char* s, int i, int seen_paren);
#define BUFFER 10240

#endif //CALC_PARSE_H

struct index_num parse_num(char* s, int i) {
    struct index_num result;
    int slen = strlen(s);
    char* buf = (char*) malloc((slen-i) * sizeof(char));
    for (int j=0; j<slen; j++){
        if (!isdigit(s[i])){
            break;
        } else {
            buf[j] = s[i];
            i++;
        }
    }
    result.index = i;
    result.number_str = strdup(buf);
    return result;
}


struct index_expr parse_paren(char* s, int i) {
    if (s[i] != '('){
        exit(11);
    } else {
        struct index_expr result;
        result = parse_expr(s, i+1, 1);
        if (result.index > strlen(s)){
            exit(12); /* Warning: index greater than string len!*/
        }
        if (s[result.index] == ' '){
            exit(14); /* Error: parse_paren */
        } else {
            if (s[result.index] != ')'){
                exit(13); /* Missing closing paren! */
            } else {
                result.index += 1;
                return result;
            }
        }
    }
}

/* Return values not correct yet.  */
struct index_expr parse_expr(char* s, int i, int seen_paren) {
  struct index_expr expressions;
  expressions.expr_list = (char**) malloc((strlen(s)-i)* sizeof(char*));
  char** expr = expressions.expr_list;
  struct index_num number;
  struct index_expr paren;
  int is_expr = 0;
  while ( i < strlen(s)){
    char c = s[i];
    if (isdigit(c)) {
      if(is_expr) { exit(-1);}
      is_expr = 1;
      number = parse_num(s, i);
      i = number.index; /* set new index in input string */
      *expr = number.number_str; //=expr.append(number)
      expr++;
    }
    else if (c == '+' || c == '-' || c == '*' || c == '/') {
      if(!is_expr) { exit(-1);}
      is_expr = 0;
      char str[2] = {c, 0};
      *expr = str;
      expr++;
      i++;
    }
    else if (c == '('){
      if(is_expr) { exit(-1);}
      is_expr = 1;
      paren = parse_paren(s, i);
      i = paren.index;
      *expr = *paren.expr_list; /* this doesn't work if it's a list of expressions instead of char* */
      expr++;
    }
    else if (c == ')'){
      if(!is_expr) { exit(-1);}
      if(!seen_paren) { exit(-2);}
      expressions.index = i;
      return expressions;
    } else {
      /* unable to parse. */
      exit(2);
    }
  }
  if(!is_expr) { exit(-2);}
  expressions.index = i;
  return expressions;
}


int main(int argc, char *argv[]) {
    char my_string[10240];
    strcpy(my_string, argv[1]);
    parse_expr(my_string, 0, 0);
}
