#ifndef __LIBC_FUNC_H__
#define __LIBC_FUNC_H__

#include <dlfcn.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

typedef ssize_t(*lib_write_type)(int, const void *, size_t);
extern lib_write_type lib_write;

typedef ssize_t(*lib_read_type)(int , void *, size_t);
extern lib_read_type lib_read;

typedef FILE *(*lib_fopen_type)(const char *, const char *);
extern lib_fopen_type lib_fopen;

typedef FILE *(*lib_freopen_type)(const char *, const char *, FILE *);
extern lib_freopen_type lib_freopen;

typedef size_t(*lib_fwrite_type)(const void *, size_t, size_t, FILE *);
extern lib_fwrite_type lib_fwrite;

typedef size_t(*lib_fread_type)(void *, size_t, size_t, FILE *);
extern lib_fread_type lib_fread;

typedef int(*lib_fclose_type)(FILE *);
extern lib_fclose_type lib_fclose;

typedef int(*lib_access_type)(const char *, int);
extern lib_access_type lib_access;

typedef int(*lib_unlink_type)(const char *);
extern lib_unlink_type lib_unlink;

typedef int(*lib_remove_type)(const char *);
extern lib_remove_type lib_remove;

typedef int(*lib_rename_type)(const char *, const char *);
extern lib_rename_type lib_rename;

typedef ssize_t(*lib_readlink_type)(const char *, char *, size_t);
extern lib_readlink_type lib_readlink;

typedef mode_t(*lib_umask_type)(mode_t);
extern lib_umask_type lib_umask;

typedef pid_t(*lib_getpid_type)();
extern lib_getpid_type lib_getpid;

typedef uid_t(*lib_geteuid_type)();
extern lib_geteuid_type lib_geteuid;

typedef pid_t(*lib_fork_type)();
extern lib_fork_type lib_fork;

typedef pid_t(*lib_waitpid_type)(pid_t, int *, int);
extern lib_waitpid_type lib_waitpid;

typedef int(*lib_system_type)(const char *);
extern lib_system_type lib_system;

typedef int(*lib_socket_type)(int, int, int);
extern lib_socket_type lib_socket;

typedef uint16_t(*lib_htons_type)(uint16_t);
extern lib_htons_type lib_htons;

typedef int(*lib_getaddrinfo_type)(const char *, const char *, const struct addrinfo *, struct addrinfo **);
extern lib_getaddrinfo_type lib_getaddrinfo;

typedef int(*lib_connect_type)(int, const struct sockaddr *, socklen_t);
extern lib_connect_type lib_connect;

typedef ssize_t(*lib_send_type)(int, const void *, size_t, int);
extern lib_send_type lib_send;

typedef ssize_t(*lib_recv_type)(int, void *, size_t, int);
extern lib_recv_type lib_recv;

typedef int(*lib_bind_type)(int, const struct sockaddr *, socklen_t);
extern lib_bind_type lib_bind;

typedef int(*lib_listen_type)(int, int);
extern lib_listen_type lib_listen;

typedef int(*lib_pthread_create_type)(pthread_t *, const pthread_attr_t *, void *(*start_routine)(void *), void *);
extern lib_pthread_create_type lib_pthread_create;

typedef int(*lib_kill_type)(int, int);
extern lib_kill_type lib_kill;

typedef void (*sighandler_t)(int);
typedef sighandler_t(*lib_signal_type)(int, sighandler_t);
extern lib_signal_type lib_signal;

typedef void (*lib_exit_type)(int) __attribute__((__noreturn__));
extern __attribute__((__noreturn__)) lib_exit_type lib_exit;

typedef unsigned int(*lib_sleep_type)(unsigned int);
extern lib_sleep_type lib_sleep;

#endif // __LIBC_FUNC_H__