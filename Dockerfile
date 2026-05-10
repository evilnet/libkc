FROM debian:13 AS build
RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential autoconf automake libtool pkg-config \
        libssl-dev libcurl4-openssl-dev libjansson-dev && \
    rm -rf /var/lib/apt/lists/*
COPY . /src
WORKDIR /src
RUN autoreconf -fi && \
    ./configure --prefix=/usr && \
    make -j"$(nproc)" && \
    make DESTDIR=/out install

FROM scratch
COPY --from=build /out/ /
