# bomberman
[![Build Status](https://travis-ci.org/NadzwyczajnaGrupaRobocza/bomberman.svg?branch=master)](https://travis-ci.org/NadzwyczajnaGrupaRobocza/bomberman)[![Build status](https://ci.appveyor.com/api/projects/status/60vqqan3qtj4eu35/branch/master?svg=true)](https://ci.appveyor.com/project/Abergard/bomberman/branch/master)[![codecov](https://codecov.io/gh/NadzwyczajnaGrupaRobocza/bomberman/branch/master/graph/badge.svg)](https://codecov.io/gh/NadzwyczajnaGrupaRobocza/bomberman)


# 1. How To Start

## 1.1 Requirments

Beside of code You also need to install:
- compilator that supports C++ 17
- git
- cmake
- boost
- sfml (we are using version 2.5)

## 1.2 Downloading and compiling code

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

# 1.3 Running code

It's time to run code. By default cmake will put binaries in directory:
```sh
<build_directory>\bin
```
To check if everything wokrs fine You may run:
simple-rectangle-draw (it should open window with white rectangle on black background)
simple-moving-rectangle (You should see some moving white rectangles)

# 2. How To Write And Make Changes

## 2.1 Code standard

- We are using snake_case for all names (variables, classes, functions, ...)
- All code that You write should be covered by UTs. We are using TDD. Test are written in gtest, for mocking we are using fakeit.

## 2.2 Making changes in code

All updates should be done on dedicated branch, so please don't use master for changes (by the way master is blocked for not administrator users :) ). After cloning repository create Your branch and switch to it. After Your changes are ready You can push them.

## 2.3 Writing UTs
...

## 2.4 Recompiling

Please remember, that Cmake create make files, that tell, how to compile Your code, so If You change anything in file structure or You add new dependencies, then probably You should also update cmake files.

If You want to recompile Your code, You should simply rerun make commands from previous subchapter.
For all targets:
```sh
cmake --build <build_directory>
```
For single target:
```sh
cmake --build <build_directory> --target <target>
```

If there are changes in cmake files, then cmake automaticly regenerate make files before compilation.

## 2.5 CI and reviews

Pushing Your changes won't apply them on master. Before it there are some steps that must success:
- creating pull request
- compilation for linux. It is done automaticly after push by Travis
- compilation for windows. It is done automaticly after push by AppVeyor
- all UTs should pass. Please remember that You should cover as much code as You can.
- closed code review.

If Your changes will pass all that steps then they will be merged to master. You can start to work on next task :)

### 2.5.1 Creating pull request
After pushing changes go to Bomberman's github page and select Your repository. In riught top corner You should find green button "Create pull request"

### 2.5.2 Compilation for linux
...

### 2.5.3 Compilation for windows
...

### 2.5.4 All UTs should pass
...

### 2.5.5 Closed code review
There should be at least one ship it to close review. If someone start new thread in review, then that person should give You ship it. If all persons involved in review give You "Ship it" You can close review and merge Your branch to master.

## 2.6 Merging branch to master
...

