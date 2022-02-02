### data race
The Thread Analyzer detects data-races that occur during the execution of a multi-threaded process. A data race occurs when:

- two or more threads in a single process access the same memory location concurrently, and
- at least one of the accesses is for writing, and
- the threads are not using any exclusive locks to control their accesses to that memory.

### race condition

A race condition or race hazard is the condition of an electronics, software, or other system 
where the system's substantive behavior is dependent on the sequence or timing of other uncontrollable events. 
It becomes a bug when one or more of the possible behaviors is undesirable.

- A race condition arises in software when a computer program, to operate properly, depends on the sequence or timing of the program's processes or threads. 
- Critical race conditions cause invalid execution and software bugs. 
- Critical race conditions often happen when the processes or threads depend on some shared state. Operations upon shared states are done in critical sections that must be mutually exclusive. Failure to obey this rule can corrupt the shared state.

从定义中我们可以确定，data race的定义是非常明确的，而race condition则没有明确的细节定义，只是给出一般性指导原则，即保护对于共享状态的访问,否则可能出现race condtion.
实际的代码里可以看出来，```unsafe_transfer```不存在data race，但是存在race condition，此时我们不仅保护了共享状态的访问，还给出了类似于事务的控制，这完全是根据程序语义而定
