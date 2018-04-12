# ![icon](icon/swan64.png) Swan

A set of C++ modules that provide some high-level features not available in the C++ Standard Library.

## Features

Swan contains the following modules:

* **dir**: Directory manipulation. It can list dir contents, change the active directory, and create and delete directories *(the functionality of this module is now part of the standard on `std::filesystem`)*.
* **file**: Reading and writing of binary files. It can also get file properties like size and type *(this module is mostly an alternative to `std::ifstream` and `std::ofstream`; the additional features are now on `std::filesystem`)*.
* **platform**: For accesing some platform features, like getting the name, launching a program, etc.
* **sharedlib**: Access to dynamically linked libraries.
* **strmanip**: Several string manipulation functions that require several statements in STL. For example, reading a text file into a string (or saving a string to a file), converting a string to a number, splitting a string with a separator token...
* **time**: Time related functions *(the functionality of this module is now part of the standard on `std::chrono`)*.

## Usage

Each of the modules is a self contained file that can be included in your project, by copying the file directly or by adding Swan to your include paths.

Every module is contained within the `swan` namespace.

Please check the **examples** folder for help on how to use the modules.

Icons made by [Freepic](http://www.freepik.com) from [www.flaticon.com](https://www.flaticon.com/) is licensed by [Creative Commons BY 3.0](http://creativecommons.org/licenses/by/3.0/).
