##  Epoll: Efficient I/O Event Monitoring in Linux

Epoll is a powerful mechanism in Linux for efficiently monitoring multiple file
descriptors (FDs) for Input/Output (I/O) events. It overcomes the following
limitations of traditional methods like `poll` and `select`, particularly when
dealing with a large number of FDs:

* **Scaling Issues:**  `poll` and `select` require copying the entire FD list
  to the kernel for each call, which becomes expensive with a high number of
  FDs.  This copying process consumes processing power and memory.

* **Returns only affected descriptors:** epoll returns only the list of
  descriptors which triggered the events. No need to iterate through 10,000
  descriptors anymore to find that one which triggered the event!

* **Flexibiliy:** You can add sockets or remove them from monitoring anytime.

* **Allows for Edge Triggering**

* **Multi-threading capabilities:**  It is possible to have the multiple
  threads waiting on the same epoll queue with epoll_wait(), something you
  cannot do with select/poll.

## Epoll:

**Focus**
Epoll is an event-driven mechanism for monitoring multiple file descriptors (
FDs) for I/O (Input/Output) events. It excels at efficiently handling a large
number of FDs, making it ideal for applications dealing with many network
connections, file I/O operations, or other I/O-intensive tasks.

**Functionality**
Epoll doesn't directly perform I/O operations like reading or writing data.
Instead, it efficiently notifies the application when an FD is ready for I/O (
e.g., data is available to be read from a network socket).

**Use Case**
Epoll is typically used in conjunction with lower-level I/O operations like read
and write or higher-level abstractions like sockets. It provides an efficient
way to determine which FD is ready for I/O, allowing the application to handle
them selectively.

### How Epoll Solves the Problem

Epoll offers a more efficient and scalable approach for I/O event monitoring:

* **Interest List:** Applications register the FDs they're interested in with
  the epoll instance. This creates an "interest list" maintained within the
  kernel, eliminating the need to copy the entire FD list on every call.
* **Event Notification:**  The kernel efficiently tracks I/O events and only
  notifies the application when an event occurs on a registered FD. This reduces
  unnecessary system calls and context switching.
* **Non-Blocking:**  Epoll calls like `epoll_wait` are non-blocking. The
  application can continue processing other tasks while waiting for I/O events.

### Benefits of Epoll

* **Scalability:** Epoll handles large numbers of FDs efficiently, making it
  ideal for applications that deal with many network connections, file I/O
  operations, or other I/O-intensive tasks.
* **Performance:**  By minimizing system calls and context switching, epoll
  significantly improves performance compared to `poll` and `select`.
* **Concurrency:**  The non-blocking nature of epoll allows applications to
  remain responsive while waiting for I/O events.

## Edge vs Level Triggering

Edge triggering returns from the wait state ONCE as soon an event **occurs**
where level triggering will return for as long as data for the event will be
available to be read.

**File Descriptors (FDs):**

* FDs are low-level representations of open resources in Linux, like files,
  network sockets, pipes, or other I/O devices.
* Epoll monitors FDs for events, such as data being available to read (for
  network sockets or files) or the ability to write data without blocking (for
  output streams).

**Output Strings:**

* Output strings are data structures in your program that hold text information.
* They are not directly related to FDs.

**Epoll and Output Operations:**

* When using epoll with output streams, you wouldn't typically use an "output
  string" as an FD.
* Instead, you'd get an FD associated with the output stream (e.g., a network
  socket or a file) that you register with epoll.
* Epoll would then notify you when the FD is ready for writing, meaning the
  underlying buffer has enough space to accept your output string without
  blocking.

**How Epoll and Writing can Fail:**

While epoll helps determine when it's safe to write data, there can still be
situations where writing might not succeed:

* **Limited Buffer Space:**  Even if epoll indicates the FD is ready for
  writing, there might not be enough space in the underlying buffer (e.g.,
  network socket) to accommodate your entire output string. The write operation
  could fail, requiring you to handle the error and potentially retry.
* **Network Issues:**  For network sockets, even if epoll signals readiness,
  there might be network congestion or other issues preventing successful data
  transmission. You might need to implement error handling and retry mechanisms
  in such scenarios.
* **Disk Errors:**  When writing to a file, disk errors or permission issues
  could cause the write operation to fail, even if epoll indicated readiness.
  Proper error handling is crucial in these cases.

**In summary:**

* Epoll doesn't directly deal with output strings, but with file descriptors
  associated with output streams (like sockets or files).
* Epoll helps determine when it's safe to write to an FD without blocking, but
  writing can still fail due to buffer limitations, network issues, or disk
  errors.
