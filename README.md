libAeon
==============

[![VS2019 Build Status](https://dev.azure.com/robindegen/aeon/_apis/build/status/libAeon%20(VS2019)?branchName=master&jobName=VS2019)](https://dev.azure.com/robindegen/aeon/_build/latest?definitionId=1&branchName=master)
[![Linux GCC8 Build Status](https://dev.azure.com/robindegen/aeon/_apis/build/status/libAeon%20(Linux%20GCC8)?branchName=master&jobName=Job)](https://dev.azure.com/robindegen/aeon/_build/latest?definitionId=4&branchName=master)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/4bf88c4e390b4413b604684990be9112)](https://www.codacy.com/app/robindegen/libaeon?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=aeon-engine/libaeon&amp;utm_campaign=Badge_Grade)
[![CodeFactor](https://www.codefactor.io/repository/github/aeon-engine/libaeon/badge)](https://www.codefactor.io/repository/github/aeon-engine/libaeon)

A general purpose C++17 support library.

License
--------------
The Aeon Library is released under the MIT license.

Copyright (c) 2012-2019 Robin Degen

 Permission is hereby granted, free of charge, to any person
 obtaining a copy of this software and associated documentation
 files (the "Software"), to deal in the Software without
 restriction, including without limitation the rights to use,
 copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following
 conditions:

 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.

Code style
--------------
A detailed description of code style is yet to be written. Please follow the 
style as established in the existing code. When in doubt, ask Robin Degen.

In short:

-   Prefer C++17 standards above boost or any other library
-   4 spaces, no tabs.
-   No CamelCase. Variables and types must be named_like_this.
-   120 character maximum line length.
-   No compiler or static analysis warnings. Ever.
-   Use the SOLID principles. [Free your functions](https://www.youtube.com/watch?v=WLDT1lDOsb4).
