FROM gcc:9.2 AS base

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && apt-get install -y cmake sudo

RUN git clone https://github.com/google/googletest.git

RUN cd googletest && mkdir build && cd build && cmake .. && make && sudo make install
RUN ls /usr/local/include
RUN pkg-config --libs --cflags gtest

WORKDIR /usr/code

COPY . .

RUN cd deps && mkdir lib && make lib/libindexer.a

RUN cp deps/lib/libindexer.a ./lib/libindexer.a

RUN make build/runTests

CMD ["build/runTests"]