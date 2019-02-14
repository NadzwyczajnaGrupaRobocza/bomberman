# bomberman
[![Build Status](https://travis-ci.org/NadzwyczajnaGrupaRobocza/bomberman.svg?branch=master)](https://travis-ci.org/NadzwyczajnaGrupaRobocza/bomberman)[![Build status](https://ci.appveyor.com/api/projects/status/60vqqan3qtj4eu35/branch/master?svg=true)](https://ci.appveyor.com/project/Abergard/bomberman/branch/master)[![codecov](https://codecov.io/gh/NadzwyczajnaGrupaRobocza/bomberman/branch/master/graph/badge.svg)](https://codecov.io/gh/NadzwyczajnaGrupaRobocza/bomberman)


# How To Start

## 1 Requirements

Beside of code You also need to install:
- compiler that supports C++ 17
- git
- cmake
- boost dev version
- sfml dev version (at leeast 2.5)

## 2 Downloading and compiling code

The easiest way to get code is using git:
```sh
git clone https://github.com/NadzwyczajnaGrupaRobocza/bomberman.git
```

To get all external dependencies please run (this should be done only once for new repository):
```sh
git submodule init
git submodule update
```

You could also do this in simpler way:
```sh
git submodule update --init
```

Or download repository and init submodules in one step:
```sh
git clone --recurse-submodules -j <n> https://github.com/NadzwyczajnaGrupaRobocza/bomberman.git
```
where n is number of submodules cloned in parallel.

When You have code and all dependencies You are ready to compile. Go to bomberman directory:
```sh
cd bomberman
```

Inside it run cmake command, which create new directory and generate inside it files needed for compilation:
```sh
cmake . -B<build_directory>
```

After cmake finish creating files You can run compilation for all targets:
```sh
cmake --build <build_directory>
```

To compile specified target add --target flag:
```sh
cmake --build <build_directory> --target <target>
```

To  check available targets run command:
```sh
cmake --build <build_directory> --target help
```

# 3 Running code

It's time to run code. By default cmake will put binaries in directory:
```sh
<build_directory>\bin
```
To check if everything wokrs fine You may run:
simple-rectangle-draw (it should open window with white rectangle on black background)
simple-moving-rectangle (You should see some moving white rectangles)

# 4 Running UTs

Running UTs is very simple. If You look at available targets:
```sh
cmake --build <build_directory> --target help"
```
You will find all UT binaries (thay have postfix "-ut"). Just build binary You want:
```sh
cmake --build <build_directory> --target <ut_target>
```
and run it:
```sh
<build_directory>\bin\<ut_target>
```

You can also run UTs with cmake. In such case build UT for all targets
```sh
cmake --build <build_directory>
```
and inside <build_directory> run
```
ctest
```
If You want to run only specified tests You can use -R:
```sh
ctest -R <regex>
```
Ctest will run tests that matches <regex>.

For more ctest options run
```
ctest --help
```
