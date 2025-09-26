FROM ubuntu:latest
RUN apt-get update && apt-get install -y git\
    cmake \
    make \
    g++ \
    vim
RUN git clone -b develop https://github.com/Terps489/ISE_Lab1.git /app || \
    (cd /app && git switch develop && git pull origin develop)
WORKDIR /app