# Question 1 start
def topological_sort_with_DFS(Graph):
    my_list = []
    my_set = set()

    def DFS(node):
        my_set.add(node)
        for outgoing_edge in Graph[node]:
            if outgoing_edge not in my_set:
                DFS(outgoing_edge)
        my_list.insert(0, node)
        
    for node in Graph:
        if node not in my_set:
            DFS(node)

    return my_list
    
def topological_sort_with_non_DFS(Graph):
    my_list = []
    my_queue = []
    indegrees = {node: 0 for node in Graph}

    for node in Graph:
        for outgoing_edge in Graph[node]:
            indegrees[outgoing_edge] += 1
    
    for node in indegrees:
        if indegrees[node] == 0:
            my_queue.append(node)

    while my_queue:
        node = my_queue.pop(0)
        my_list.append(node)

        for outgoing_edge in Graph[node]:
            indegrees[outgoing_edge] -= 1
            
            if indegrees[outgoing_edge] == 0:
                my_queue.append(outgoing_edge)

    if len(my_list) != len(Graph):
        return "Error: DAG has a cycle"
    return my_list
# Question 1 end

# Question 2 start
def power(base, exponent):
    if(exponent == 0):
        return 1
    
    result = power(base, int(exponent/2))
    result *= result;
    
    if(exponent % 2 == 1):
        result *= base
        
    return result;
# Question 2 end

# Question 3 start
def isValid(grid, row, col, num):   # Function to check if a given number is a valid choice for a given cell in the sudoku grid
    for i in range(9):
        if grid[row][i] == num:
            return False
            
    for i in range(9):
        if grid[i][col] == num:
            return False

    row_start = (row//3)*3
    col_start = (col//3)*3
    for i in range(row_start, row_start+3):
        for j in range(col_start, col_start+3):
            if grid[i][j] == num:
                return False
    return True

def solveSudoku(grid, row, col):    # Recursive function to solve the sudoku game
    if row > 8 or col > 8:
        return True
        
    if grid[row][col] != 0:
        if col == 8:
            return solveSudoku(grid, row+1, 0)
        else:
            return solveSudoku(grid, row, col+1)

    for num in range(1, 10):
        if isValid(grid, row, col, num):
            grid[row][col] = num
            if col == 8:
                if solveSudoku(grid, row+1, 0):
                    return True
            else:
                if solveSudoku(grid, row, col+1):
                    return True

    grid[row][col] = 0
    return False 
# Question 3 end

# Driver
print("-- Question 1 --")
graph_instance = {
    "CSE102": ["CSE241"],
    "CSE241": ["CSE222"],
    "CSE222": ["CSE321"],
    "CSE321": ["CSE422"],
    "CSE211": ["CSE321"],
    "CSE422" : []
}

print("a) ", topological_sort_with_DFS(graph_instance))
print("b) ", topological_sort_with_non_DFS(graph_instance))
print("----------------")

print("-- Question 2 --")
print("2^4 =", power(2,4))
print("2^7 =", power(2,7))
print("----------------")

print("-- Question 3 --")

grid = [[5, 3, 0, 0, 7, 0, 0, 0, 0],
        [6, 0, 0, 1, 9, 5, 0, 0, 0],
        [0, 9, 8, 0, 0, 0, 0, 6, 0],
        [8, 0, 0, 0, 6, 0, 0, 0, 3],
        [4, 0, 0, 8, 0, 3, 0, 0, 1],
        [7, 0, 0, 0, 2, 0, 0, 0, 6],
        [0, 6, 0, 0, 0, 0, 2, 8, 0],
        [0, 0, 0, 4, 1, 9, 0, 0, 5],
        [0, 0, 0, 0, 8, 0, 0, 7, 9]]
        
print("Initially:")
for row in grid:
    print(row)

solveSudoku(grid, 0, 0)

print("Finally:")
for row in grid:
    print(row)
print("----------------")