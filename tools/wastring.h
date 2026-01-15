#ifndef _WA_STRING_H
#define _WA_STRING_H
#ifndef EXTEND_MULTIPLE
#define EXTEND_MULTIPLE 2
#endif
#include <stdlib.h>
#include <string.h>
#define MAX_DECIMAL_DIGITS 15
#define INIT_CAPACITY 10

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#if defined(_WIN32) || defined(_WIN64)
    #define STR_COPY(dst, dst_buffer_size, src) strcpy_s(dst, dst_buffer_size, src)
    #define STR_NCOPY(dst, dst_buffer_size,src, len) strncpy_s(dst, dst_buffer_size, src, len)
#else
    #define STR_COPY(dst, dst_size, src) strcpy(dst, src)
    #define STR_NCOPY(dst, nothing, src, len) do{\
        strncpy(dst, src, len);\
        dst[n] = '\0'; \
    } while(0)
#endif


typedef struct wastring{
    char* data;
    size_t capacity;
    size_t size;
}wastring;

#define str_ptr wastring*
#define str_ptr_ptr str_ptr*

str_ptr create_wastring();
str_ptr create_wastring_initstr(const char* initstr);
void destroy_wastring(str_ptr_ptr string_ptr);
void wa_append(str_ptr str, const char* value);
void wa_append_char(str_ptr str, char value);
void wa_erase(str_ptr str, int index);
void wa_erase_str(str_ptr str, str_ptr e_sub);
void wa_copy_str(str_ptr des, str_ptr src);
void wa_clear(str_ptr str);
int wa_resize(str_ptr str);
int wa_equal(str_ptr str1, str_ptr str2);
str_ptr wa_substr(str_ptr str, int start, int len);
int wa_find_substr(str_ptr str, str_ptr substr, int start);
int wa_index_substr(str_ptr str, str_ptr substr);
int wa_is_empty(str_ptr str);
int* wa_get_next(str_ptr pattern_str);
int wa_index_substr_fast(str_ptr str, str_ptr substr);
const char* wa_to_string(str_ptr str);
char wa_at(str_ptr str, int index);
const char *double_to_string(double num);


str_ptr create_wastring()
{
    str_ptr str = (str_ptr)malloc(sizeof(wastring));
    str->data = (char*)malloc(sizeof(char) * INIT_CAPACITY);
    memset(str->data, 0, INIT_CAPACITY);
    *str->data = '\0';
    str->capacity = INIT_CAPACITY;
    str->size = 0;
    return str;
}

str_ptr create_wastring_initstr(const char* initstr)
{
    if(!initstr)return create_wastring();
    str_ptr str = (str_ptr)malloc(sizeof(wastring));
    int len = (int)strlen(initstr);
    str->data = (char*)malloc(sizeof(char) * (len + INIT_CAPACITY));
    memset(str->data, 0, len + INIT_CAPACITY);
    STR_COPY(str->data, len + INIT_CAPACITY, initstr);
    str->capacity = len + INIT_CAPACITY;
    str->size = len;
    return str;
}

void wa_append_char(str_ptr str, char c)
{
    if(!str)return;
    if(str->size + 1 > str->capacity - 1)if(!wa_resize(str))return;
    str->data[str->size] = c;
    str->data[str->size + 1] = '\0';
    str->size++;
}

void wa_append(str_ptr str, const char* value)
{
    if(!str || !value)return;
    while(str->capacity - 1 - str->size < strlen(value)){
        if(!wa_resize(str))return;
    }
    int extend_size = (int)strlen(value);
    for(int i = 0; i <= extend_size; i++)str->data[str->size + i] = value[i]; 
    str->size += extend_size;
}

int wa_resize(str_ptr str)
{
    if(!str || str->capacity == 0)return FALSE;
    char* tmp = str->data;
    str->data = (char*)malloc(sizeof(char) * str->capacity * EXTEND_MULTIPLE);
    str->capacity *= EXTEND_MULTIPLE;
    memset(str->data, 0, str->capacity);
    STR_COPY(str->data, str->capacity, tmp);
    free(tmp);
    return TRUE;
}

void destroy_wastring(str_ptr_ptr string_ptr)
{
    if(!string_ptr || !(*string_ptr))return;
    if((*string_ptr)->data)free((*string_ptr)->data);
    free(*string_ptr);
    *string_ptr = NULL;
}

void wa_clear(str_ptr str)
{
    if(!str || str->size == 0)return;
    memset(str->data, 0, str->capacity);
    str->size = 0;
}

int wa_is_empty(str_ptr str)
{
    return !str || str->size == 0;
}

int wa_equal(str_ptr str1, str_ptr str2)
{
    if(!str1 || !str2)return FALSE;
    return strcmp(str1->data, str2->data) == 0;
}

str_ptr wa_substr(str_ptr str, int start, int len)
{
    if(wa_is_empty(str) || start + len > str->size)return NULL;
    char* res = (char*)malloc(sizeof(char) * (len + 1));
    memset(res, 0, len + 1);
    STR_NCOPY(res, len + 1,str->data + start, len);
    res[len] = '\0';
    str_ptr str_res =  create_wastring_initstr(res);
    free(res);
    res = NULL;
    return str_res;
}


int wa_index_substr(str_ptr str, str_ptr substr)
{
    if(!str || !substr || str->size < substr->size)return -1;
    if(wa_is_empty(str) && wa_is_empty(substr))return 0;
    int i = 0;
    for(i; i < str->size; i++){
        if(str->size - i < substr->size)break;
        if(wa_find_substr(str, substr, i))return i;
    }
    return -1;
}


int wa_find_substr(str_ptr str, str_ptr substr, int start)
{
    if(!str || !substr || str->size - start < substr->size)return FALSE;
    str_ptr sub = wa_substr(str, start, (int)substr->size);
    int res = wa_equal(sub, substr);
    destroy_wastring(&sub);
    return res;
}

int* wa_get_next(str_ptr pattern_str)
{
    if(!pattern_str || pattern_str->size == 0)return NULL;
    int i = 1, j = 0;
    int *next = (int*)malloc(sizeof(int) * (pattern_str->size + 1));
    memset(next, 0, sizeof(int) * (pattern_str->size + 1));
    next[i] = j;
    while(i < pattern_str->size)
    {
        if(j == 0 || pattern_str->data[i - 1] == pattern_str->data[j - 1]){
            ++j;++i;
            next[i] = j;
        }else{
            j = next[j];
        }
    }
    return next;
}

int wa_index_substr_fast(str_ptr str, str_ptr substr)
{
    if(!str || !substr)return -1;
    int *next = wa_get_next(substr);
    if(!next)return -1;
    int i = 0, j = 0;
    while(i < (int)str->size && j < (int)substr->size)
    {
        if(j == -1 || str->data[i] == substr->data[j]){
            ++i;++j;
        }else{
            //由于计算的next数组是从下标为1开始的所以+1转换到对应值-1
            j = next[j + 1] - 1;
        }
    }
    free(next);
    next = NULL;
    if(j == substr->size)return i - j;
    return -1;
}


void wa_copy_str(str_ptr des, str_ptr src)
{
    if(!des || !src)return;
    wa_clear(des);
    wa_append(des, src->data);
}

const char* wa_to_string(str_ptr str)
{
    if(!str)return NULL;
    return str->data;
}

char wa_at(str_ptr str, int index)
{
    if(!str || index < 0 || index >= str->size)return '\0';
    return str->data[index];
}


void wa_erase(str_ptr str, int index)
{
    if(!str || index < 0 || index >= str->size)return;
    for(int i = index; i < str->size - 1; i++)str->data[i] = str->data[i + 1];
    str->data[str->size - 1] = '\0';
}


void wa_erase_str(str_ptr str, str_ptr e_sub)
{
    if(!str || !e_sub)return;
    int start = wa_index_substr_fast(str, e_sub);
    if(start == -1)return;
    int len = (int)e_sub->size;
    int k = (int)str->size - (start + len);
    for(int i = 0; i < k; i++)str->data[start + i] = str->data[start + len + i];
    int resize = (int)str->size - len;
    memset(str->data + resize, 0, str->capacity);
    str->size = resize;
}

const char *double_to_string(double num)
{
    int is_negative = 0;
    // 负数转为正数
    if (num < 0)
    {
        is_negative = 1;
        num = -num;
    }

    // 最大小数位15

    long long num_int = (long long)num;
    double num_decimal = num - num_int;

    // 提取小数部分数字
    char dec_digits[MAX_DECIMAL_DIGITS + 1] = {0};
    int dec_len = 0;
    while (num_decimal > 1e-15 && dec_len < MAX_DECIMAL_DIGITS)
    {
        num_decimal *= 10;
        int digit = (int)num_decimal;
        dec_digits[dec_len++] = digit + '0';
        num_decimal -= digit;
    }

    // 去掉末尾部分0
    while (dec_len > 0 && dec_digits[dec_len - 1] == '0')
        dec_len--;

    int int_len = 0;
    long long tmp_int = num_int;
    if (tmp_int == 0)
    {
        int_len = 1;
    }
    else
    {
        while (tmp_int)
        {
            tmp_int /= 10;
            int_len++;
        }
    }

    // 计算总长度
    int has_decimal = (dec_len > 0) ? 1 : 0;
    int size = is_negative + int_len + has_decimal + dec_len + 1;
    char *res = (char *)malloc(sizeof(char) * size);
    if (!res)
        return NULL;
    memset(res, 0, size);

    int idx = size - 2;
    for (int i = dec_len - 1; i >= 0; i--)
        res[idx--] = dec_digits[i];

    if (has_decimal)
        res[idx--] = '.';

    tmp_int = num_int;
    if (tmp_int == 0)
        res[idx--] = '0';
    else
    {
        while (tmp_int)
        {
            int digit = tmp_int % 10;
            tmp_int /= 10;
            res[idx--] = digit + '0';
        }
    }

    if (is_negative)
        res[idx--] = '-';

    res[size - 1] = '\0';

    return res;
}
#endif