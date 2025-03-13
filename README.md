Scrambler demo application
==========================

Scramble a command-line argument using a hard-coded key.  Implemented in multiple languages.

Usage
-----

The argument `<plaintext>` must be a single alphanumeric string.  Lower case letters will automatically be converted to upper case.

* C++: `scrambler <plaintext>`
* Java: `java cs5150.Scrambler <plaintext>`
* Python: `python scrambler.py <plaintext>`

Building
--------

Try to get your IDE to build these projects.  If you prefer to work manually on the command line, here are some tips:

* C++: `make` (requires a C++14 compiler)
* Java: (source organization follows Maven conventions)

Testing
-------

Try to get your IDE to run the test suites for these projects.  If you prefer to work manually on the command line, here are some tips:

* C++: `make test` (requires Boost.Test header)
* Java: `java -jar junit-platform-console-standalone.jar -cp test/java:main/java --scan-classpath` (requires JUnit 5 Console Launcher)
* Python: `python -m unittest`
# scrambler
