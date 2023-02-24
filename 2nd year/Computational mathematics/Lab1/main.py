import matrix_io
import calculations
import copy

input_type = matrix_io.read_input_type(["с клавиатуры", "из файла", "случайными числами"])

if input_type == 0:
    matrix, dimension = matrix_io.get_matrix_input()
elif input_type == 1:
    matrix, dimension = matrix_io.get_matrix_file("input.txt")
elif input_type == 2:
    matrix, dimension = matrix_io.get_random_matrix()
else:
    matrix, dimension = matrix_io.get_random_matrix()

print("Полученная матрица:")

matrix_io.print_matrix(matrix, dimension)

#det = calculations.calculate_det(matrix, dimension)
print()
#print("Определитель данной матрицы: " + str(det))

#if det == 0:
 #   print("Матрица не совместна.")
  #  exit()

triangle_matrix = copy.deepcopy(matrix)

calculations.to_triangle(triangle_matrix, dimension)
print()
print("Матрица в треугольном виде:")

matrix_io.print_matrix(triangle_matrix, dimension)

answer = calculations.calc_answer(triangle_matrix, dimension)
print()
print("Полученный ответ: ")
matrix_io.print_answer(answer, dimension)

discrepancy = calculations.calc_discrepancy(matrix, dimension, answer)
print()
print("Полученные невязки: ")
matrix_io.print_discrepancy(discrepancy)

