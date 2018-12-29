# Clean Editor - Sample code editor using Qt Qml/Quick and Widgets

<center>
  <img src="screencapture.png?raw=true" width="600">
</center>

## Description

Sample project that demonstrates how to structure a Qt example with two front-ends sharing the same back-end. The two front-ends use different Qt technologies: Qt Widgets as well as Qt Quick/QML. Currently only the QML front-end has been implemented. 

The project is a simple code editor, where it's possible to open and edit files.

Further details of the project can be found on my blog www.cleanqt.io, where it's thoroughly covered in the [Crash Course for C++ developers series](https://www.cleanqt.io/blog/crash-course-in-qt-for-c%2B%2B-developers,-part-6).

## Building

These are the instructions on how to build the sample application using the CMake buildsystem generator.

The project requires:
* `CMake version >= 3.8.2`
* `Qt version >= 5.11` with `Core`, `Gui`, `Qml`, `Quick`, `QuickControls2` enabled.

### Instructions 

1. From the root directory of the checkout, create a build directory and change into it:

```
mkdir build
cd build
```

2. Generate the desired project by using `cmake`. Specify the generator with the `-G` option. See `cmake --help` for more information.

```
cmake -DCMAKE_BUILD_TYPE=Debug .. # For debug
cmake -DCMAKE_BUILD_TYPE=Release .. # For release
```

3. Build by running either of the following commands:
```
make    # Unix,
nmake   # Windows
```

Alternatively, if you're using Qt Creator, just open up the `CMakeLists.txt` in the root directory.