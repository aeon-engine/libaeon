FROM ubuntu:18.04

MAINTAINER Robin Degen version: 1.0

ENV DEBIAN_FRONTEND noninteractive
RUN apt-get update && apt-get install -y tzdata && ln -fs /usr/share/zoneinfo/Europe/Amsterdam /etc/localtime && dpkg-reconfigure --frontend noninteractive tzdata

RUN apt-get install -y clang cmake mono-devel git

ENV CC clang
ENV CXX clang++

COPY . /libaeon

RUN cd /libaeon && ./bootstrap.sh
RUN cd /libaeon/build && make -j2
RUN cd /libaeon/build && ctest
