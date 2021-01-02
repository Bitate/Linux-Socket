#!/bin/bash
echo "Enter directory name"
read new_dir
mkdir $new_dir
rm -r -i $new_dir
