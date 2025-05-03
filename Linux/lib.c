#include <linux/seccomp.h>
#include <linux/prctl.h>
#include <sys/syscall.h>
#include <sys/prctl.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>

void
sandbox0(void)
{
	if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) == -1)
		warn("%s", "prctl: PR_SET_NO_NEW_PRIVS");

#if 1
	if (syscall(SYS_seccomp, SECCOMP_SET_MODE_STRICT, 0, NULL) == -1 && errno != ENOSYS)
		warn("%s", "seccomp");
#else
	if (prctl(PR_SET_SECCOMP, SECCOMP_MODE_STRICT) == -1 && errno != ENOSYS)
		warn("%s", "prctl: SECCOMP_MODE_STRICT");
#endif
}
