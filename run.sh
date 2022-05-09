#!/bin/bash
#SBATCH -A qgp
#SBATCH -p qgp
#SBATCH -t 01:00:00

./interpolate_ebsq eos.dat 
