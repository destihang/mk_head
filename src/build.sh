#!/bin/bash
make clean
make
cp user_data.bin boot_data.bin produce_16M_data ../in/
cd ../in/
./produce_16M_data
rm user_data.bin boot_data.bin produce_16M_data
