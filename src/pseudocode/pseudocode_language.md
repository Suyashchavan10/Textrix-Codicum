# Declaration
1. Declare x As Integer
2. Declare str As String
3. Declare a As Boolean
4. Declare arr As Array Of Integer[3]
5. Declare mat As Array of Integer[1][1]

# Assignment
1. x = 10
2. str = "Suyash"
3. a = True
4. arr[0] = 1
5. mat[0][0] = 2

# Conditional operators
<, >, <=, >=, ==

# Arithmetic operations
1. x = a + b
2. y = 2 * 3

# Logical operations
1. isTrue = True And False
2. isBig = a > b

# If statement
1. If x > 10 Then
    x = x + 1
Else 
    x = x - 1
End If

# Else If statement
1. If x == 1 Then
    x = 0
Else If x == 2 Then
    x = 1
Else 
    x = -1
End If

# For loop
1. For i=1 To 10 Do
    i = i + 1
End For

# While loop
1. While x < 10 Do
    x = x * 2
End While

# Do while loop
1. Do
    x = x + 1
While x < 10

# Functions (return value)
1. Function add(x As Integer, b As Integer) As Integer
    Return a + b
End Function

# Procedure (void functions)
1. Procedure print(x As Integer)
    x = x + 1
End Procedure

# Input and Output
1. Read x
2. Print "I am Suyash!"

# Example Conversion
1. Pseudocode :

Function add(a As Integer, b As Integer)
    Return a + b
End Function

Declare x As Integer
Declare y As Integer
Declare result As Integer
Declare arr As Array OF Integer[5]
Declare matrix As Array OF Integer[3][3]
Declare str As String
Declare concatResult As String

x = 5
y = 10
result = add(x, y)
Print result

If result > 10 Then
    Print "Result is greater than 10"
Else
    Print "Result is 10 or less"
End If

For i=0 To 4 Do
    arr[i] = i * 2
End For

For i=0 To 2 Do
    For j=0 To 2 Do
        matrix[i][j] = i + j
    End For
End For

For i=0 To 2 Do
    For j=0 To 2 Do
        Print matrix[i][j]
    End For
End For

str = "Hello"
concatResult = str + " World"
Print concatResult

Declare isTrue As Boolean
Declare isFalse As Boolean
Declare boolResult As Boolean

isTrue = True
isFalse = False
boolResult = isTrue And isFalse
Print boolResult

2. C++ code :

#include <iostream>
#include <string>
using namespace std;

int add(int a, int b) {
    return a + b;
}

int main() {
    int x;
    int y;
    int result;
    int arr[5];
    int matrix[3][3];
    string str;
    string concatResult;

    x = 5;
    y = 10;
    result = add(x, y);
    cout << result << endl;

    if (result > 10) {
        cout << "Result is greater than 10" << endl;
    } else {
        cout << "Result is 10 or less" << endl;
    }

    for (int i = 0; i < 5; ++i) {
        arr[i] = i * 2;
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            matrix[i][j] = i + j;
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    str = "Hello";
    concatResult = str + " World";
    cout << concatResult << endl;

    bool isTrue = true;
    bool isFalse = false;
    bool boolResult = isTrue && isFalse;
    cout << boolResult << endl;

    return 0;
}


