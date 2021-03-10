set OS_NAME=TrainsOS
set BUILD_DIR=%0/../bin
set OVMF_DIR=%0/../../ovmf-x64

qemu-system-x86_64 -drive file=%BUILD_DIR%/%OS_NAME%.img -m 256M -cpu qemu64 -drive if=pflash,format=raw,unit=0,file="%OVMF_DIR%/OVMF_CODE-pure-efi.fd",readonly=on -drive if=pflash,format=raw,unit=1,file="%OVMF_DIR%/OVMF_VARS-pure-efi.fd" -net none
pause
