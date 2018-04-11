# ![icon](icon/swan64.png) Swan

A set of C++ classes that provide some high-level features not available in the C++ Standard Library that integrate well with it.

NOTE: Some of the functionality available here has been added in recent revisions of the C++ standard, so some features might be removed from the library.

## Features

Swan contains the following modules:

* **dir**: Directory manipulation. It can list dir contents, change the active directory, and create and delete directories *(this module might be removed in favor of `std::filesystem`)*.
* **file**: Reading and writing of binary files. It can also get file properties like size and type *(this module might be removed in favor of `std::filesystem`, `std::ifstream` and `std::ofstream`)*.
* **sharedlib**: For manipulating dynamically linked libraries.
* **str**: Several string-related functions that require several statements in STL. For example, reading a text file into a string (or saving a string to a file), converting a string to a number, splitting a string with a separator token...
* **sys**: For accesing some system features, like getting the platform name, launching a program, etc.
* **time**: Time related functions *(this module might be removed in favor of `std::chrono`)*.

## Usage

Each of the modules is a self contained file that can be included in your project, by copying the file directly or by adding Swan to your include paths.

Every module is contained within the `swan` namespace.

Icons made by [Freepic](http://www.freepik.com) from [www.flaticon.com](https://www.flaticon.com/) is licensed by [Creative Commons BY 3.0](http://creativecommons.org/licenses/by/3.0/).
