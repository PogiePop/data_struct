#ifndef OBJECT_H
#define OBJECT_H
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "wastring.h"
#define object void *
#define object_ptr object *
typedef enum obj_type
{
    NONE,
    CHAR,
    INTEGER,
    FLOAT,
    DOUBLE,
    STRING,
    WASTRING
} obj_type;
typedef union value
{
    char i_char;
    int i_int;
    float i_float;
    double i_double;
    char *i_string;
    str_ptr i_wastring;
} value;
const char type_name[][10] = {
    "none",
    "char",
    "integer",
    "float",
    "double",
    "string",
    "wastring"
};
typedef struct Object
{
    object data;
    obj_type type;
    size_t buffer_size;
} Object;

#define Obj_ptr Object *
#define Obj_ptr_ptr Obj_ptr *
void free_object(Obj_ptr obj_ptr);
void destory_object(Obj_ptr_ptr obj_ptr_ptr);
void copy_object_value(Obj_ptr dest, Obj_ptr src);
size_t get_object_size(Obj_ptr obj_ptr);
const char *get_object_type(Obj_ptr obj_ptr);
value get_object_value(Obj_ptr obj_ptr);
void printf_object_value(const char *format, va_list value);
void print_object(const char *format, ...);
Obj_ptr create_object();
Obj_ptr create_object_int();
void set_object_int(Obj_ptr obj_ptr, int value);
int get_object_int(Obj_ptr obj_ptr);
Obj_ptr create_object_float();
void set_object_float(Obj_ptr obj_ptr, float value);
float get_object_float(Obj_ptr obj_ptr);
Obj_ptr create_object_double();
void set_object_double(Obj_ptr obj_ptr, double value);
double get_object_double(Obj_ptr obj_ptr);
Obj_ptr create_object_char_ptr();
Obj_ptr create_object_wastring();
void set_object_wastring(Obj_ptr obj_ptr, str_ptr str);
void set_object_wastring_char_ptr(Obj_ptr, const char* str);
str_ptr get_object_wastring(Obj_ptr obj_ptr);
void set_object_char_ptr(Obj_ptr obj_ptr, const char *value);
const char *get_object_char_ptr(Obj_ptr obj_ptr);
void set_object_int_wrap(Obj_ptr obj_ptr, void *data);
void set_object_float_wrap(Obj_ptr obj_ptr, void *data);
void set_object_double_wrap(Obj_ptr obj_ptr, void *data);
void set_object_char_wrap(Obj_ptr obj_ptr, void *data);
void set_object_char_ptr_wrap(Obj_ptr obj_ptr, void *data);
int cmp_object_value(Obj_ptr obj_ptr, void *data);
const char* obj_to_string(Obj_ptr obj_ptr);


Obj_ptr create_object_int()
{
    Obj_ptr obj = (Obj_ptr)malloc(sizeof(Object));
    obj->data = malloc(sizeof(int));
    obj->type = INTEGER;
    obj->buffer_size = sizeof(int);
    return obj;
}

void set_object_int(Obj_ptr obj_ptr, int value)
{
    if (!obj_ptr)
        return;
    if (obj_ptr->type != INTEGER)
        free_object(obj_ptr);
    if (!obj_ptr->data)
    {
        obj_ptr->data = malloc(sizeof(int));
        obj_ptr->type = INTEGER;
        obj_ptr->buffer_size = sizeof(int);
    }
    *(int *)obj_ptr->data = value;
}

int get_object_int(Obj_ptr obj_ptr)
{
    if (!obj_ptr || !obj_ptr->data)
        return 0;
    return *(int *)obj_ptr->data;
}

Obj_ptr create_object_float()
{
    Obj_ptr obj = create_object();
    obj->type = FLOAT;
    return obj;
}
void set_object_float(Obj_ptr obj_ptr, float value)
{
    if (!obj_ptr)
        return;
    if (obj_ptr->type != FLOAT)
        free_object(obj_ptr);
    if (!obj_ptr->data)
    {
        obj_ptr->data = malloc(sizeof(float));
        obj_ptr->type = FLOAT;
        obj_ptr->buffer_size = sizeof(float);
    }
    *(float *)obj_ptr->data = value;
}
float get_object_float(Obj_ptr obj_ptr)
{
    if (!obj_ptr || !obj_ptr->data)
        return 0.0f;
    return *(float *)obj_ptr->data;
}

Obj_ptr create_object_double()
{
    Obj_ptr obj = create_object();
    obj->type = DOUBLE;
    return obj;
}
void set_object_double(Obj_ptr obj_ptr, double value)
{
    if (!obj_ptr)
        return;
    if (obj_ptr->type != DOUBLE)
        free_object(obj_ptr);
    if (!obj_ptr->data)
    {
        obj_ptr->data = malloc(sizeof(double));
        obj_ptr->type = DOUBLE;
        obj_ptr->buffer_size = sizeof(double);
    }
    *(double *)obj_ptr->data = value;
}
double get_object_double(Obj_ptr obj_ptr)
{
    if (!obj_ptr || !obj_ptr->data)
        return 0.0;
    return *(double *)obj_ptr->data;
}

Obj_ptr create_object_char()
{
    Obj_ptr obj = create_object();
    obj->type = CHAR;
    return obj;
}
void set_object_char(Obj_ptr obj_ptr, char value)
{
    if (!obj_ptr)
        return;
    if (obj_ptr->type != CHAR)
        free_object(obj_ptr);
    if (!obj_ptr->data)
    {
        obj_ptr->data = malloc(sizeof(char));
        obj_ptr->type = CHAR;
        obj_ptr->buffer_size = sizeof(char);
    }
    *(char *)obj_ptr->data = value;
}
char get_object_char(Obj_ptr obj_ptr)
{
    if (!obj_ptr || !obj_ptr->data)
        return '\0';
    return *(char *)obj_ptr->data;
}

Obj_ptr create_object_char_ptr()
{
    Obj_ptr obj = create_object();
    obj->type = STRING;
    return obj;
}
void set_object_char_ptr(Obj_ptr obj_ptr, const char *value)
{
    if (!obj_ptr || !value)
        return;
    if (obj_ptr->type != STRING)
        free_object(obj_ptr);
    if (!obj_ptr->data)
    {
        obj_ptr->data = malloc(sizeof(char) * (strlen(value) + 1));
        strcpy_s((char *)obj_ptr->data, strlen(value) + 1, value);
        obj_ptr->buffer_size = strlen(value) + 1;
        obj_ptr->type = STRING;
        return;
    }
    free(obj_ptr->data);
    obj_ptr->data = malloc(sizeof(char) * (strlen(value) + 1));
    obj_ptr->buffer_size = strlen(value) + 1;
    strcpy_s((char *)obj_ptr->data, strlen(value) + 1, value);
}
const char *get_object_char_ptr(Obj_ptr obj_ptr)
{
    if (!obj_ptr || !obj_ptr->data)
        return NULL;
    return (char *)obj_ptr->data;
}

void free_object(Obj_ptr obj_ptr)
{
    if (!obj_ptr)
        return;
    free(obj_ptr->data);
    obj_ptr->data = NULL;
    obj_ptr->buffer_size = 0;
    obj_ptr->type = NONE;
}

void destory_object(Obj_ptr_ptr obj_ptr_ptr)
{
    if (!obj_ptr_ptr || !(*obj_ptr_ptr))
        return;
    if ((*obj_ptr_ptr)->data)
        free((*obj_ptr_ptr)->data);
    free(*obj_ptr_ptr);
    *obj_ptr_ptr = NULL;
}

const char *get_object_type(Obj_ptr obj_ptr)
{
    if (!obj_ptr)
        return type_name[NONE];
    switch (obj_ptr->type)
    {
    case NONE:
        return type_name[NONE];
    case INTEGER:
        return type_name[INTEGER];
    case FLOAT:
        return type_name[FLOAT];
    case DOUBLE:
        return type_name[DOUBLE];
    case CHAR:
        return type_name[CHAR];
    case STRING:
        return type_name[STRING];
    case WASTRING:
        return type_name[WASTRING];
    default:
        return type_name[NONE];
    }
}

size_t get_object_size(Obj_ptr obj_ptr)
{
    if (!obj_ptr)
        return 0;
    switch (obj_ptr->type)
    {
    case CHAR:
        return obj_ptr->buffer_size;
    case INTEGER:
        return obj_ptr->buffer_size / sizeof(int);
    case DOUBLE:
        return obj_ptr->buffer_size / sizeof(double);
    case FLOAT:
        return obj_ptr->buffer_size / sizeof(float);
    case STRING:
        return obj_ptr->buffer_size;
    default:
        return 0;
    }
}

Obj_ptr create_object()
{
    Obj_ptr obj = (Obj_ptr)malloc(sizeof(Object));
    obj->data = NULL;
    obj->type = NONE;
    obj->buffer_size = 0;
    return obj;
}

value get_object_value(Obj_ptr obj_ptr)
{
    value val = {0};
    if (!obj_ptr)
        return val;
    switch (obj_ptr->type)
    {
    case INTEGER:
        val.i_int = get_object_int(obj_ptr);
        break;
    case FLOAT:
        val.i_float = get_object_float(obj_ptr);
        break;
    case DOUBLE:
        val.i_double = get_object_double(obj_ptr);
        break;
    case CHAR:
        val.i_char = get_object_char(obj_ptr);
        break;
    case STRING:
        if (val.i_string)
            free(val.i_string);
        val.i_string = (char *)malloc(sizeof(char) * obj_ptr->buffer_size);
        strcpy_s(val.i_string, obj_ptr->buffer_size, get_object_char_ptr(obj_ptr));
        break;
     case WASTRING:
        if(val.i_wastring)
            destroy_wastring(&val.i_wastring);
        val.i_wastring = create_wastring_initstr(get_object_wastring(obj_ptr)->data);
        break;
    default:
        break;
    }
    return val;
}

void printf_object_value(const char *format, va_list ap)
{
    if (!format)
        return;
    const char *p = format;
    while (*p != '\0')
    {
        if (*p == '%')
        {
            p++;
            switch (*p)
            {
                // 不打印类型
            case 'o':
            {
                Obj_ptr obj = va_arg(ap, Obj_ptr);
                if (!obj)
                {
                    printf("NULL obj");
                    break;
                }
                value val = get_object_value(obj);
                switch (obj->type)
                {
                case CHAR:
                    printf("%c", val.i_char);
                    break;
                case INTEGER:
                    printf("%d", val.i_int);
                    break;
                case FLOAT:
                    printf("%.2f", val.i_float);
                    break;
                case DOUBLE:
                    printf("%.4f", val.i_double);
                    break;
                case STRING:
                    printf("%s", val.i_string);
                    break;
                case WASTRING:
                    printf("%s", val.i_wastring->data);
                    break;
                default:
                    printf("none");
                    break;
                }
                break;
            }
            case 'O':
            {
                Obj_ptr obj = va_arg(ap, Obj_ptr);
                if (!obj)
                {
                    printf("NULL obj");
                    break;
                }
                printf("[%s]", get_object_type(obj));
                value val = get_object_value(obj);
                switch (obj->type)
                {
                case CHAR:
                    printf("%c", val.i_char);
                    break;
                case INTEGER:
                    printf("%d", val.i_int);
                    break;
                case FLOAT:
                    printf("%.2f", val.i_float);
                    break;
                case DOUBLE:
                    printf("%.4f", val.i_double);
                    break;
                case STRING:
                    printf("%s", val.i_string);
                    break;
                 case WASTRING:
                    printf("%s", val.i_wastring->data);
                    break;
                default:
                    printf("none");
                    break;
                }
                break;
            }
            case 'V':
            {
                value val = va_arg(ap, value);
                obj_type type = va_arg(ap, obj_type);
                switch (type)
                {
                case CHAR:
                    printf("%c", val.i_char);
                    break;
                case INTEGER:
                    printf("%d", val.i_int);
                    break;
                case FLOAT:
                    printf("%.2f", val.i_float);
                    break;
                case DOUBLE:
                    printf("%.4f", val.i_double);
                    break;
                case STRING:
                    printf("%s", val.i_string);
                    break;
                 case WASTRING:
                    printf("%s", val.i_wastring->data);
                    break;
                default:
                    printf("none");
                    break;
                }
                break;
            }
            case 'd':
                printf("%d", va_arg(ap, int));
                break;
            case 'c':
                printf("%c", va_arg(ap, int));
                break;
            case 'f':
                printf("%.2f", va_arg(ap, double));
                break;
            case 's':
                printf("%s", va_arg(ap, char *));
                break;
            case '%':
                printf("%%");
                break;
            default:
                printf("%%%c", *p);
                break;
            }
            p++;
        }
        else
        {
            putchar(*p);
            p++;
        }
    }
}

void print_object(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    printf_object_value(format, ap);
    va_end(ap);
}

void copy_object_value(Obj_ptr dest, Obj_ptr src)
{
    if (!dest || !src || !src->data)
        return;
    value val = get_object_value(src);
    switch (src->type)
    {
    case CHAR:
        set_object_char(dest, val.i_char);
        break;
    case INTEGER:
        set_object_int(dest, val.i_int);
        break;
    case FLOAT:
        set_object_float(dest, val.i_float);
        break;
    case DOUBLE:
        set_object_double(dest, val.i_double);
        break;
    case STRING:
        set_object_char_ptr(dest, val.i_string);
        break;
    case WASTRING:
        break;
    default:
        break;
    }
}

void set_object_int_wrap(Obj_ptr obj_ptr, void *data)
{
    if (!data)
        return;
    set_object_int(obj_ptr, *(int *)data);
}
void set_object_float_wrap(Obj_ptr obj_ptr, void *data)
{
    if (!data)
        return;
    set_object_float(obj_ptr, *(float *)data);
}
void set_object_double_wrap(Obj_ptr obj_ptr, void *data)
{
    if (!data)
        return;
    set_object_double(obj_ptr, *(double *)data);
}
void set_object_char_wrap(Obj_ptr obj_ptr, void *data)
{
    if (!data)
        return;
    set_object_char(obj_ptr, *(char *)data);
}
void set_object_char_ptr_wrap(Obj_ptr obj_ptr, void *data)
{
    if (!data)
        return;
    set_object_char_ptr(obj_ptr, (char *)data);
}

int cmp_object_value(Obj_ptr obj_ptr, void *data)
{
    if (!data)
        return -2;
    switch (obj_ptr->type)
    {
    case CHAR:
    {
        char value = *(char *)data;
        char me = get_object_char(obj_ptr);
        if (me > value)
            return 1;
        else if (me < value)
            return -1;
        else
            return 0;
    }
    case INTEGER:
    {
        int value = *(int *)data;
        int me = get_object_int(obj_ptr);
        if (me > value)
            return 1;
        else if (me < value)
            return -1;
        else
            return 0;
    }
    case FLOAT:
    {
        float value = *(float *)data;
        float me = get_object_float(obj_ptr);
        if (me > value)
            return 1;
        else if (me < value)
            return -1;
        else
            return 0;
    }
    case DOUBLE:
    {
        double value = *(double *)data;
        double me = get_object_double(obj_ptr);
        if (me > value)
            return 1;
        else if (me < value)
            return -1;
        else
            return 0;
    }
    case STRING:
        return strcmp(get_object_char_ptr(obj_ptr), (char *)data);
        break;
    default:
        return -2;
        break;
    }
}

typedef void (*SETOBJECT)(Obj_ptr obj_ptr, void *data);


//待实现,object转字符串
const char* obj_to_string(Obj_ptr obj_ptr)
{
    if(!obj_ptr)return NULL;
    obj_type type = obj_ptr->type;
    //value val = get_object_value(obj_ptr);
    char* res;
    switch (type)
    {
    case CHAR:
        res = (char*)(malloc(sizeof(char) * 2));
        *res = get_object_char(obj_ptr);
        res[1] = '\0';
        return res;
        break;
    case INTEGER:
        return (char*)double_to_string(get_object_int(obj_ptr));
        break;
    case FLOAT:
        return (char*)double_to_string(get_object_float(obj_ptr));
        break;
    case DOUBLE:
        return (char*)double_to_string(get_object_double(obj_ptr));
        break;
    case STRING:
        return (char*)get_object_char_ptr(obj_ptr);
        break;
    default:
        return NULL;
        break;
    }
}

// 类型-函数指针映射表
static const SETOBJECT set_object_funcs[] = {
    [INTEGER] = set_object_int_wrap,
    [FLOAT] = set_object_float_wrap,
    [DOUBLE] = set_object_double_wrap,
    [CHAR] = set_object_char_wrap,
    [STRING] = set_object_char_ptr_wrap};

#define PRINT_OBJECT(format, ...) print_object(format, ##__VA_ARGS__)


Obj_ptr create_object_wastring()
{
    Obj_ptr obj = create_object();
    obj->type = WASTRING;
    obj->data = create_wastring();
    obj->buffer_size = sizeof(wastring);
    return obj;
}

void set_object_wastring(Obj_ptr obj_ptr, str_ptr str)
{
    if(!obj_ptr)return;
    if(obj_ptr->type != WASTRING)free_object(obj_ptr);
    if(!obj_ptr->data){
        obj_ptr->data = create_wastring_initstr(str->data);
        obj_ptr->type = WASTRING;
        obj_ptr->buffer_size = sizeof(wastring);
        return;
    }
    wa_clear((str_ptr)obj_ptr->data);
    wa_append((str_ptr)obj_ptr->data, str->data);
}

str_ptr get_object_wastring(Obj_ptr obj_ptr)
{
    if(!obj_ptr)return NULL;
    return (str_ptr)obj_ptr->data;
}


#endif