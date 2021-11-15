# FADOP
An integer linear program solver using a Lagrange decomposition into binary decision diagrams on GPUs. Lagrange multipliers are updated through dual block coordinate ascent.

## Requirements
Developed and tested on CUDA 11.2.

## Installation

`git clone https://github.com/LPMP/BDD`

`git submodule update --remote --recursive --init`

Then continue with creating a build folder and use cmake:

`mkdir build && cd build && cmake ..`

## Running
In the build folder execute:


    cd src
    ./bdd_solver_cl -i <PATH_TO_LP> -s mma_cuda --incremental_primal --incremental_initial_perturbation 1.0 --incremental_perturbation_growth_rate 1.2
