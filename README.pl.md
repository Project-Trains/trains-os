# Trains OS

![GitHub repo size](https://img.shields.io/github/repo-size/Project-Trains/trains-os)
![GitHub issues](https://img.shields.io/github/issues/Project-Trains/trains-os)
[![Readme English](https://img.shields.io/badge/README-English-blue)](https://github.com/Project-Trains/trains-os/blob/master/README.md)

## Konfiguracja środowiska

Jeśli korzystasz z komputera z systemem Windows 10, musisz skonfigurować WSL z wybraną dystrybucją Linuksa. Jeżeli masz już gotowy WSL lub jesteś na komputerze z Linuksem, powinieneś zaktualizować swoje pakiety i zainstalować `build-essential` oraz `mtools`.
```
sudo apt-get install build-essential mtools
```
Jeśli korzystasz z komputera z systemem Linux, powinieneś również zainstalować `qemu` za pomocą
```
sudo apt-get install qemu
```
jednak jeśli korzystasz z komputera z systemem Windows, możesz pobrać QEMU z ich witryny internetowej lub użyć [tego linku](https://qemu.weilnetz.de/w64/2020/qemu-w64-setup-20200201.exe).

Wtedy możesz przejść do folderu `gnu-efi` i wykonać komendę `make`.

## Budowanie

Aby zbudować projekt, musisz przejść do katalogu `gnu-efi` i uruchomić
```
make bootloader
```
następnie w katalogu `kernel` musisz uruchomić
```
make kernel
```
i w końcu
```
make buildimg
```
po tym możesz uruchomić QEMU za pomocą
```
make run
```
jeśli używasz Linuksa lub za pomocą `start.bat` jeśli używasz Windows.