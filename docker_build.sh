#!/bin/sh

set -eu

IMAGE_NAME="rubik_build_env"
CONTAINER_NAME="rubik_env"

if [ "${1:-}" == "-c" ]; then
    docker stop "${CONTAINER_NAME}"
    docker rm "${CONTAINER_NAME}"
    docker image rm "${IMAGE_NAME}"
fi

if ! docker inspect ${IMAGE_NAME} >> /dev/null; then
	echo "Creating ${IMAGE_NAME}"
    docker build \
           --rm \
           --tag="${IMAGE_NAME}" \
           "."
fi

if ! docker inspect ${CONTAINER_NAME} >> /dev/null; then
	echo "Creating ${CONTAINER_NAME}"
    docker run \
           --detach \
           -it \
           --name="${CONTAINER_NAME}" \
           --privileged \
           --volume="$(pwd):/workdir" \
           --workdir="/workdir" \
           "${IMAGE_NAME}" \
            sh
else
    docker start "${CONTAINER_NAME}"
fi

exit 0
