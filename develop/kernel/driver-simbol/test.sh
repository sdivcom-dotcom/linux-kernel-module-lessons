#!/usr/bin/env bash
sudo insmod hello-4.ko
sudo dmesg -t
sudo rmmod hello-4
sudo dmesg -t
sudo dmesg -C
