## Personal Solution for MIT 6.828 course
---
[mit 6.828 course link](https://pdos.csail.mit.edu/6.828/2020/schedule.html)


#### Getting Started
---
* how to build docker image
```sh
docker build -t xv6 .
```

* run docker image(we need to mount xv6-labs-2020)
```sh
docker run -it -v {path to your xv6-labs-2020}/:/xv6-labs-2020 xv6
```