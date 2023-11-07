FROM rikorose/gcc-cmake:latest

WORKDIR /app

COPY . /app/

RUN cmake -DCMAKE_BUILD_TYPE=Release .
RUN cmake --build .
ENTRYPOINT ["/bin/sh"]