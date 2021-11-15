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

## Source code for GPU solver
- [src/bdd_cuda_base.cu: ](src/bdd_cuda_base.cu) contains code for setting up the GPU solver. This code performs conversion of CPU BDD representation to GPU and also provides functions to compute lower bounds, all min marginals etc.
- [src/bdd_cuda_parallel_mma.cu:](src/bdd_cuda_parallel_mma.cu) contains code for parallel deferred min-marginal averaging solver.
- [src/incremental_mm_agreement_rounding_cuda.cu](src/incremental_mm_agreement_rounding_cuda.cu) contains code for primal rounding. 
