#include <linux/landlock.h>
#include <linux/seccomp.h>
#include <linux/prctl.h>
#include <sys/syscall.h>
#include <sys/prctl.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>

static void
landlock(void)
{
	struct landlock_ruleset_attr ruleset_attr = {
		.handled_access_fs = LANDLOCK_ACCESS_FS_READ_FILE | LANDLOCK_ACCESS_FS_READ_DIR,
	};
	int fd;

	fd = syscall(SYS_landlock_create_ruleset, &ruleset_attr, sizeof(ruleset_attr), 0);
	if (fd == -1) {
		if (errno != ENOSYS)
			warn("%s", "landlock_create_ruleset");
		return;
	}

	if (syscall(SYS_landlock_restrict_self, fd, 0) == -1 && errno != ENOSYS)
		warn("%s", "landlock_restrict_self");

	while (close(fd) == -1 && errno == EINTR)
		;
}

void
sandbox0(void)
{
	if (prctl(PR_SET_DUMPABLE, 0L) == -1)
		warn("%s", "prctl: PR_SET_DUMPABLE");

	if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) == -1)
		warn("%s", "prctl: PR_SET_NO_NEW_PRIVS");

	landlock();

	/* XXX After this seccomp, only read, write, _exit & sigreturn is allowed */
#if 1
	if (syscall(SYS_seccomp, SECCOMP_SET_MODE_STRICT, 0, NULL) == -1 && errno != ENOSYS)
		warn("%s", "seccomp");
#else
	if (prctl(PR_SET_SECCOMP, SECCOMP_MODE_STRICT) == -1 && errno != ENOSYS)
		warn("%s", "prctl: SECCOMP_MODE_STRICT");
#endif
}
