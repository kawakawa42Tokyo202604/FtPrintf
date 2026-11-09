#include "ft_printf.h"

int main(void)
{
    int count;

    count = ft_printf("%s: %d\n", "answer", 42);
    return (count != 11);
}
