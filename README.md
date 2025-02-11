# Left Recursion Elimination in Context-Free Grammars
This C++ program is designed to eliminate left recursion from a given context-free grammar (CFG). Left recursion is a common issue in grammars that can cause problems in parsing algorithms, particularly in top-down parsers like recursive descent parsers. This program implements an algorithm to eliminate both immediate and indirect left recursion from a CFG.

## Approach
The program follows these steps to eliminate left recursion:

**Input Parsing**: The grammar is input by the user in a specific format. The program parses the input and stores the non-terminals and their production rules.

#### Immediate Left Recursion Elimination:

For each non-terminal, the program checks if it has immediate left recursion (i.e., productions of the form A -> Aα).

If immediate left recursion is found, the program rewrites the productions to eliminate it. This involves introducing a new non-terminal to handle the recursion and ensuring that the original non-terminal no longer has left-recursive productions.

#### Indirect Left Recursion Elimination:

The program checks for indirect left recursion, where a non-terminal indirectly refers to itself through other non-terminals.

It eliminates indirect left recursion by substituting the productions of the intermediate non-terminals.

**Output**: After eliminating left recursion, the program prints the modified grammar.

### Input Format
The input to the program is a set of production rules in the following format:

```
A -> production1 | production2 | ...
```
- A is a non-terminal.

- production1, production2, etc., are the right-hand sides of the production rules.

- Multiple productions for the same non-terminal are separated by the | symbol.

- The -> symbol separates the non-terminal from its productions.

#### Example Input
```
Enter the number of production rules: 3
Enter the production rules in the format: A -> production1 | production2 | ...
A -> Aa | b
B -> Bc | d
C -> Cx | y
```

#### Sample Input and Output

Input
```
Enter the number of production rules: 3
Enter the production rules in the format: A -> production1 | production2 | ...
A -> Aa | b
B -> Bc | d
C -> Cx | y
```

Output
```
Grammar after eliminating left recursion:
A -> bA'
A' -> aA' | ε
B -> dB'
B' -> cB' | ε
C -> yC'
C' -> xC' | ε
```

### Explanation of the Output
- The original grammar had left-recursive productions for non-terminals A, B, and C.

- The program introduced new non-terminals A', B', and C' to handle the left recursion.

- The modified grammar no longer contains left recursion, making it suitable for top-down parsing algorithms.

### How to Run the Code
Compile the code using a C++ compiler:

```
g++ -o left_recursion_elimination left_recursion_elimination.cpp
```

Run the executable:
```
./left_recursion_elimination
```

Follow the prompts to input the grammar rules.

### Dependencies
- The code uses standard C++ libraries and does not require any external dependencies.

### Limitations
- The program assumes that the input grammar is well-formed and does not handle errors in the input format.

- It does not handle left recursion in cases where the grammar is ambiguous or contains cycles that are not left-recursive.

### Conclusion
This program provides a straightforward implementation of left recursion elimination in context-free grammars. It is useful for preparing grammars for use in top-down parsing algorithms, ensuring that they are free from left recursion.

Credits- GFG (This code is a modified and more dynamic version of left recursion eliminator available on GFG)
