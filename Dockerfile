FROM debian:bullseye

# 更新 apt 源
ADD source.list source.list
RUN mv source.list /etc/apt/sources.list

# 安装依赖
RUN apt-get -y update
RUN apt-get install -fy --fix-missing git build-essential gdb-multiarch qemu-system-misc gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu

RUN apt-get -y install zsh python3
RUN ln -s /usr/bin/python3 /usr/bin/python
CMD ["zsh"]