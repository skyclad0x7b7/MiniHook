#include "hook.h"

lib_fopen_type lib_fopen = NULL;
lib_freopen_type lib_freopen = NULL;
lib_fwrite_type lib_fwrite = NULL;
lib_fread_type lib_fread = NULL;
lib_fclose_type lib_fclose = NULL;
lib_access_type lib_access = NULL;
lib_unlink_type lib_unlink = NULL;
lib_remove_type lib_remove = NULL;
lib_rename_type lib_rename = NULL;
lib_readlink_type lib_readlink = NULL;
lib_umask_type lib_umask = NULL;
lib_getpid_type lib_getpid = NULL;
lib_geteuid_type lib_geteuid = NULL;
lib_fork_type lib_fork = NULL;
lib_waitpid_type lib_waitpid = NULL;
lib_system_type lib_system = NULL;
lib_socket_type lib_socket = NULL;
lib_htons_type lib_htons = NULL;
lib_getaddrinfo_type lib_getaddrinfo = NULL;
lib_connect_type lib_connect = NULL;
lib_send_type lib_send = NULL;
lib_recv_type lib_recv = NULL;
lib_bind_type lib_bind = NULL;
lib_listen_type lib_listen = NULL;
lib_pthread_create_type lib_pthread_create = NULL;
lib_kill_type lib_kill = NULL;
lib_signal_type lib_signal = NULL;
lib_exit_type lib_exit = NULL;
lib_sleep_type lib_sleep = NULL;

static void con() __attribute__((constructor));
void con()
{
    lib_fopen = (lib_fopen_type)dlsym(RTLD_NEXT, "fopen");
    lib_freopen = (lib_freopen_type)dlsym(RTLD_NEXT, "freopen");
    lib_fwrite = (lib_fwrite_type)dlsym(RTLD_NEXT, "fwrite");
    lib_fread = (lib_fread_type)dlsym(RTLD_NEXT, "fread");
    lib_fclose = (lib_fclose_type)dlsym(RTLD_NEXT, "fclose");
    lib_access = (lib_access_type)dlsym(RTLD_NEXT, "access");
    lib_unlink = (lib_unlink_type)dlsym(RTLD_NEXT, "unlink");
    lib_remove = (lib_remove_type)dlsym(RTLD_NEXT, "remove");
    lib_rename = (lib_rename_type)dlsym(RTLD_NEXT, "rename");
    lib_readlink = (lib_readlink_type)dlsym(RTLD_NEXT, "readlink");
    lib_umask = (lib_umask_type)dlsym(RTLD_NEXT, "umask");
    lib_getpid = (lib_getpid_type)dlsym(RTLD_NEXT, "getpid");
    lib_geteuid = (lib_geteuid_type)dlsym(RTLD_NEXT, "geteuid");
    lib_fork = (lib_fork_type)dlsym(RTLD_NEXT, "fork");
    lib_waitpid = (lib_waitpid_type)dlsym(RTLD_NEXT, "waitpid");
    lib_system = (lib_system_type)dlsym(RTLD_NEXT, "system");
    lib_socket = (lib_socket_type)dlsym(RTLD_NEXT, "socket");
    lib_connect = (lib_connect_type)dlsym(RTLD_NEXT, "connect");
    lib_htons = (lib_htons_type)dlsym(RTLD_NEXT, "htons");
    lib_getaddrinfo = (lib_getaddrinfo_type)dlsym(RTLD_NEXT, "getaddrinfo");
    lib_send = (lib_send_type)dlsym(RTLD_NEXT, "send");
    lib_recv = (lib_recv_type)dlsym(RTLD_NEXT, "recv");
    lib_bind = (lib_bind_type)dlsym(RTLD_NEXT, "bind");
    lib_listen = (lib_listen_type)dlsym(RTLD_NEXT, "listen");
    lib_pthread_create = (lib_pthread_create_type)dlsym(RTLD_NEXT, "pthread_create");
    lib_kill = (lib_kill_type)dlsym(RTLD_NEXT, "kill");
    lib_signal = (lib_signal_type)dlsym(RTLD_NEXT, "signal");
    lib_exit = (lib_exit_type)dlsym(RTLD_NEXT, "exit");
    lib_sleep = (lib_sleep_type)dlsym(RTLD_NEXT, "sleep");
}

 /* ========================================================== */

FILE *fopen(const char *filename, const char *mode)
{
    Variable args[2] = { 
        Variable(VariableType::VT_char_array, (PTR_TYPE)filename),
        Variable(VariableType::VT_char_array, (PTR_TYPE)mode)
    };
    Logger::instance().log(MakeLogString("fopen", 2, args) + "\n");

    FILE *ret = lib_fopen(filename, mode);
    return ret;
}

FILE *freopen(const char *filename, const char *mode, FILE *stream)
{
    Variable args[3] = { 
        Variable(VariableType::VT_char_array, (PTR_TYPE)filename),
        Variable(VariableType::VT_char_array, (PTR_TYPE)mode),
        Variable(VariableType::VT_offset, (PTR_TYPE)stream)
    };
    Logger::instance().log(MakeLogString("freopen", 3, args) + "\n");

    FILE *ret = lib_freopen(filename, mode, stream);
    return ret;
}

size_t fwrite(const void *buffer, size_t size, size_t count, FILE *stream)
{
    Variable args[4] = { 
        Variable(VariableType::VT_char_array, (PTR_TYPE)buffer),
        Variable(VariableType::VT_unsigned_int, (PTR_TYPE)size),
        Variable(VariableType::VT_unsigned_int, (PTR_TYPE)count),
        Variable(VariableType::VT_offset, (PTR_TYPE)stream)
    };
    Logger::instance().log(MakeLogString("fwrite", 4, args) + "\n");

    size_t *ret = lib_fwrite(buffer, size, count, stream);
    return ret;
}

int fprintf(FILE *stream, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    char tmp[1024] = {0,};
    vsnprintf(tmp, sizeof(tmp), format, ap);
    Variable args[2] = { 
        Variable(VariableType::VT_offset, (PTR_TYPE)stream),
        Variable(VariableType::VT_char_array, (PTR_TYPE)tmp),
    };
    Logger::instance().log(MakeLogString("fprintf", 2, args) + "\n");
    va_end(ap);

    va_start(ap, format);
    int ret = vfprintf(stream, format, ap);
    va_end(ap);
    return ret;
}

size_t fread(void *buffer, size_t size, size_t count, FILE *stream)
{
    Variable args[4] = { 
        Variable(VariableType::VT_offset, (PTR_TYPE)buffer),
        Variable(VariableType::VT_unsigned_int, (PTR_TYPE)size),
        Variable(VariableType::VT_unsigned_int, (PTR_TYPE)count),
        Variable(VariableType::VT_offset, (PTR_TYPE)stream)
    };
    Logger::instance().log(MakeLogString("fread", 4, args) + "\n");

    size_t *ret = lib_fread(buffer, size, count, stream);
    return ret;
}

int fclose(FILE *stream)
{
    Variable args[1] = { 
        Variable(VariableType::VT_offset, (PTR_TYPE)stream)
    };
    Logger::instance().log(MakeLogString("fclose", 1, args) + "\n");

    int ret = lib_fclose(stream);
    return ret; 
}

int access(const char *pathname, int mode)
{
    Variable args[2] = { 
        Variable(VariableType::VT_char_array, (PTR_TYPE)pathname),
        Variable(VariableType::VT_int, (PTR_TYPE)mode)
    };
    Logger::instance().log(MakeLogString("access", 2, args) + "\n");

    int ret = lib_access(pathname, mode);
    return ret; 
}

int unlink(const char *filename)
{
    Variable args[1] = { 
        Variable(VariableType::VT_char_array, (PTR_TYPE)filename)
    };
    Logger::instance().log(MakeLogString("unlink", 1, args) + "\n");

    int ret = lib_unlink(filename);
    return ret;
}

int remove(const char *filename)
{
    Variable args[1] = { 
        Variable(VariableType::VT_char_array, (PTR_TYPE)filename)
    };
    Logger::instance().log(MakeLogString("remove", 1, args) + "\n");

    int ret = lib_remove(filename);
    return ret;
}

int rename(const char *oldname, const char *newname)
{
    Variable args[2] = { 
        Variable(VariableType::VT_char_array, (PTR_TYPE)oldname),
        Variable(VariableType::VT_char_array, (PTR_TYPE)newname)
    };
    Logger::instance().log(MakeLogString("rename", 2, args) + "\n");

    int ret = lib_rename(oldname, newname);
    return ret;
}

ssize_t readlink(const char *path, char *buf, size_t bufsize)
{
    Variable args[3] = { 
        Variable(VariableType::VT_char_array, (PTR_TYPE)path),
        Variable(VariableType::VT_offset, (PTR_TYPE)buf),
        Variable(VariableType::VT_unsigned_int, (PTR_TYPE)bufsize)
    };

    Logger::instance().log(MakeLogString("readlink", 3, args) + "\n");
    ssize_t ret = lib_readlink(path, buf, bufsize);
    return ret;
}

mode_t umask(mode_t mode)
{
    Variable args[1] = { 
        Variable(VariableType::VT_unsigned_int, (PTR_TYPE)mode)
    };
    Logger::instance().log(MakeLogString("umask", 1, args) + "\n");

    mode_t ret = lib_umask(mode);
    return ret;
}

pid_t getpid()
{
    Logger::instance().log(MakeLogString("getpid", 0, NULL) + "\n");
    pid_t ret = lib_getpid();
    return ret;
}

uid_t geteuid()
{
    Logger::instance().log(MakeLogString("geteuid", 0, NULL) + "\n");
    uid_t ret = lib_geteuid();
    return ret;
}

pid_t fork()
{
    pid_t ret = lib_fork();
    Logger::instance().reopen_logfile(); // must be called after fork
    Logger::instance().log(MakeLogString("fork", 0, NULL) + "\n");
    return ret;
}

pid_t waitpid(pid_t pid, int *stat_loc, int options)
{
    Variable args[3] = { 
        Variable(VariableType::VT_unsigned_int, (PTR_TYPE)pid),
        Variable(VariableType::VT_int, (PTR_TYPE)stat_loc),
        Variable(VariableType::VT_int, (PTR_TYPE)options)
    };
    Logger::instance().log(MakeLogString("waitpid", 3, args) + "\n");

    pid_t ret = lib_waitpid(pid, stat_loc, options);
    return ret;
}

int system(const char *command)
{
    Variable args[1] = { 
        Variable(VariableType::VT_char_array, (PTR_TYPE)command)
    };
    Logger::instance().log(MakeLogString("system", 1, args) + "\n");

    int ret = lib_system(command);
    return ret;
}

int socket(int domain, int type, int protocol)
{
    Variable args[3] = { 
        Variable(VariableType::VT_int, (PTR_TYPE)domain),
        Variable(VariableType::VT_int, (PTR_TYPE)type),
        Variable(VariableType::VT_int, (PTR_TYPE)protocol)
    };
    Logger::instance().log(MakeLogString("socket", 3, args) + "\n");

    int ret = lib_socket(domain, type, protocol);
    return ret;
}

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    Variable args[3] = { 
        Variable(VariableType::VT_int, (PTR_TYPE)sockfd),
        Variable(VariableType::VT_offset, (PTR_TYPE)addr),
        Variable(VariableType::VT_unsigned_int, (PTR_TYPE)addrlen)
    };
    Logger::instance().log(MakeLogString("connect", 3, args) + "\n");

    int ret = lib_connect(sockfd, addr, addrlen);
    return ret;
}

uint16_t htons(uint16_t hostshort)
{
    Variable args[1] = { 
        Variable(VariableType::VT_unsigned_short, (PTR_TYPE)hostshort)
    };
    Logger::instance().log(MakeLogString("htons", 1, args) + "\n");

    uint16_t ret = lib_htons(hostshort);
    return ret;
}

int getaddrinfo(const char *name, const char *service, const struct addrinfo *req, struct addrinfo **pai)
{
    Variable args[4] = { 
        Variable(VariableType::VT_char_array, (PTR_TYPE)name),
        Variable(VariableType::VT_char_array, (PTR_TYPE)service),
        Variable(VariableType::VT_offset, (PTR_TYPE)req),
        Variable(VariableType::VT_offset, (PTR_TYPE)pai)
    };
    Logger::instance().log(MakeLogString("getaddrinfo", 4, args) + "\n");

    int ret = lib_getaddrinfo(name, service, req, pai);
    return ret;
}

ssize_t send(int s, const void *msg, size_t len, int flags)
{
    Variable args[4] = { 
        Variable(VariableType::VT_int, (PTR_TYPE)s),
        Variable(VariableType::VT_offset, (PTR_TYPE)msg),
        Variable(VariableType::VT_unsigned_int, (PTR_TYPE)len),
        Variable(VariableType::VT_int, (PTR_TYPE)flags)
    };
    Logger::instance().log(MakeLogString("send", 4, args) + "\n");

    ssize_t ret = lib_send(s, msg, len, flags);
    return ret;
}

ssize_t recv(int s, void *buf, size_t len, int flags)
{
    Variable args[4] = { 
        Variable(VariableType::VT_int, (PTR_TYPE)s),
        Variable(VariableType::VT_offset, (PTR_TYPE)buf),
        Variable(VariableType::VT_unsigned_int, (PTR_TYPE)len),
        Variable(VariableType::VT_int, (PTR_TYPE)flags)
    };
    Logger::instance().log(MakeLogString("recv", 4, args) + "\n");

    ssize_t ret = lib_recv(s, buf, len, flags);
    return ret;
}

int bind(int socket, const struct sockaddr *address, socklen_t address_len)
{
    Variable args[3] = { 
        Variable(VariableType::VT_int, (PTR_TYPE)socket),
        Variable(VariableType::VT_offset, (PTR_TYPE)address),
        Variable(VariableType::VT_unsigned_int, (PTR_TYPE)address_len)
    };
    Logger::instance().log(MakeLogString("bind", 3, args) + "\n");

    int ret = lib_bind(socket, address, address_len);
    return ret;
}

int listen(int socket, int backlog)
{
    Variable args[2] = { 
        Variable(VariableType::VT_int, (PTR_TYPE)socket),
        Variable(VariableType::VT_int, (PTR_TYPE)backlog)
    };
    Logger::instance().log(MakeLogString("listen", 2, args) + "\n");

    int ret = lib_listen(socket, backlog);
    return ret;
}

int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *restrictarg)
{
    Variable args[4] = { 
        Variable(VariableType::VT_offset, (PTR_TYPE)thread),
        Variable(VariableType::VT_offset, (PTR_TYPE)attr),
        Variable(VariableType::VT_offset, (PTR_TYPE)start_routine),
        Variable(VariableType::VT_offset, (PTR_TYPE)restrictarg)
    };
    Logger::instance().log(MakeLogString("pthread_create", 4, args) + "\n");

    int ret = lib_pthread_create(thread, attr, start_routine, restrictarg);
    return ret;
}

sighandler_t signal(int signum, sighandler_t handler)
{
    Variable args[2] = { 
        Variable(VariableType::VT_int, (PTR_TYPE)signum),
        Variable(VariableType::VT_offset, (PTR_TYPE)handler)
    };
    Logger::instance().log(MakeLogString("signal", 2, args) + "\n");

    sighandler_t ret = lib_signal(signum, handler);
    return ret;
}

void exit(int status)
{
    Variable args[1] = { 
        Variable(VariableType::VT_int, (PTR_TYPE)status)
    };
    Logger::instance().log(MakeLogString("exit", 1, args) + "\n");

    lib_exit(status);
}

unsigned int sleep(unsigned int seconds)
{
    Variable args[1] = { 
        Variable(VariableType::VT_unsigned_int, (PTR_TYPE)seconds)
    };
    Logger::instance().log(MakeLogString("sleep", 1, args) + "\n");
    
    unsigned int ret = lib_sleep(seconds);
    return ret;
}