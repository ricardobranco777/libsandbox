#include <unistd.h>
#include <err.h>

void
sandbox0(void)
{
	if (pledge("stdio", NULL) < 0)
		warn("pledge");

	if (unveil(NULL, NULL) < 0)
		warn("unveil");
}
