from get_grid import main as get_grid
from solve_grid import main as solve_grid
from draw_numbers import main as draw_numbers

grid = get_grid()

solved_grid = solve_grid(grid)

draw_numbers(solved_grid)
