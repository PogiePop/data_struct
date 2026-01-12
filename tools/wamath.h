#ifndef _WA_MATH_H
#define _WA_MATH_H
#include "stack.h"
#include "wastring.h"

int cmp_operator(char op, char top);
int get_number(char *str);
int is_number_char(char c);
double get_numberd(char **str);
double calculate_number(double left, double right, char op);
const char *get_suffix_express(const char *str);
double calculate_suffix_express(const char *suffix);
int is_operator_char(char c);


int is_operator_char(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int cmp_operator(char op, char top)
{
    if (top == '/' || top == '*' || (top == '+' || top == '-') && (op == '+' || op == '-'))
        return 1; // top >= op
    else
        return 0; // top < op
}

int is_number_char(char c)
{
    return c >= '0' && c <= '9';
}

int get_number(char *number)
{
    if (!number)
        return 0;
    int res = 0;
    while (*number)
    {
        char c = *number;
        if (!is_number_char(c))
            break;
        res = res * 10 + (c - '0');
        number++;
    }
    number--;
    return res;
}

double get_numberd(char **number)
{
    if (!number && !(*number))
        return 0.0;
    int is_negative = 0;
    if (**number == '-')
    {
        is_negative = 1;
        (*number)++;
    }
    long long num_int = 0;
    long long num_point = 0;
    int point_len = 0;
    int is_start = FALSE;
    while (**number)
    {
        char c = **number;
        if (!is_number_char(c) && c != '.')
            break;
        if (c == '.')
        {
            is_start = TRUE;
            (*number)++;
            continue;
        }
        int digit = c - '0';
        if (!is_start)
        {
            num_int = num_int * 10 + digit;
        }
        else
        {
            num_point = num_point * 10 + digit;
            point_len++;
        }
        (*number)++;
    }
    (*number)--;
    double multiple = 1.0;
    for (int i = 0; i < point_len; i++)
        multiple *= 0.1;
    double decimal = num_point * multiple;
    double res = num_int + decimal;
    return (is_negative) ? -res : res;
}

double calculate_number(double left, double right, char op)
{
    switch (op)
    {
    case '-':
        return left - right;
    case '+':
        return left + right;
    case '*':
        return left * right;
    case '/':
        return left / right;
    default:
        return 0.0;
    }
}

double calculate_suffix_express(const char *suffix)
{
    if (!suffix)
        return 0;
    sk_ptr sk_number = create_stack();
    while (*suffix)
    {
        char c = *suffix;
        if (c == '|')
        {
            suffix++;
            double num = get_numberd(&(char *)suffix);
            push_double(sk_number, num);
        }
        else
        {
            // 先弹出的为右操作数
            double right = get_object_double(sk_top(sk_number));
            sk_pop(sk_number);
            double left = get_object_double(sk_top(sk_number));
            sk_pop(sk_number);
            push_double(sk_number, calculate_number(left, right, c));
        }
        suffix++;
    }
    double res = get_object_double(sk_top(sk_number));
    destory_stack(&sk_number);
    return res;
}



//暂时不考虑负数
const char* get_suffix_express(const char* str)
{
    if(!str)return NULL;
    sk_ptr sk = create_stack();
    lk_list list = create_linklist();
    while(*str)
    {
        char c = *str;
        if(is_number_char(c)){
            lk_insert_back_char(list, '|');
            lk_insert_back_double(list, get_numberd(&str));
        }
        else if(c == '(' || c == ')')
        {
            if(c == '(')push_char(sk, c);
            else{
                while(!sk_is_empty(sk) && get_object_char(sk_top(sk)) != '(')
                {
                    lk_insert_back_char(list, get_object_char(sk_top(sk)));
                    sk_pop(sk);
                }
                if(get_object_char(sk_top(sk)) == '(')
                sk_pop(sk);
            }
        }
        else if(is_operator_char(c)){
            char top = get_object_char(sk_top(sk));
            while(!sk_is_empty(sk) && top != '(' && cmp_operator(c, top))
            {
                lk_insert_back_char(list, top);
                sk_pop(sk);
                top = get_object_char(sk_top(sk));
            }
            push_char(sk, c);
        }else{
            return NULL;
        }
        str++;
    }
    while(!sk_is_empty(sk))
    {
        lk_insert_back_char(list, get_object_char(sk_top(sk)));
        sk_pop(sk);
    }

    int size = lk_get_buffer_size(list);
    char* res = (char*)malloc(sizeof(char) * size);
    if(!res)return NULL;
    memset(res, 0, size);
    strcpy_s(res, size,lk_to_string(list));
    destory_linklist(&list);
    destory_stack(&sk);
    return res;
}
#endif