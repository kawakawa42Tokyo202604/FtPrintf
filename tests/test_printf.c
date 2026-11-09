#define _POSIX_C_SOURCE 200809L
#include "ft_printf.h"
#include <fcntl.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int checks;
static int failures;

static void check(int condition, const char *name)
{
	checks++;
	if (!condition)
	{
		fprintf(stderr, "FAIL: %s\n", name);
		failures++;
	}
}

#define CASE(...) do { \
	char expected[4096]; \
	char actual[4096]; \
	FILE *capture = tmpfile(); \
	int saved = dup(STDOUT_FILENO); \
	int wanted = snprintf(expected, sizeof(expected), __VA_ARGS__); \
	int result; \
	size_t count; \
	if (!capture || saved < 0) return (1); \
	fflush(stdout); \
	if (dup2(fileno(capture), STDOUT_FILENO) < 0) return (1); \
	result = ft_printf(__VA_ARGS__); \
	fflush(stdout); \
	if (dup2(saved, STDOUT_FILENO) < 0) return (1); \
	close(saved); \
	rewind(capture); \
	count = fread(actual, 1, sizeof(actual), capture); \
	fclose(capture); \
	check(result == wanted && count == (size_t)wanted \
		&& !memcmp(expected, actual, count), #__VA_ARGS__); \
} while (0)

int main(void)
{
	int value = 42;
	int saved;
	int readonly;
	int result;
	int (*printer)(const char *, ...) = ft_printf;

	CASE("%s", "");
	CASE("%s", "hello world");
	CASE("%c%c%c", 'A', '\0', 'Z');
	CASE("%d %i %d", INT_MIN, 0, INT_MAX);
	CASE("%u %u", 0U, UINT_MAX);
	CASE("%x %X %x", 0U, UINT_MAX, 42U);
	CASE("%p %p", (void *)&value, (void *)NULL);
	CASE("%s:%d:%u:%x:%X:%c:%%", "mix", -42, 42U, 42U, 42U, '!');
	CASE("literal %% and %%");
	check(printer("") == 0, "empty format");
	saved = dup(STDOUT_FILENO);
	readonly = open("/dev/null", O_RDONLY);
	if (saved < 0 || readonly < 0 || dup2(readonly, STDOUT_FILENO) < 0)
		return (1);
	result = ft_printf("%s", "write error");
	if (dup2(saved, STDOUT_FILENO) < 0)
		return (1);
	close(saved);
	close(readonly);
	check(result == -1, "write error returns -1");
	printf("ft_printf: %d checks, %d failures\n", checks, failures);
	return (failures != 0);
}
