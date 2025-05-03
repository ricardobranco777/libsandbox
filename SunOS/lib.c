#include <priv.h>
#include <err.h>

void
sandbox0(void)
{
	priv_set_t *empty;

	if ((empty = priv_allocset()) == NULL)
		warn("%s", "priv_allocset");

	priv_emptyset(empty);
	if (setppriv(PRIV_SET, PRIV_EFFECTIVE, empty) < 0)
		warn("%s", "setppriv");

	priv_freeset(empty);
}
