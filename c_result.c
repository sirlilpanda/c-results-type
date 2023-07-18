#include <stdio.h>
#include <stdlib.h>

#define Result_t_type(ok_type, error_type, type)          \
    struct Result_t {                                      \
        union Data_U{ok_type ok; error_type error;} data;   \
        _Bool has_errored;                                   \
    } type;                                                   \

#define Result_t_funcs(ok_type, error_type, tpye)                                                            \
    tpye tpye##Ok(ok_type ok){return (tpye) {ok, 0};};                                                        \
    tpye tpye##error(error_type error){return (tpye) {error, 1};};                                             \
    ok_type tpye##unwrap(tpye result){if (!result.has_errored) {return result.data.ok;} exit(1);}               \
    ok_type tpye##unwrapor(tpye result, ok_type or){if (!result.has_errored) {return result.data.ok;} return or;}\
    
//you must call this with a type def to avoid complier checks
#define Result_t(ok_type, error_type, type)\
    Result_t_type(ok_type, error_type, type)\
    Result_t_funcs(ok_type, error_type, type)\

typedef enum numberAddingErrors_s{
    NUMBERS_NOT_EVEN,
}numberAddingErrors_t;

typedef Result_t(int, numberAddingErrors_t, Result_int_int_t);

Result_int_int_t add_even_nums(int num1, int num2){
    if (num1%2 == 0 && num2%2 == 0){
        int num3 = num1+num2;
        Result_int_int_tOk(num3);
    } 
    else {
        Result_int_int_terror(NUMBERS_NOT_EVEN);
    }
}

int main(int argc, char const *argv[])
{
    int n1 = 4;
    int n2 = 5;
    Result_int_int_t answer = add_even_nums(n1, n2);
    int a = Result_int_int_tunwrap(answer);
    printf("%d\n", a);
    return 0;
}
