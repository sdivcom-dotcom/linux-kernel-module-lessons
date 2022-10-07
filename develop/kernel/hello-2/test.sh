#!/usr/bin/env bash
sudo dmesg -C
sudo insmod hello-2.ko
sudo rmmod hello-2.ko
dmesg
