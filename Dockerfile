FROM ubuntu:rolling

RUN apt-get update && apt-get install -y \
		binutils \
		build-essential \
		git \
		gcovr \
		libcmocka0 \
		libcmocka-dev \
        libsdl2-2.0-0 \
        libsdl2-dev \
        libsdl2-image-2.0-0 \
        libsdl2-image-dev \
        && rm -rf /var/lib/apt/lists/*
