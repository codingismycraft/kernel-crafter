# Vectored IO (scatterd / gathered IO)

Vectored IO is an IO method to read or write an array of buffers from a stream.

The advantages are efficiency, performance and atomicity

The main advantages are efficiency, performance and atomicity

```
ssize_t readv(int fd, const struct iovec *iov, int iovcnt);

ssize_t writev(int fd, const struct iovec *iov, int iovcnt);
```

The related struct to hold the buffers:
```
  struct iovec {
               void  *iov_base;    /* Starting address */
               size_t iov_len;     /* Number of bytes to transfer */
           };
```

## Return value

- On success returns the number of bytes read.

- On error -1 is returned and errno is set.

On success, readv() and writev() return the number of bytes read or written,
respectively. This number should be the sum of all count iov_len values.

## Errors

On error, the system calls return −1 and set errno as appropriate. 

In addition, the standards define two other error situations. 

#### EINVAL 
if the sum of all count iov_len values is greater than SSIZE_MAX, no data will
be transferred, −1 will be returned, and errno will be set to EINVAL.

#### EINVAL 

POSIX dictates that count must be larger than zero and less than or equal to
IOV_MAX, which is defined in <limits.h>. In Linux, IOV_MAX is currently 1024. If
count is 0, the system calls return 0.1 If count is greater than IOV_MAX, no
data is transferred, the calls return −1, and errno is set to EINVAL.

#### EOPNOTSUPP 

An unknown flag is specified in flags.
