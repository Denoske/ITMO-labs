import matrix_io
def calculate_minor(matrix, dimension, i, j):
    return [[matrix[row][col] for col in range(dimension) if col != j] for row in range(dimension) if row != i]


def calculate_det(matrix, dimension):
    if dimension == 1:
        return matrix[0][0]
    det = 0
    sgn = 1
    for j in range(dimension):
        det += sgn * matrix[0][j] * calculate_det(calculate_minor(matrix, dimension, 0, j), dimension - 1)
        sgn *= -1
    return det


def swap_columns(matrix, dimension, col1, col2):
    for row in range(dimension):
        matrix[col1][row], matrix[col2][row] = matrix[col2][row], matrix[col1][row]


def make_element_not_zero(matrix, dimensions, i):
    for j in range(i, dimensions):
        if matrix[i][j] != 0 and matrix[j][i] != 0:
            swap_columns(matrix, dimensions, i, j)
            return
    print("Нельзя найти решение")
    exit()


def to_triangle(matrix, dimension):
    for i in range(dimension):
        if matrix[i][i] == 0:
            make_element_not_zero(matrix, dimension, i)
        for m in range(i + 1, dimension):
            a = -(matrix[m][i] / matrix[i][i])
            for j in range(i, dimension):
                matrix[m][j] += a * matrix[i][j]
            matrix[m][-1] += a * matrix[i][-1]
        sum = 0
        for j in range(dimension):
            sum += matrix[i][j]
        if sum == 0:
            print("Система не имеет решений")
            exit()
        #matrix_io.print_matrix(matrix, dimension)
        #print()


def calc_answer(matrix, dimension):
    answer = []
    answer.append(matrix[dimension - 1][-1]/matrix[dimension - 1][dimension - 1])
    i = dimension - 2
    while i >= 0:
        result = matrix[i][-1]
        k = dimension - 1
        while k > i:
            result -= answer[dimension - 1 - k] * matrix[i][k]
            k -= 1
        result /= matrix[i][i]
        answer.append(result)
        i -= 1
    answer.reverse()
    return answer

def calc_discrepancy(matrix, dimension, answer):
    discrepancy = []
    for i in range(dimension):
        sum = 0
        for j in range(dimension):
            sum += matrix[i][j] * answer[j]
        discrepancy.append([sum, matrix[i][-1], abs(sum - matrix[i][-1])])
    return discrepancy
