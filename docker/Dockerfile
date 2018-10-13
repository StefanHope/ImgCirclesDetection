FROM phusion/baseimage:0.10.0

# Use baseimage-docker's init system.
CMD ["/sbin/my_init"]

RUN add-apt-repository ppa:beineri/opt-qt-5.10.1-xenial

RUN apt-get update \
      && apt-get install -y --no-install-recommends \
      build-essential \
      cmake \
      libopencv-dev \
      libgtest-dev \
      google-mock \
      libgoogle-glog-dev

RUN cd /usr/src/gtest && cmake . && make && mv /usr/src/gtest/*.a /usr/lib/
RUN cd /usr/src/gmock && cmake . && make && mv /usr/src/gmock/*.a /usr/lib/

# Clean up APT when done.
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*
