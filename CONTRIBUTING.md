# How To Write And Make Changes

## 1 Code standard

- We are using snake_case for all names (variables, classes, functions, ...)
- All code that You write should be covered by UTs. We are using TDD. Test are written in gtest, for mocking we are using fakeit.

## 2 Making changes in code

All updates should be done on dedicated branch, so please don't use master for changes (by the way master is blocked for not administrator users :) ). After cloning repository create Your branch and switch to it. After Your changes are ready You can push them.

## 3 Writing UTs

We prefer TDD (https://en.wikipedia.org/wiki/Test-driven_development), so You should cover code as much as possible by UTs.

To write tests we are using gtest library (https://github.com/google/googletest)

For mocking classes we are using FakeIt (https://github.com/eranpeer/FakeIt)

## 4 Recompiling

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

If there are changes in cmake files, then cmake automatically regenerate make files before compilation.

## 5 CI and reviews

Pushing Your changes won't apply them on master. Before it there are some steps that must success:
- creating pull request (You should do this only once after first push of Your branch).
- compilation for linux. It is done automatically by Travis after each push for Your branch.
- compilation for windows. It is done automatically by AppVeyor after each push for Your branch.
- all UTs should pass. UTs run is checked after each push for Your branch.
- closed code review.

If Your changes will pass all that steps then they will be merged to master. You can start to work on next task :)

### 5.1 Creating pull request

After pushing changes go to Bomberman's github page and select Your repository. In riught top corner You should find green button "Create pull request"

### 5.2 Compilation for linux

Compilation for linux is done automatically by Travis (using gcc compiler). After pushing new changes Travis will take code with Your changes and run compilation. To check compilation status go to "Pull requests" tab on github and click on Your pull request.
On bottom of the site You will see continuous-integration/travis-ci/pr  and continuous-integration/travis-ci/push. If You click on details You will get output from Travis.

Be aware that Travis compiles all targets and then run ctest, so even if compilation will pass Travis job may fail due to broken tests.

### 5.3 Compilation for windows

Compilation for windows is done automatically by AppVeyor. After pushing new changes AppVeyor will take code with Your changes and run compilation. To check compilation status go to "Pull requests" tab on github and click on Your pull request.
On bottom of the site You will see continuous-integration/appveyor/pr  and continuous-integration/appveyor/branch. If You click on details You will get output from AppVeyor.

Be aware that AppVeyor compiles all targets and then run ctest, so even if compilation will pass AppVeyor job may fail due to broken tests.

### 5.4 All UTs should pass

As mentioned above UTs are run automatically by Travis and AppVeyor when they are check Your changes. If even one test won't pass then all job is treated as broken.

### 5.5 Closed code review

There should be at least one ship it to close review. If someone start new thread in review, then that person should give You ship it. If all persons involved in review give You "Ship it" You can close review and merge Your branch to master.

## 6 Merging branch to master

... #ToDo (this will be added just after my branch will be merged)
