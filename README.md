# Optimizing the costs of an energy company

Work for the Optimization subject in the Computer Science course at the Federal University of Paraná.

Done by Anderson Frasão and Richard Heise

Objective

To model an optimization problem

Implementation

  The implementation is a C code that simply reads the inputs from the keyboard and generates an output file ready to be passed to lp solve. Due to the restrictions of lp solve, the code expands the sums and writes them in full, along with the other equations and inequalities, in stdout. Reading is done according to the number of months n and other information read from stdin.

Execution

Compile with
> make

Run with
> ./despacho < exemplo.txt | ./lp_solve_5.5.2.11_exe_ux64/lp_solve
