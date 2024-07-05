# Textrix Codicum: Pseudocode to C++ Code Generator

**Textrix Codicum** is a powerful tool designed to seamlessly convert algorithmic pseudocode into executable and well structured C++ code. By automating the parsing and interpretation of custom syntax, this project generates robust C++ code that supports variables, loops, functions, and more. It's ideal for students, educators, and developers to streamline the transition from algorithm design to implementation.

## Features

- **Variable Declarations**: Supports integers, strings, booleans, and arrays.
- **Assignments**: Easily assign values to variables.
- **Conditional Operators**: Includes standard comparison operators (`<`, `>`, `<=`, `>=`, `==`).
- **Arithmetic Operations**: Perform arithmetic calculations.
- **Logical Operations**: Evaluate logical expressions.
- **Control Structures**: Implement if statements, else-if statements, for loops, while loops, and do-while loops.
- **Functions and Procedures**: Define functions with return values and procedures (void functions).
- **Input and Output**: Read from input and print output.

## Future Milestones

- **Bidirectional Conversion**: Implement the functionality to convert C++ code back to pseudocode, enabling seamless bidirectional conversion.
- **Multilingual Support**: Extend support to multiple programming languages, transforming the tool into a versatile converter between different languages, including pseudocode.
- **Developer-Friendly Extensions**: Allow developers to add new language support by writing the conversion logic between the new language and pseudocode in the new language itself.
- **Automated Language Conversion**: Facilitate automatic conversion from the source language to the target language by first converting the source language to pseudocode and then from pseudocode to the target language.


## Pseudocode Syntax

### Declaration
- `Declare x As Integer`
- `Declare str As String`
- `Declare a As Boolean`
- `Declare arr As Array Of Integer[3]`
- `Declare mat As Array of Integer[1][1]`

### Assignment
- `x = 10`
- `str = "Suyash"`
- `a = True`
- `arr[0] = 1`
- `mat[0][0] = 2`

### Conditional Operators
- `<`, `>`, `<=`, `>=`, `==`

### Arithmetic Operations
- `x = a + b`
- `y = 2 * 3`

### Logical Operations
- `isTrue = True And False`
- `isBig = a > b`

### If Statement
- `If x > 10 Then x = x + 1 Else x = x - 1 End If`

### Else If Statement
- `If x == 1 Then x = 0 Else If x == 2 Then x = 1 Else x = -1 End If`

### For Loop
- `For i=1 To 10 Do i = i + 1 End For`

### While Loop
- `While x < 10 Do x = x * 2 End While`

### Do While Loop
- `Do x = x + 1 While x < 10`

### Functions (Return Value)
- `Function add(x As Integer, b As Integer) As Integer Return a + b End Function`

### Procedure (Void Functions)
- `Procedure print(x As Integer) x = x + 1 End Procedure`

### Input and Output
- `Read x`
- `Print "I am Suyash!"`

## Example Conversion

### Pseudocode

```plaintext
Declare x As Integer
Declare y As Integer
Declare result As Integer
Declare arr As Array Of Integer[5]
Declare matrix As Array Of Integer[3][3]
Declare str As String
Declare concatResult As String

Assign x = 5
Assign y = x + 5 * 3
Print result

If result > 10 Then
    Assign x = 5
    Print "Result is greater than 10"
Else
    Print "Result is 10 or less"
    Assign x = 10
End If

If result > 10 Then
    If x = 3+4 Then
        Assign x = 3*3
    End If
Else
    If x < 23 Then
        Print "Result is 10 or less"
        Assign x = 10
    Else 
        Declare z As Integer
        Assign z = 234
    End If
End If

For i=0 To 4 Do
    Assign arr[i] = i * 2
End For

For i=0 To 2 Do
    For j=0 To 2 Do
        Assign matrix[i][j] = i + j
    End For
End For

For i=0 To 2 Do
    For j=0 To 2 Do
        If i = 0 Then   
            Print i
        Else
            Print j
        End If
    End For
End For

Assign str = "Hello"
Assign concatResult = str + " World"
Print concatResult

While i < 4 Do
    Assign i = i + 1
    Print i
End While

While i < 4 Do
    If i = 0 Then
        Print "Zero"
    Else 
        Print "NoZero"
    End If
    Assign i = i + 1
End While
```

### Generated C++ Code 

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {

	int x;
	int y;
	int result;
	int arr[5];
	int matrix[3][3];
	string str;
	string concatResult;
	int i;
	x = 5 ;
	y = x + 5 * 3 ;
	cout << result << endl;
	if ( result > 10 ) {
		x = 5 ;
		cout << "Result is greater than 10" << endl;
	}
	else {
		cout << "Result is 10 or less" << endl;
		x = 10 ;
	}

	if ( result > 10 ) {
		if ( x = 3 + 4 ) {
			x = 3 * 3 ;
		}
	}
	else {
		if ( x < 23 ) {
			cout << "Result is 10 or less" << endl;
			x = 10 ;
		}
		else {
			int z;
			z = 234 ;
		}

	}

	for (int i = 0 ; i <= 4 ; i++) {
		arr[i] = i * 2 ;
	}

	for (int i = 0 ; i <= 2 ; i++) {
		for (int j = 0 ; j <= 2 ; j++) {
			matrix[i][j] = i + j ;
		}

	}

	for (int i = 0 ; i <= 2 ; i++) {
		for (int j = 0 ; j <= 2 ; j++) {
			if ( i = 0 ) {
				cout << i << endl;
			}
			else {
				cout << j << endl;
			}

		}

	}

	str = "Hello" ;
	concatResult = str + " World" ;
	cout << concatResult << endl;
	while (i < 4 ) {
		i = i + 1 ;
		cout << i << endl;
	}

	while (i < 4 ) {
		if ( i = 0 ) {
			cout << "Zero" << endl;
		}
		else {
			cout << "NoZero" << endl;
		}

		i = i + 1 ;
	}


return 0;
}
```

## Getting Started

### Prerequisites
- A basic understanding of C++.
- A C++ compiler (like GCC, Clang, or MSVC).

### Installation
Clone the repository:
```bash
git clone https://github.com/Suyashchavan10/Textrix-Codicum.git
```
Navigate to the project directory:
```bash
cd Textrix-codicum
```
Run the code from terminal
```
make
```
## Usage

1. Write your pseudocode in the specified format.
2. Run the tool to convert pseudocode to C++ code.
3. Compile and run the generated C++ code.



