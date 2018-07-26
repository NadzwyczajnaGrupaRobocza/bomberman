# bomberman
[![Build Status](https://travis-ci.org/NadzwyczajnaGrupaRobocza/bomberman.svg?branch=master)](https://travis-ci.org/NadzwyczajnaGrupaRobocza/bomberman)[![Build status](https://ci.appveyor.com/api/projects/status/60vqqan3qtj4eu35/branch/master?svg=true)](https://ci.appveyor.com/project/Abergard/bomberman/branch/master)[![codecov](https://codecov.io/gh/NadzwyczajnaGrupaRobocza/bomberman/branch/master/graph/badge.svg)](https://codecov.io/gh/NadzwyczajnaGrupaRobocza/bomberman)

1. How To Start
===============

1.1 Requirments
---------------
Beside of code You also need to install:
- git
- cmake
- boost
- sfml (we are using version 2.5)

1.2 Downloading and compiling code
----------------------------------
The easiest way to get code is using git:
```sh
git clone https://github.com/NadzwyczajnaGrupaRobocza/bomberman.git
```

To get all external dependencies please run (this should be done only once for new repository):
```sh
git submodule init
git submodule update
```
When You have all dependencies You are ready to compile code. Go to bomberman directory:
```sh
cd bomberman
```
Inside it create new directory (there will be placed files created during compilation):
```sh
mkdir build
```

Go to this new dir:
```sh
cd build
```

Inside please run cmake:
```sh
cmake ..
```

After cmake finish creating files You can run compilation:
```sh
make target
```

1.3 Recompiling
------------------
Please remember, that Cmake create make files, that tell, how to compile Your code, so If You change anything in file structure or You add new dependencies, then probably You should also update cmake files.

If You want to recompile Your code, You should simply run make command:
```sh
make target
```
If there are changes in cmake files, then cmake automaticly regenerate them before recompilation.

2. How To Write
===============

2.1 Code Standard
-----------------
- We are using snake_case for all names (variables, classes, functions, ...)
- All code that You write should be covered by UTs. We are using TDD. Test are written in gtest, for mocking we are using fakeit.

2.2 Making changes in code
-------------------------------------------
All updates should be done on dedicated branch, so please don't use master for changes. After cloning repository create Your branch and switch to it. After Your changes are ready You can push them.

2.4 CI and reviews
------------------
Pushing Your changes won't apply them on master. Before it there are some steps that must success:
- compilation for linux. It is done automaticly after push by Travis
- compilation for windows. It is done automaticly after push by AppVeyor
- UT's run. All UTs should pass. Please remember that You should cover as much code as You can.
- Code review.

If Your changes will pass all that steps then they will be merged to master. You can start to work on next task :)

