#
#	Docker file for rubik
#

FROM ubuntu:latest

RUN apt-get -y update
RUN apt-get -y upgrade
RUN apt-get install -y sqlite3 libsqlite3-dev g++ build-essential
ENTRYPOINT [ "" ]
