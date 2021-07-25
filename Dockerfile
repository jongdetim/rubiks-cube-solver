#
#	Docker file for rubik
#

FROM debian

# RUN apk --update add build-base bash sqlite-dev
RUN apt update ; apt upgrade ; apt install -y build-essential libsqlite3-dev
ADD . /rubik

# CMD ["/bin/bash"]
