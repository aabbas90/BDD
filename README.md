# FADOP
An integer linear program solver using a Lagrange decomposition into binary decision diagrams on GPUs. Lagrange multipliers are updated through dual block coordinate ascent.

## Source code for GPU solver
- [src/bdd_cuda_base.cu: ](src/bdd_cuda_base.cu) contains code for setting up the GPU solver. This code performs conversion of CPU BDD representation to GPU and also provides functions to compute lower bounds, all min marginals etc.
- [src/bdd_cuda_parallel_mma.cu:](src/bdd_cuda_parallel_mma.cu) contains code for parallel deferred min-marginal averaging solver.
- [src/incremental_mm_agreement_rounding_cuda.cu](src/incremental_mm_agreement_rounding_cuda.cu) contains code for primal rounding. 

## Running
Unfortunately https://anonymous.4open.science/ does not currently offer full git functionalities therefore the code cannot be run. We will make the full code publicily available upon acceptance. 
