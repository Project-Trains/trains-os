# Trains OS

![GitHub repo size](https://img.shields.io/github/repo-size/Project-Trains/trains-os)
![GitHub issues](https://img.shields.io/github/issues/Project-Trains/trains-os)
[![Readme Polski](https://img.shields.io/badge/README-Polski-blue)](https://github.com/Project-Trains/trains-os/blob/master/README.pl.md)

## Environment setup

If you are on a Windows 10 machine you need to setup WSL with a distro of your choosing. When you have WSL ready or you are on a Linux machine you should update your packages and install `build-essential` and `mtools`.
```
sudo apt-get install build-essential mtools
```
If you are on a Linux machine you should also install `qemu` using
```
sudo apt-get install qemu
```
however if you are on a Windows machine you can download QEMU from their website or use [this link](https://qemu.weilnetz.de/w64/2020/qemu-w64-setup-20200201.exe).

Then you can go to `gnu-efi` directory and run `make` command.

## Building

To build the project you need to go `gnu-efi` directory and run
```
make bootloader
```
then in `kernel` directory you need to run
```
make kernel
```
and finally
```
make buildimg
```
after that you can start QEMU using
```
make run
```
if you are using Linux or you can run `start.bat` if you are using Windows.