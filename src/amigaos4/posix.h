/*
 * posix_amiga.h
 *
 *  Created on: 4 May 2020
 *      Author: billy
 */

#ifndef LIBGIT2_SRC_AMIGAOS4_POSIX_H_
#define LIBGIT2_SRC_AMIGAOS4_POSIX_H_

#include "fcntl.h"
#include "dirent.h"

#include <unistd.h>
#include <sys/socket.h>
#include <time.h>

#include "amigaos4/amiga-compat.h"


/* extern int p_fsync(int fd); */

#include <proto/dos.h>
#include <proto/bsdsocket.h>

typedef int GIT_SOCKET;

extern size_t p_fsync__cnt;



typedef int GIT_SOCKET;
#define INVALID_SOCKET -1

#define p_lseek(f,n,w) lseek(f, n, w)
#define p_fstat(f,b) fstat(f, b)
#define p_lstat(p,b) lstat(p,b)
#define p_stat(p,b) stat(p, b)

#if defined(GIT_USE_STAT_MTIMESPEC)
# define st_atime_nsec st_atimespec.tv_nsec
# define st_mtime_nsec st_mtimespec.tv_nsec
# define st_ctime_nsec st_ctimespec.tv_nsec
#elif defined(GIT_USE_STAT_MTIM)
# define st_atime_nsec st_atim.tv_nsec
# define st_mtime_nsec st_mtim.tv_nsec
# define st_ctime_nsec st_ctim.tv_nsec
#elif !defined(GIT_USE_STAT_MTIME_NSEC) && defined(GIT_USE_NSEC)
# error GIT_USE_NSEC defined but unknown struct stat nanosecond type
#endif


#define p_readlink(a, b, c) readlink(a, b, c)
#define p_symlink(o,n) symlink(o, n)
#define p_link(o,n) link(o, n)
#define p_unlink(p) unlink(p)
#define p_mkdir(p,m) mkdir(p, m)
#define p_realpath(a,b) realpath(a,b)





extern int p_inet_pton(int af, const char *src, void *dst);

#define p_strcasecmp(s1, s2) strcasecmp(s1, s2)
#define p_strncasecmp(s1, s2, c) strncasecmp(s1, s2, c)
#define p_vsnprintf(b, c, f, a) vsnprintf(b, c, f, a)
#define p_snprintf snprintf
#define p_mkstemp(p) mkstemp(p)
#define p_chdir(p) chdir(p)
#define p_chmod(p,m) chmod(p, m)
#define p_rmdir(p) rmdir(p)
#define p_access(p,m) access(p,m)
#define p_ftruncate(fd, sz) ftruncate(fd, sz)

/* see win32/posix.h for explanation about why this exists */
#define p_lstat_posixly(p,b) lstat(p,b)

#define p_localtime_r(c, r) localtime_r(c, r)
#define p_gmtime_r(c, r) gmtime_r(c, r)

#define p_timeval timeval

#ifdef GIT_USE_FUTIMENS
GIT_INLINE(int) p_futimes(int f, const struct p_timeval t[2])
{
	struct timespec s[2];
	s[0].tv_sec = t[0].tv_sec;
	s[0].tv_nsec = t[0].tv_usec * 1000;
	s[1].tv_sec = t[1].tv_sec;
	s[1].tv_nsec = t[1].tv_usec * 1000;
	return futimens(f, s);
}
#else
# define p_futimes futimes
#endif



extern int socket(int domain, int type, int protocol);
extern int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
extern struct servent *getservbyname(const char *name, const char *proto);
extern struct hostent *gethostbyname(const char *name);
extern int p_utimes(const char *filename, const struct timeval times[2]);
extern ssize_t p_send(int sockfd, const void *buf, size_t len, int flags);
extern ssize_t p_recv(int sockfd, void *buf, size_t len, int flags);

extern char *strndup (const char *src, size_t n);

extern char *getpass(const char *prompt);

GIT_INLINE(int) p_fsync(int fd)
{
	p_fsync__cnt ++;
	return fsync (fd);
}







#endif /* LIBGIT2_SRC_AMIGAOS4_POSIX_H_ */
