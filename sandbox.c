void sandbox0(void);

static void __attribute__ ((constructor)) _init (void)
{
	sandbox0();
}
