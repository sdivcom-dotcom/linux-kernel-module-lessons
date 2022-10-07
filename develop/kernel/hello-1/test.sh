#!/usr/bin/env bash
sudo dmesg -C
sudo insmod hello-1.ko
sudo rmmod hello-1.ko
dmesg
