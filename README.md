_______________________________________________________________________________
# utl

Utility C++ Library

**utl** is a modular header-only library that provides common utility classes and functions released under MIT license. See [3rdparty](https://github.com/lucas137/utl/tree/master/3rdparty) for optional dependency licenses.

### Directory structure
- `3rdparty .......` 3rd party dependency information
- `cb .............` Code::Blocks project and workspace
    - `doxygen ....` Doxygen configuration
- `doc ............` library documentation
- `test ...........` unit tests
    - `cb .........` unit test Code::Blocks projects
    - `src ........` unit test source code
- `utl ............` library source code

### How to use this library

Include a module header to access the respective set of classes and/or functions in the `utl` namespace. Example:
```cpp
#include <utl/string>

std::string s = "01:02:03";     // string to be parsed
auto v = utl::parse(s, ":");    // returns a std::vector<std::string>
```

### 3rd party dependencies

Included in source code:
- JSON for Modern C++ -- https://github.com/nlohmann/json

Optional dependencies not included:
- Asio -- https://think-async.com/
- FLTK -- https://www.fltk.org/
- OpenCV -- https://opencv.org/

_______________________________________________________________________________
