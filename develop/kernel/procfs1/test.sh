
#!/usr/bin/env bash
sudo insmod procfs1.ko
sudo dmesg -t
cat /proc/helloworld
sudo rmmod procfs1
sudo dmesg -t
sudo dmesg -C
