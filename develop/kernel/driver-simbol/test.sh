#!/usr/bin/env bash
sudo dmesg -C
sudo insmod chardev.ko
sudo dmesg -t
#sudo rmmod chardev
#sudo dmesg -t
#sudo dmesg -C
