#!/usr/bin/env bash
sudo insmod hello-3.ko mystring="bebop" myintarray=-1
sudo dmesg -t | tail -7
sudo rmmod hello-3
sudo dmesg -t | tail -1
sudo dmesg -C
 read -sn1 -p "Press any key to continue..."; echo
sudo insmod hello-3.ko mystring="supercalifragilisticexpialidocious"
sudo dmesg -t | tail -7
sudo rmmod hello-3
sudo dmesg -t | tail -1
sudo dmesg -C
 read -sn1 -p "Press any key to continue..."; echo
sudo insmod hello-3.ko mylong=hello
sudo rmmod hello-3
sudo dmesg -t | tail -1
sudo dmesg -C
