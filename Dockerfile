FROM ubuntu:latest
WORKDIR /app
COPY . .
RUN apt-get update && apt-get install -y \
    cmake \
    make \
    g++
RUN cmake .