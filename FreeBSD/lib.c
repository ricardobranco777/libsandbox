#include <capsicum_helpers.h>
#include <err.h>

void
sandbox0(void)
{
	caph_cache_catpages();
	caph_cache_tzdata();

	if (caph_limit_stdio() < 0)
		warn("%s", "caph_limit_stdio");

	if (caph_enter() < 0)
		warn("%s", "caph_enter");
}
