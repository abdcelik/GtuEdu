import random

# ----- Helper functions start -----
def create_1d_array(size):
    arr = []
    
    for i in range(size):
        arr.append(random.randint(1, 100))
    
    return arr

def create_2d_array(row, col):
    arr = [[0 for _ in range(col)] for _ in range(row)]

    for i in range(row):
        for j in range(col):
            arr[i][j] = random.randint(10, 70)

    return arr
# ----- Helper functions end   -----

# Question 1 start
def common(str1, str2): # Returns common part betwen string1 and string2
    def _iterator():
        for str1_char, str2_char in zip(str1, str2):
            if str1_char == str2_char:
                yield str1_char
            else:
                return

    return ''.join(_iterator())

def longest_substring(str_arr, left, right):
    if left == right:
        return str_arr[left]

    middle = int(left + (right - left ) / 2)

    left_part = longest_substring(str_arr, left, middle)
    right_part = longest_substring(str_arr, middle + 1, right)

    return common(left_part, right_part)
# Question 1 end

# Question 2 start
# Returns maximum profit, minimum item index, maximum item index
def find_min_index(arr, left, right):
    min = arr[left]
    minIndex = left

    for i in range(left, right + 1):
        if arr[i] < min:
            min = arr[i]
            minIndex = i
    
    return minIndex

def find_max_index(arr, left, right):
    max = arr[left]
    maxIndex = left

    for i in range(left, right + 1):
        if arr[i] > max:
            max = arr[i]
            maxIndex = i
    
    return maxIndex


def find_min_and_max_in_logaritmic(arr, left, right):
    if left == right:
        return (0, left, right)

    middleIndex = int(left + (right - left) / 2)

    (leftSubProfit, leftSubMinIndex, leftSubMaxIndex) = find_min_and_max_in_logaritmic(arr, left, middleIndex)
    (rightSubProfit, rightSubMinIndex, rightSubMaxIndex) = find_min_and_max_in_logaritmic(arr, middleIndex + 1, right)

    leftMinItemIndex = find_min_index(arr, left, middleIndex)
    rightMaxItemIndex = find_max_index(arr, middleIndex + 1, right)

    # cross profit
    minItemIndex = leftMinItemIndex
    maxItemIndex = rightMaxItemIndex
    maxProfit = arr[maxItemIndex] - arr[minItemIndex]

    if maxProfit < leftSubProfit:
        minItemIndex = leftSubMinIndex
        maxItemIndex = leftSubMaxIndex
        maxProfit = leftSubProfit

    if maxProfit < rightSubProfit:
        minItemIndex = rightSubMinIndex
        maxItemIndex = rightSubMaxIndex
        maxProfit = rightSubProfit

    return (maxProfit, minItemIndex, maxItemIndex)

def find_max_profit_linear(arr):
    buy = maxProfit = savedBuy = savedSell = 0

    for sell in range(1, len(arr)):
        if arr[sell] > arr[buy]:
            profit = arr[sell] - arr[buy]

            if profit > maxProfit:
                maxProfit = profit
                savedBuy = buy
                savedSell = sell
        else:
            buy = sell
        
    return maxProfit, savedBuy, savedSell
# Question 2 end

# Question 3 start
def longest_increasing_subarray_with_dynamic_prog(arr, size):
    longestConsecutive = [1] * size
    
    for i in range(1, size):
        if arr[i] > arr[i - 1]:
            longestConsecutive[i] = longestConsecutive[i - 1] + 1

    return max(longestConsecutive)
# Question 3 end

# Question 4 start
# Prints map
def print_array(arr, row, col):
    print("Input: n = ", row, ", m = ", col)
    print("Game map:")

    for row in arr:
        for item in row:
            print("{:2d}".format(item), end="  ")
        print()

# Returns path string
def find_maximum_path(arr, row, column):
    current_row = row - 1
    current_col = column - 1
    indices = []

    while current_row >= 0 and current_col >= 0:
        indices.append((current_row + 1, current_col + 1))
        up = left = 0

        if current_row - 1 >= 0:
            up = arr[current_row-1][current_col]
        
        if current_col - 1 >= 0:
            left = arr[current_row][current_col-1]

        if left > up:
            current_col -= 1
        else:
            current_row -= 1

    return indices[::-1]

# Finds highest score using dynamic programming
def highest_score_dyanmic_prog(arr, row, column):
    maxCost = [[0 for x in range(column)] for y in range(row)]
    maxCost[0][0] = arr[0][0]

    for i in range(1, row):
        maxCost[i][0] = maxCost[i-1][0] + arr[i][0]
    
    for j in range(1, column):
        maxCost[0][j] = maxCost[0][j-1] + arr[0][j]
    
    for i in range(1, row):
        for j in range(1, column):
            maxCost[i][j] = max(maxCost[i - 1][j], maxCost[i][j - 1]) + arr[i][j]

    return maxCost[row - 1][column - 1], find_maximum_path(maxCost, row, column)

def highest_score_greedy(arr, row, column):
    path = []
    max_cost = arr[0][0]
    current_row = current_col = 0
  
    while current_row < row and current_col < column:
        down = right = 0
        path.append((current_row + 1, current_col + 1))

        if current_row + 1 < row:
            down = arr[current_row + 1][current_col]

        if current_col + 1 < column:
            right = arr[current_row][current_col + 1]

        if down > right:
            max_cost += down
            current_row += 1
        else:
            max_cost += right
            current_col += 1

    return max_cost, path
# Question 4 end

# Question 1 driver start
print("--- Question 1 ---")
Q1_arr = ["programmable", "programming", "programmer", "programmatic", "programmability"]
print(Q1_arr)
print("Common substring: {}\n".format(longest_substring(Q1_arr, 0, len(Q1_arr) - 1)))
# Question 1 driver end

# Question 2 driver start
print("--- Question 2 ---")
Q2_arr_size = random.randint(5, 10)
Q2_arr = create_1d_array(Q2_arr_size)
print(Q2_arr)
print("(a)")
(profit, minIndex, maxIndex) = find_min_and_max_in_logaritmic(Q2_arr, 0, Q2_arr_size - 1)
print("Buy on Day{} for {}$ and sell on Day{} for {}$. Profit: {}$".format(minIndex, Q2_arr[minIndex], maxIndex, Q2_arr[maxIndex], profit))

print("(b)")
(profit, linear_min, linear_max) = find_max_profit_linear(Q2_arr)
print("Buy on Day{} for {}$ and sell on Day{} for {}$. Profit: {}$\n".format(linear_min, Q2_arr[linear_min], linear_max, Q2_arr[linear_max], profit))
# Question 2 driver end

# Question 3 driver start
print("--- Question 3 ---")
Q3_arr_size = random.randint(5, 10)
Q3_arr = create_1d_array(Q3_arr_size)
print(Q3_arr)
print("Output: {}\n".format(longest_increasing_subarray_with_dynamic_prog(Q3_arr, Q3_arr_size)))
# Question 3 driver end

# Question 4 driver start
print("--- Question 4 ---")
Q4_arr_row = 4
Q4_arr_column = 3
Q4_arr = [
    [25, 30, 25],
    [45, 15, 11],
    [1, 88, 15],
    [9, 4, 23]
]

(Q4_a_max_point, a_path) = highest_score_dyanmic_prog(Q4_arr, Q4_arr_row, Q4_arr_column)
print_array(Q4_arr, Q4_arr_row, Q4_arr_column)
print("(a)")
print("Route:", end=" ")
for i, (row, column) in enumerate(a_path):
    print("A{}B{}".format(row, column), end="")
    if i < len(a_path) - 1:
        print(' -> ', end='')
print("\nPoints:", end=" ")
for i, (row, column) in enumerate(a_path):
    print("{}".format(Q4_arr[row-1][column-1]), end="")
    if i < len(a_path) - 1:
        print(' + ', end='')
print(" = {}\n".format(Q4_a_max_point))

print("(b)")
(Q4_b_max_point, b_path) = highest_score_greedy(Q4_arr, Q4_arr_row, Q4_arr_column)
print("Route:", end=" ")
for i, (row, column) in enumerate(b_path):
    print("A{}B{}".format(row, column), end="")
    if i < len(b_path) - 1:
        print(' -> ', end='')
print("\nPoints:", end=" ")
for i, (row, column) in enumerate(b_path):
    print("{}".format(Q4_arr[row-1][column-1]), end="")
    if i < len(b_path) - 1:
        print(' + ', end='')
print(" = {}\n".format(Q4_b_max_point))
# Question 4 driver end

# -- Random map --
Q4_arr_random_row = random.randint(4, 8)
Q4_arr_random_column = random.randint(4, 8)
Q4_arr_random = create_2d_array(Q4_arr_random_row, Q4_arr_random_column)

print("Random inputs")
print_array(Q4_arr_random, Q4_arr_random_row, Q4_arr_random_column)
print("(a)")

(rand_max_a, rand_path_a) = highest_score_dyanmic_prog(Q4_arr_random, Q4_arr_random_row, Q4_arr_random_column)
print("Route:", end=" ")
for i, (row, column) in enumerate(rand_path_a):
    print("A{}B{}".format(row, column), end="")
    if i < len(rand_path_a) - 1:
        print(' -> ', end='')
print("\nPoints:", end=" ")
for i, (row, column) in enumerate(rand_path_a):
    print("{}".format(Q4_arr_random[row-1][column-1]), end="")
    if i < len(rand_path_a) - 1:
        print(' + ', end='')
print(" = {}\n".format(rand_max_a))

print("(b)")
(rand_max_b, rand_path_b) = highest_score_greedy(Q4_arr_random, Q4_arr_random_row, Q4_arr_random_column)
print("Route:", end=" ")
for i, (row, column) in enumerate(rand_path_b):
    print("A{}B{}".format(row, column), end="")
    if i < len(rand_path_b) - 1:
        print(' -> ', end='')
print("\nPoints:", end=" ")
for i, (row, column) in enumerate(rand_path_b):
    print("{}".format(Q4_arr_random[row-1][column-1]), end="")
    if i < len(rand_path_b) - 1:
        print(' + ', end='')
print(" = {}\n".format(rand_max_b))