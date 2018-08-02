FROM gcc:8.1 as BUILD
RUN apt-get update -y && \
    apt-get install -y cmake libsfml-dev libboost-all-dev

WORKDIR /app
ADD external external
ADD src src
ADD cmake cmake 
COPY CMakeLists.txt .

RUN mkdir build && cd build && cmake .. && make -j $(nproc)

FROM ubuntu:18.04 as RUN
RUN apt-get update -y && \
    apt-get install -y libsfml-dev libboost-all-dev

WORKDIR /artifacts
COPY --from=BUILD /app/build/bin/* ./
CMD ["./Bomberman"]