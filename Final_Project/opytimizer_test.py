import numpy as np
import math

from opytimizer import Opytimizer
from opytimizer.utils.callback import Callback
from opytimizer.core import Function
from opytimizer.optimizers.science import WCA
from opytimizer.spaces import SearchSpace
import tkinter as tk

Cities = [
  [156, 89],
  [32, 174],
  [105, 40],
  [68, 116],
  [187, 61],
  [83, 173],
  [21, 97],
  [145, 32],
  [198, 112]
]

def update_graph(order):
    # Clear the canvas
    canvas.delete("line")

    # Plot the current solution
    to_plot = [int(i) for i in order]
    didPoints = False
    for i in range(len(to_plot) - 1):
        x1, y1 = Cities[to_plot[i]]
        x2, y2 = Cities[to_plot[i + 1]]
        # flip y axis
        y1 = 200 - y1
        y2 = 200 - y2
        x1 *= 3
        y1 *= 3
        x2 *= 3
        y2 *= 3
        if not didPoints:
            canvas.create_oval(x1-2, y1-2, x1+2, y1+2, fill="red", outline="red", width=5)
            canvas.create_oval(x2-2, y2-2, x2+2, y2+2, fill="red", outline="red", width=5)
        canvas.create_line(x1, y1, x2, y2, fill="blue", width=2, tags="line")
    didPoints = True
    # Update the canvas
    canvas.update()

# Create a tkinter window
window = tk.Tk()

# Create a canvas to draw the graph
canvas = tk.Canvas(window, width=650, height=600)
canvas.pack()

# Start the tkinter main loop








def Distance(city1: list[int], city2: list[int]):
    return math.sqrt((city1[0] - city2[0]) ** 2 + (city1[1] - city2[1]) ** 2)

def ConvertPrioritiesToCityOrder(x: np.ndarray) -> list[int]:
    # Flatten x (which is list[list[int]]) to list[int]
    CityPriority = [int(item) for sublist in x for item in sublist]
    # Create a list of cities
    CityOrder = [i for i in range(len(Cities))]
    # Sort the cities based on the priority
    CityOrder = sorted(CityOrder, key=lambda c: CityPriority[c])
    # Append the first city to the end to complete the loop
    CityOrder.append(CityOrder[0])

    # update_graph(CityOrder)

    return CityOrder

def TotalDistance(city_order: list[int]) -> float:
    # Calculate the total distance of the route
    distance = 0
    for i in range(len(city_order) - 1):
        distance += Distance(Cities[city_order[i]], Cities[city_order[i + 1]])
    return distance

n_agents = 50
n_variables = len(Cities)
lower_bound = [0 for _ in range(n_variables)]
upper_bound = [100 for _ in range(n_variables)]

space = SearchSpace(n_agents, n_variables, lower_bound, upper_bound)
optimizer = WCA()
function = Function(lambda x: TotalDistance(ConvertPrioritiesToCityOrder(x)))

opt = Opytimizer(space, optimizer, function)

# opt.start(n_iterations=1000, callback=lambda x: print(f"Best result at epoch {x}: {opt.space.best_agent.fitness}"))
callback = Callback()
def on_iteration_end(i: int, o: Opytimizer):
    update_graph(ConvertPrioritiesToCityOrder(o.space.best_agent.position))
callback.on_iteration_end = on_iteration_end

opt.start(n_iterations=100, callbacks=[callback])

# Convert the solution to a list of cities indices
solution = ConvertPrioritiesToCityOrder(opt.space.best_agent.position)

import matplotlib.pyplot as plt
to_plot = [int(i) for i in solution]
plt.plot([Cities[i][0] for i in to_plot], [Cities[i][1] for i in to_plot], marker='o')
plt.show()
