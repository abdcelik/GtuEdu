import random

# ----- Helper functions start -----
def create_1d_array(size):
    arr = []
    
    for i in range(size):
        arr.append(random.randint(0, 50))
    
    return arr

def create_2d_array(row, col):
    arr = [[0 for _ in range(col)] for _ in range(row)]

    for i in range(row):
        for j in range(col):
            arr[i][j] = random.randint(1, 50)

    return arr

def print_array(arr, row, col):
    print("Input: n = ", row, ", m = ", col)
    print("Game map:")

    for row in arr:
        for item in row:
            print("{:2d}".format(item), end="  ")
        print()

class Node:
    def __init__(self, data=None):
        self.data = data
        self.next = None

class CircularLinkedList:
    def __init__(self):
        self.head = None
        self.tail = None
    
    def append(self, data):
        new_node = Node(data)
        
        if not self.head:
            self.head = new_node
            self.tail = new_node
            new_node.next = self.head
        else:
            self.tail.next = new_node
            self.tail = new_node
            self.tail.next = self.head
    
    def __str__(self):
        values = []
        current_node = self.head
        
        while current_node:
            values.append(str(current_node.data))
            current_node = current_node.next
            if current_node == self.head:
                break
        
        return ' -> '.join(values)

def create_circular_linked_list(size):
    circular_ll = CircularLinkedList()
    
    for i in range(1, size + 1):
        circular_ll.append(i)
    
    return circular_ll
# ----- Helper functions end -----

# ----- Question 1 start -----
def partially_dijkstra(map, row, column, i, j):
    if i == row - 1 and j == column - 1:
        return map[i][j], [(i+1, j+1)]
    
    right_move_max_point = 0
    bottom_move_max_point = 0
    right_move_path = []
    bottom_move_path = []
    
    if i < row - 1:
        right_move_max_point, right_move_path = partially_dijkstra(map, row, column, i+1, j)
    
    if j < column - 1:
        bottom_move_max_point, bottom_move_path = partially_dijkstra(map, row, column, i, j+1)
    
    if right_move_max_point > bottom_move_max_point:
        return map[i][j] + right_move_max_point, [(i+1, j+1)] + right_move_path
    else:
        return map[i][j] + bottom_move_max_point, [(i+1, j+1)] + bottom_move_path
# ----- Question 1 end -----

# ----- Question 2 start -----
def partition(array, left, right):
    pivot = array[right]    # select right most element as pivot
    i = left
    for j in range(left, right):
        if array[j] <= pivot:
            (array[i], array[j]) = (array[j], array[i])
            i = i + 1
              
    array[i], array[right] = array[right], array[i]
    return i

def quickselect(array, left, right, key):

    if key <= 0 and key > (right - left + 1):
        print("Key index is out of bound!")
    
    index = partition(array, left, right)

    if (index - left == key - 1):   # Is index is kth element?
        return array[index]

    if (index - left > key - 1):    # quickselect for left subarray
        return quickselect(array, left, index - 1, key)

    return quickselect(array, index + 1, right, key - index + left - 1) # quickselect for right subarray
    
def median():
    
    size = random.randint(5, 15)
    array = create_1d_array(size)
    
    print("Array: ", array)
    print("Size: ", size)
    
    key = int(size / 2)
    med = 0
    
    if size % 2 == 0:
        med += quickselect(array, 0, size - 1, key)
        med += quickselect(array, 0, size - 1, key + 1)
        med /= 2
    else:
        med = quickselect(array, 0, size - 1, key + 1)

    print("Median: ", med)
# ----- Question 2 end -----

# ----- Question 3 start -----
def find_winner(self):
    curr = self.head
    while curr.next != curr:
        print("P{} eliminates P{}".format(curr.data, curr.next.data))
        curr.next = curr.next.next
        curr = curr.next
    return curr.data

def find_winner_logaritmic(size):
    if (size == 1):
        return 1
 
    if (size % 2 == 0):
        return 2 * find_winner_logaritmic(size / 2) - 1
    
    return 2 * find_winner_logaritmic(((size - 1) / 2)) + 1

# ----- Question 3 end -----

# Driver
print()
print("-- Question 1 --")

row = random.randint(2, 7)
column = random.randint(2, 7)
map = create_2d_array(row, column)

print_array(map, row, column)
max_point, max_path = partially_dijkstra(map, row, column, 0, 0)

print("Path: ", max_path)
print("Max point: ", max_point)

print("----------------")

print()
print()

print("-- Question 2 --")
median()
print("----------------")

print()
print()

print("-- Question 3 --")
print("(a)")
circular_ll = create_circular_linked_list(random.randint(2, 10))
print("Circular Linked List: ", circular_ll)
print("Winner: P{}".format(find_winner(circular_ll)))
print()
print("(b)")
size = random.randint(2, 10)
print("Player number: ", size-1)
for i in range(1, size):
    print(i, end=" ")
print()
print("(Logaritmic calculated)Winner: P{}".format(find_winner_logaritmic(size-1)))

print("----------------")