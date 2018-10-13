MKFILE_DIR := $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
MNT_DIR := $(abspath $(MKFILE_DIR)../)

# Main docker image name
DOCKER_IMG         = imgcirclesdetection-build:0.1

# Where to mount the base of the repository in the container
DOCKER_MOUNT_POINT = /ImgCirclesDetection/

# Set up source code volume mount
DOCKER_VOLUME_MOUNT = -v $(MNT_DIR):$(DOCKER_MOUNT_POINT)

# Working directories
WORKING_DIRECTORY = /ImgCirclesDetection/docker 
DOCKER_WD = /ImgCirclesDetection/docker

# Set up final docker commands
DOCKER = docker run --rm -it $(DOCKER_VOLUME_MOUNT) -w $(WORKING_DIRECTORY) $(DOCKER_IMG)

build:
	$(eval WORKING_DIRECTORY = $(DOCKER_WD))
	$(DOCKER) ./make.sh
#	$(DOCKER) /ImgCirclesDetection/src/docker/make.sh

image:
	docker build . -t $(DOCKER_IMG)
