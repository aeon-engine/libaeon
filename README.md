libAeon
==============

[![VS2019 Build Status](https://dev.azure.com/robindegen/aeon/_apis/build/status/libAeon%20(VS2019)?branchName=master&jobName=VS2019)](https://dev.azure.com/robindegen/aeon/_build/latest?definitionId=1&branchName=master)
[![Linux GCC10 Build Status](https://dev.azure.com/robindegen/aeon/_apis/build/status/libAeon%20(Linux%20GCC8)?branchName=master&jobName=Job)](https://dev.azure.com/robindegen/aeon/_build/latest?definitionId=4&branchName=master)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/4bf88c4e390b4413b604684990be9112)](https://www.codacy.com/app/robindegen/libaeon?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=aeon-engine/libaeon&amp;utm_campaign=Badge_Grade)
[![CodeFactor](https://www.codefactor.io/repository/github/aeon-engine/libaeon/badge)](https://www.codefactor.io/repository/github/aeon-engine/libaeon)

A general purpose C++20 support library.

How to build
--------------
### Windows (Visual Studio 2019)

libAeon is tested on the most recent versions of Visual Studio 2019. It is best to just install the latest stable version when building.

1. Make sure you have cloned the submodules

   ```git submodule update --init```

2. Run `bootstrap.cmd`

   This will download all dependencies and generate the Visual Studio solution and project files in the `vs_build` subfolder.

3. Load the solution in Visual Studio and build

### Linux

libAeon requires at least GCC 9 but parts still may work on GCC 8 (Untested).

1. Make sure you have cloned the submodules

   ```git submodule update --init```

2. Run `./bootstrap.sh`

   This will download all dependencies and generate a Makefile in the `build` subfolder.

3. Enter the `build` folder and run make


### Other platforms

libAeon has also been successfully tested on other platforms like BSD and macOS. As long as you use a recent compiler this should work.
However there are no prebuilt dependencies available for these platforms. You can try using `./bootstrap_local.sh`. This will try to use
dependencies that are installed on the system already instead of downloading prebuilt ones. If you have any questions about this feel
free to contact me. I will try to do my best to help, but I can't guarantee anything.

License
--------------
The Aeon Library is released under the 2-Clause BSD license.

Copyright 2012-2020 Robin Degen

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

-   Prefer C++20 standards above boost or any other library
-   4 spaces, no tabs.
-   No CamelCase. Variables and types must be named_like_this.
-   120 character maximum line length.
-   No compiler or static analysis warnings. Ever.
-   Use the SOLID principles. [Free your functions](https://www.youtube.com/watch?v=WLDT1lDOsb4).
