FROM ubuntu:18.04

MAINTAINER Robin Degen version: 1.0

RUN apt-get update && apt-get install -y clang cmake libmono-2.0-dev git

ENV CC clang
ENV CXX clang++

COPY . /libaeon

RUN cd /libaeon && ./bootstrap.sh
RUN cd /libaeon/build && make -j2
RUN cd /libaeon/build && ctest
