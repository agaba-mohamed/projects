# Input matrix
arr = [
    [8, 0, 5, 2, 0, 4, 3, 9, 0],
    [0, 0, 0, 5, 7, 0, 0, 0, 0],
    [7, 0, 2, 0, 0, 0, 0, 6, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 7, 0, 0, 0, 0, 0, 0, 0],
    [5, 0, 6, 0, 0, 0, 0, 0, 1],
    [0, 0, 0, 0, 0, 2, 0, 1, 0],
    [0, 0, 9, 0, 3, 0, 2, 0, 4],
    [0, 0, 0, 0, 0, 0, 0, 0, 0]
]

# Position of the input elements in the arr
pos = {}

# Count of the remaining number of the elements
rem = {}

# Graph defining tentative positions of the elements to be filled
graph = {}

# Keep track of the changes made
added_numbers = []

# Print the matrix array
def printMatrix():
    for i in range(0, 9):
        for j in range(0, 9):
            print(str(arr[i][j]), end=" ")
        print()


# Method to check if the inserted element is safe
def is_safe(x, y):
    key = arr[x][y]
    for i in range(0, 9):
        if i != y and arr[x][i] == key:
            return False
        if i != x and arr[i][y] == key:
            return False

    r_start = int(x / 3) * 3
    r_end = r_start + 3

    c_start = int(y / 3) * 3
    c_end = c_start + 3

    for i in range(r_start, r_end):
        for j in range(c_start, c_end):
            if i != x and j != y and arr[i][j] == key:
                return False
    return True


# Modified method to fill the matrix and track changes
def fill_matrix(k, keys, r, rows):
    for c in graph[keys[k]][rows[r]]:
        if arr[rows[r]][c] > 0:
            continue
        arr[rows[r]][c] = keys[k]
        added_numbers.append((keys[k], rows[r], c))  # Track the added number and its position
        if is_safe(rows[r], c):
            if r < len(rows) - 1:
                if fill_matrix(k, keys, r + 1, rows):
                    return True
                else:
                    arr[rows[r]][c] = 0
                    added_numbers.pop()  # Undo the change
                    continue
            else:
                if k < len(keys) - 1:
                    if fill_matrix(k + 1, keys, 0, list(graph[keys[k + 1]].keys())):
                        return True
                    else:
                        arr[rows[r]][c] = 0
                        added_numbers.pop()  # Undo the change
                        continue
                return True
        arr[rows[r]][c] = 0
        added_numbers.pop()  # Undo the change
    return False


# Fill the pos and rem dictionary. It will be used to build graph
def build_pos_and_rem():
    for i in range(0, 9):
        for j in range(0, 9):
            if arr[i][j] > 0:
                if arr[i][j] not in pos:
                    pos[arr[i][j]] = []
                pos[arr[i][j]].append([i, j])
                if arr[i][j] not in rem:
                    rem[arr[i][j]] = 9
                rem[arr[i][j]] -= 1

    # Fill the elements not present in input matrix. Example: 1 is missing in input matrix
    for i in range(1, 10):
        if i not in pos:
            pos[i] = []
        if i not in rem:
            rem[i] = 9


# Build the graph
def build_graph():
    for k, v in pos.items():
        if k not in graph:
            graph[k] = {}

        row = list(range(0, 9))
        col = list(range(0, 9))

        for cord in v:
            row.remove(cord[0])
            col.remove(cord[1])

        if len(row) == 0 or len(col) == 0:
            continue

        for r in row:
            for c in col:
                if arr[r][c] == 0:
                    if r not in graph[k]:
                        graph[k][r] = []
                    graph[k][r].append(c)


# Build the pos, rem, and graph dictionaries
build_pos_and_rem()
rem = {k: v for k, v in sorted(rem.items(), key=lambda item: item[1])}
build_graph()

# Fill the matrix
key_s = list(rem.keys())
fill_matrix(0, key_s, 0, list(graph[key_s[0]].keys()))

# Convert the added numbers into a 9x9 grid of changes
added_grid = [[0] * 9 for _ in range(9)]
for num, row, col in added_numbers:
    added_grid[row][col] = num

# Print the resulting grid and the added numbers in grid format
print("Solved Sudoku Grid:")
printMatrix()

print("\nGrid of Added Numbers:")
for row in added_grid:
    print(" ".join(str(x) for x in row))
