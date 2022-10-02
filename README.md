libAeon
==============

[![Build Status](https://ci.aeons.dev/api/badges/aeon-engine-private/libaeon/status.svg?ref=refs/heads/master)](https://git.aeons.dev/aeon-engine/libaeon)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/00148aa1097f467b93ebcb4262a8fcf1)](https://www.codacy.com/gh/aeon-engine/libaeon/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=aeon-engine/libaeon&amp;utm_campaign=Badge_Grade)
[![CodeFactor](https://www.codefactor.io/repository/github/aeon-engine/libaeon/badge)](https://www.codefactor.io/repository/github/aeon-engine/libaeon)

A general purpose C++20 support library.

How to build
--------------
### Conan
You must first install Conan. libAeon will pull in packages from both conan center and a private repository.

The following remote must be added:
https://artifactory.aeons.dev/artifactory/api/conan/aeon

### Windows (Visual Studio 2022)

libAeon is tested on the most recent version of Visual Studio 2022. It is best to just install the latest stable version when building.

1.  Make sure you have cloned the submodules

    ```git submodule update --init```

2.  Run `bootstrap.cmd`

    This will download all dependencies and generate the Visual Studio solution and project files in the `build` subfolder.

3.  Load the solution in Visual Studio and build

### Linux

libAeon requires at least GCC 12

1.  Make sure you have cloned the submodules

    ```git submodule update --init```

2.  Run `./bootstrap.sh`

    This will download all dependencies and generate a Makefile in the `build` subfolder.

3.  Enter the `build` folder and run make


### Other platforms

libAeon has also been successfully tested on other platforms like BSD and macOS. As long as you use a recent compiler this should work.
However there are no prebuilt dependencies available for these platforms. You can try using `./bootstrap_local.sh`. This will try to use
dependencies that are installed on the system already instead of downloading prebuilt ones. If you have any questions about this feel
free to contact me. I will try to do my best to help, but I can't guarantee anything.

License
--------------
The Aeon Library is released under the 2-Clause BSD license.

Copyright 2012-2022 Robin Degen

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
   disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
   disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Code style
--------------
A detailed description of code style is yet to be written. Please follow the 
style as established in the existing code. When in doubt, ask Robin Degen.

In short:

-   Prefer C++20 standards above any other library
-   4 spaces, no tabs.
-   No CamelCase. Variables and types must be named_like_this.
-   120 character maximum line length.
-   No compiler or static analysis warnings. Ever.
-   Use the SOLID principles. [Free your functions](https://www.youtube.com/watch?v=WLDT1lDOsb4).
