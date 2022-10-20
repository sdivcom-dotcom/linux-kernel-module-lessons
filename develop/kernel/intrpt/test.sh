
#!/usr/bin/env bash
sudo insmod intrpt.ko
sudo dmesg -t
sudo rmmod intrpt
sudo dmesg -t
sudo dmesg -C
