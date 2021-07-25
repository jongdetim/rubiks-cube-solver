#
#	Docker file for rubik
#

FROM alpine

RUN apk --update add build-base bash sqlite-dev

ADD . /rubik

CMD ["/bin/bash"]
