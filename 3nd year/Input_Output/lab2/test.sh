#!/bin/bash

function mount_disks() {
    echo "Mounting disks"

    mkfs.ext4 -v /dev/mydisk1
    mkfs.ext4 -v /dev/mydisk5
    mkfs.ext4 -v /dev/mydisk6

    mkdir -p /mnt/mydisk1
    mkdir -p /mnt/mydisk5
    mkdir -p /mnt/mydisk6

    sudo mount /dev/mydisk1 /mnt/mydisk1
    sudo mount /dev/mydisk5 /mnt/mydisk5
    sudo mount /dev/mydisk6 /mnt/mydisk6
}

function copy_from_virtual_to_virtual() {
    copy_random_to_disk

    echo "Testing speed of copying files between parts of virtual disk"

    pv /mnt/mydisk1/file > /mnt/mydisk5/file
    pv /mnt/mydisk5/file > /mnt/mydisk6/file
    pv /mnt/mydisk6/file > /mnt/mydisk1/file

    delete_files
}

function copy_between_virtual_and_real() {
    copy_random_to_disk
    mkdir test

    echo "Testing speed of copying files from virtual to real disk"

    pv /mnt/mydisk1/file > test/1
    pv /mnt/mydisk5/file > test/5
    pv /mnt/mydisk6/file > test/6

    delete_files

    echo "Testing speed of copying files from real to virtual disk"

    pv test/1 > /mnt/mydisk1/file
    pv test/5 > /mnt/mydisk5/file
    pv test/6 > /mnt/mydisk6/file

    delete_files
    rmdir test
}

function copy_random_to_disk() {
    echo "Filling files on virtual disks with random information"

    dd if=/dev/urandom of=/mnt/mydisk1/file bs=7M count=1
    dd if=/dev/urandom of=/mnt/mydisk5/file bs=7M count=1
    dd if=/dev/urandom of=/mnt/mydisk6/file bs=7M count=1
}

function delete_files() {
    echo "Deleting test files"

    rm /mnt/mydisk1/file
    rm /mnt/mydisk5/file
    rm /mnt/mydisk6/file
}

function unmount_disks() {
    echo "Unmounting disks"

    umount /mnt/mydisk1
    umount /mnt/mydisk5
    umount /mnt/mydisk6

    rmdir /mnt/mydisk1
    rmdir /mnt/mydisk5
    rmdir /mnt/mydisk6
}

mount_disks
copy_from_virtual_to_virtual
copy_between_virtual_and_real
unmount_disks
