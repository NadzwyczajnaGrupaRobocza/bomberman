# Building Bomberman using Dockerfile

## Prequsities 
You should have those installed in your system:
* Docker
* X server (i.e. _Xming_ for Windows)

## Build an image with all Bomberman's binaries
```
docker build -t bomberman/bomberman .
```

In case of changes to the source code, just run the same command again. Docker behaves somehow like Makefiles and rebuilds only stages that have changed.

## Run any binary in Docker
For a console binary, such as unit tests, you can run:
```
docker run --rm bomberman/bomberman ./BINARY_NAME
```

If it's a binary with GUI, you need to run X server and export DISPLAY variable with your local machine's IP address and X server display number. You can do that as following:
```
docker run --rm -e DISPLAY=YOUR_IP:DISPLAY_NUM bomberman/bomberman-dev ./BINARY_NAME
```

## Compiling with docker in a current directory
During development you would like to preserve _build_ directory so when recompiling, you won't rebuild the whole project again. To do that, you can use _Dockerfile.dev_:

Build the image:
```
docker build -t bomberman/bomberman-dev -f Dockerfile.dev .
```

Run an interactive shell inside the container with your current directory mount as _/app_:
```
docker run --rm -it -e DISPLAY=YOUR_IP:DISPLAY_NUM -v ${PWD}:/app bomberman/bomberman-dev
```