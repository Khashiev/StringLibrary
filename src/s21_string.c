#include "s21_string.h"

#include <stdio.h>   // delete
#include <string.h>  // delete

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;

  if (str) {
    for (int i = 0; str[i]; i++) {
      len++;
    }
  }

  return len;
}

void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *res = S21_NULL;
  char *ptr = (char *)str;

  for (s21_size_t i = 0; i < n && ptr && !res; i++, ptr++) {
    if (*ptr == c) {
      res = ptr;
    }
  }

  return res;
}

char *s21_strchr(const char *str, int c) {
  char *res = S21_NULL;

  for (; *str != '\0' && !res; str++) {
    if (*str == c) {
      res = (char *)str;
    }
  }

  return res;
}

char *s21_strrchr(const char *str, int c) {
  char *res = S21_NULL;
  s21_size_t len = s21_strlen(str);

  for (int i = len; i >= 0 && !res; i--) {
    if (str[i] == c) {
      res = (char *)str + i;
    }
  }

  return res;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = S21_NULL;

  for (; *str1 != '\0' && !res; str1++) {
    if (s21_strchr(str2, *str1)) {
      res = (char *)str1;
    }
  }

  return res;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *res = S21_NULL;
  s21_size_t hst_len = s21_strlen(haystack);
  s21_size_t ndl_len = s21_strlen(needle);

  if (hst_len >= ndl_len) {
    for (s21_size_t i = 0; i <= hst_len - ndl_len; i++) {
      int flag = 1;
      for (s21_size_t j = i, k = 0; needle[k]; k++, j++) {
        if (haystack[j] != needle[k]) {
          flag = 0;
          break;
        }
      }
      if (flag) {
        res = (char *)haystack + i;
        break;
      }
    }
  }
  return res;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t dest_len = s21_strlen(dest);
  s21_size_t i = 0;

  // for (; i < n && src[i]; i++) {
  //   dest[dest_len + i] = src[i];
  // }

  // dest[dest_len + i] = '\0';

  if (dest_len > 0) {
    for (; i < n && src[i] && dest[i]; i++) {
      dest[dest_len + i] = src[i];
    }

    dest[dest_len + i] = '\0';
  }

  return dest;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t res = 0;
  s21_size_t ptr = 0;

  for (s21_size_t i = 0; str1[i]; i++) {
    ptr = res;
    for (s21_size_t j = 0; str2[j]; j++) {
      if (str1[i] == str2[j]) {
        res++;
        break;
      }
    }
    if (ptr == res) break;
  }

  return res;
}

char *s21_strtok(char *str, const char *delim) {
  static char *tmp = S21_NULL;
  if (str) tmp = str;

  if (tmp) {
    str = tmp + s21_strspn(tmp, delim);
    tmp = str + strcspn(str, delim);  // change

    if (*tmp != '\0') {
      *tmp = '\0';
      tmp++;
    }
  }

  return *str != '\0' ? str : S21_NULL;
}

char *s21_strerror(int errnum) {
#ifdef __APPLE__
  char err_list[107][50] =
  { "Undefined error: 0",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "Device not configured",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource deadlock avoided",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Resource busy",
    "File exists",
    "Cross-device link",
    "Operation not supported by device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Result too large",
    "Resource temporarily unavailable",
    "Operation now in progress",
    "Operation already in progress",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol family",
    "Address already in use",
    "Can't assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Socket is already connected",
    "Socket is not connected",
    "Can't send after socket shutdown",
    "Too many references: can't splice",
    "Operation timed out",
    "Connection refused",
    "Too many levels of symbolic links",
    "File name too long",
    "Host is down",
    "No route to host",
    "Directory not empty",
    "Too many processes",
    "Too many users",
    "Disc quota exceeded",
    "Stale NFS file handle",
    "Too many levels of remote in path",
    "RPC struct is bad",
    "RPC version wrong",
    "RPC prog. not avail",
    "Program version wrong",
    "Bad procedure for program",
    "No locks available",
    "Function not implemented",
    "Inappropriate file type or format",
    "Authentication error",
    "Need authenticator",
    "Device power is off",
    "Device error",
    "Value too large to be stored in data type",
    "Bad executable (or shared library)",
    "Bad CPU type in executable",
    "Shared library version mismatch",
    "Malformed Mach-o file",
    "Operation canceled",
    "Identifier removed",
    "No message of desired type",
    "Illegal byte sequence",
    "Attribute not found",
    "Bad message",
    "EMULTIHOP (Reserved)",
    "No message available on STREAM",
    "ENOLINK (Reserved)",
    "No STREAM resources",
    "Not a STREAM",
    "Protocol error",
    "STREAM ioctl timeout",
    "Operation not supported on socket",
    "Policy not found",
    "State not recoverable",
    "Previous owner died",
    "Interface output queue is full",
  }

#endif

#ifdef __linux__
  char err_list[134][50] = {"Success",
                            "Operation not permitted",
                            "No such file or directory",
                            "No such process",
                            "Interrupted system call",
                            "Input/output error",
                            "No such device or address",
                            "Argument list too long",
                            "Exec format error",
                            "Bad file descriptor",
                            "No child processes",
                            "Resource temporarily unavailable",
                            "Cannot allocate memory",
                            "Permission denied",
                            "Bad address",
                            "Block device required",
                            "Device or resource busy",
                            "File exists",
                            "Invalid cross-device link",
                            "No such device",
                            "Not a directory",
                            "Is a directory",
                            "Invalid argument",
                            "Too many open files in system",
                            "Too many open files",
                            "Inappropriate ioctl for device",
                            "Text file busy",
                            "File too large",
                            "No space left on device",
                            "Illegal seek",
                            "Read-only file system",
                            "Too many links",
                            "Broken pipe",
                            "Numerical argument out of domain",
                            "Numerical result out of range",
                            "Resource deadlock avoided",
                            "File name too long",
                            "No locks available",
                            "Function not implemented",
                            "Directory not empty",
                            "Too many levels of symbolic links",
                            "Unknown error 41",
                            "No message of desired type",
                            "Identifier removed",
                            "Channel number out of range",
                            "Level 2 not synchronized",
                            "Level 3 halted",
                            "Level 3 reset",
                            "Link number out of range",
                            "Protocol driver not attached",
                            "No CSI structure available",
                            "Level 2 halted",
                            "Invalid exchange",
                            "Invalid request descriptor",
                            "Exchange full",
                            "No anode",
                            "Invalid request code",
                            "Invalid slot",
                            "Unknown error 58",
                            "Bad font file format",
                            "Device not a stream",
                            "No data available",
                            "Timer expired",
                            "Out of streams resources",
                            "Machine is not on the network",
                            "Package not installed",
                            "Object is remote",
                            "Link has been severed",
                            "Advertise error",
                            "Srmount error",
                            "Communication error on send",
                            "Protocol error",
                            "Multihop attempted",
                            "RFS specific error",
                            "Bad message",
                            "Value too large for defined data type",
                            "Name not unique on network",
                            "File descriptor in bad state",
                            "Remote address changed",
                            "Can not access a needed shared library",
                            "Accessing a corrupted shared library",
                            ".lib section in a.out corrupted",
                            "Attempting to link in too many shared libraries",
                            "Cannot exec a shared library directly",
                            "Invalid or incomplete multibyte or wide character",
                            "Interrupted system call should be restarted",
                            "Streams pipe error",
                            "Too many users",
                            "Socket operation on non-socket",
                            "Destination address required",
                            "Message too long",
                            "Protocol wrong type for socket",
                            "Protocol not available",
                            "Protocol not supported",
                            "Socket type not supported",
                            "Operation not supported",
                            "Protocol family not supported",
                            "Address family not supported by protocol",
                            "Address already in use",
                            "Cannot assign requested address",
                            "Network is down",
                            "Network is unreachable",
                            "Network dropped connection on reset",
                            "Software caused connection abort",
                            "Connection reset by peer",
                            "No buffer space available",
                            "Transport endpoint is already connected",
                            "Transport endpoint is not connected",
                            "Cannot send after transport endpoint shutdown",
                            "Too many references: cannot splice",
                            "Connection timed out",
                            "Connection refused",
                            "Host is down",
                            "No route to host",
                            "Operation already in progress",
                            "Operation now in progress",
                            "Stale file handle",
                            "Structure needs cleaning",
                            "Not a XENIX named type file",
                            "No XENIX semaphores available",
                            "Is a named type file",
                            "Remote I/O error",
                            "Disk quota exceeded",
                            "No medium found",
                            "Wrong medium type",
                            "Operation canceled",
                            "Required key not available",
                            "Key has expired",
                            "Key has been revoked",
                            "Key was rejected by service",
                            "Owner died",
                            "State not recoverable",
                            "Operation not possible due to RF-kill",
                            "Memory page has hardware error"};

#endif

  static char message[64];

#ifdef _APPLE__
  if (errnum < 0 || errnum > 106) {
    sprintf(message, "Unknown error: %d", errnum);  // change
  } else {
    sprintf(message, "%s", err_list[errnum]);  // change
  }
#elif __linux__
  if (errnum < 0 || errnum > 133) {
    sprintf(message, "Unknown error %d", errnum);  // change
  } else {
    sprintf(message, "%s", err_list[errnum]);  // change
  }

#endif

  return message;
}