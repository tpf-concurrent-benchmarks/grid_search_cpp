FROM rikorose/gcc-cmake:latest

WORKDIR /app

COPY . /app/

RUN cmake . -DAMQP-CPP_LINUX_TCP=ON
RUN cmake --build .
ENTRYPOINT ["/bin/sh"]