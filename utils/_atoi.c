#include "_atoi.h"
#include "_strlen.h"

static int _atoi_rec(char* str);

int _atoi (char* str)
{
    if (str[0] == '-') {
        return -_atoi_rec(&str[1]);
    }
    return _atoi_rec(str);
}

int _atoi_rec(char* str)
{
    unsigned char num_len = _strlen(str);
    if (num_len == 0 || !('0' <= str[num_len - 1] && str[num_len - 1] <= '9')) {
        return 0;
    }
    unsigned char last_digit = str[num_len - 1] - '0';
    str[num_len - 1] = '\0';
    return last_digit + 10 * _atoi_rec(str);
}
