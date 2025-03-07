# Cannot compile due missing headers
- <sys/sysctl.h>
- <mach/mach.h>

## Test Machine
I'm using a linux distribution to compile/run your program Ubuntu 14.04.2

## Compilation Error
```
➜  first-challenge-equipo-1 git:(main) ✗ g++ -std=c++17 -o challenge challenge.cpp
challenge.cpp:1:10: fatal error: sys/sysctl.h: No such file or directory
    1 | #include <sys/sysctl.h>
      |          ^~~~~~~~~~~~~~
compilation terminated.
```

## Another compilation error (2025-03-06)

```
challenge.cpp: In function ‘int main()’:
challenge.cpp:104:18: error: ‘sort’ is not a member of ‘std’; did you mean ‘qsort’?
  104 |             std::sort(palabras.begin(),palabras.end());
      |                  ^~~~
      |                  qsort
challenge.cpp: In function ‘int main()’:
challenge.cpp:104:18: error: ‘sort’ is not a member of ‘std’; did you mean ‘qsort’?
  104 |             std::sort(palabras.begin(),palabras.end());
      |                  ^~~~
      |                  qsort
challenge.cpp:121:14: error: ‘sort’ is not a member of ‘std’; did you mean ‘qsort’?
  121 |         std::sort(palabras.begin(),palabras.end());
      |              ^~~~
      |              qsort
challenge.cpp:121:14: error: ‘sort’ is not a member of ‘std’; did you mean ‘qsort’?
  121 |         std::sort(palabras.begin(),palabras.end());
      |              ^~~~
      |              qsort
```