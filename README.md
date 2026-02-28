Linear Equation Solver (C++ CLI)
Project Type: Systems of Linear Equations Solver
Algorithm: Gaussian Elimination (Partial Pivoting)
Interface: Command-Line (CLI)

📖 Project Overview
This project is a C++ application designed to parse and solve systems of linear equations. It features a custom-built parser that reads equations in standard string format (e.g., 2x1+3x2=10) and a mathematical engine that uses Gaussian Elimination to solve for n variables.

✨ Key Features
•	Dynamic Parsing: Directly parses equations containing +, -, and variable indices (e.g., x1, x2).
•	Memory Management: Uses dynamic 2D array allocation for matrices to handle varying system sizes.
•	Robust Solver: Implements row swapping (pivoting) to handle cases where a pivot element is zero.
•	Command-Based Interface: Interactive loop allowing users to query specific data before or after solving.

🚀 Getting Started
1. Compilation
Use any standard C++ compiler 
g++ -o solver main.cpp

2. Execution
Run the program:
.solve

3. Usage Flow
1.	Enter Number of Equations: Provide an integer n.
2.	Input Equations: Type each equation on a new line (e.g., 1x1+2x2=5).
3.	Use Commands: Once input is finished, use the following commands:
o	num_vars: Displays the number of variables detected.
o	equation [i]: Displays the i ^ th processed equation.
o	column [xk]: Displays all coefficients for variable xk.
o	solve: Executes Gaussian Elimination and outputs values.
o	quit: Exits the program.
👥 Task Breakdown Structure
Task	Description
Parsing Logic	Converting string input into coefficient matrices and RHS vectors.
Matrix Operations	Dynamic memory allocation and deallocation for n * n matrices.
Gaussian Solver	Implementing forward elimination, pivoting, and back substitution.
CLI Command Loop	Handling interactive user commands (solve, column, etc.).

