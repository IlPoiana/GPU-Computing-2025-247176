## Valgrind usage
Tipical workflow:
1. Compile using `-g` flag option
2. Execute `valgrind --tool=cachegrind <program>` for getting the cache analysis
3. run `cg_annotate --auto=yes <cachegrind.out>` to get a detailed row by row execution analysis of the program


*citing from the official website*

- I cache reads (`Ir`, which equals the number of instructions executed), I1 cache read misses (`I1mr`) and LL cache instruction read misses (`ILmr`).

- D cache reads (`Dr`, which equals the number of memory reads), D1 cache read misses (`D1mr`), and LL cache data read misses (`DLmr`).

- D cache writes (`Dw`, which equals the number of memory writes), D1 cache write misses (`D1mw`), and LL cache data write misses (`DLmw`).

**Note that D1 total accesses is given by D1mr + D1mw, and that LL total accesses is given by ILmr + DLmr + DLmw.**

When simulating the branch predictor, with --branch-sim=yes, Cachegrind gathers the following statistics:

-   Conditional branches executed (`Bc`) and conditional branches mispredicted (`Bcm`).

-   Indirect branches executed (`Bi`) and indirect branches mispredicted (`Bim`).
