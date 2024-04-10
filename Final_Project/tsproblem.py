#!/usr/bin/env python
# Created by "Thieu" at 13:57, 07/11/2023 ----------%                                                                               
#       Email: nguyenthieu2102@gmail.com            %                                                    
#       Github: https://github.com/thieu1995        %                         
# --------------------------------------------------%

# In the context of the Mealpy for the Traveling Salesman Problem (TSP), a solution is a possible route that
# represents a tour of visiting all the cities exactly once and returning to the starting city. The solution is typically
# represented as a permutation of the cities, where each city appears exactly once in the permutation.

# For example, let's consider a TSP instance with 5 cities labeled as A, B, C, D, and E. A possible solution could be
# represented as the permutation [A, B, D, E, C], which indicates the order in which the cities are visited. This solution
# suggests that the tour starts at city A, then moves to city B, then D, E, and finally C before returning to city A.


import numpy as np
from mealpy import PermutationVar, WCA, Problem
# from opytimizer.optimizers.science import WCA

# # # Define the positions of the cities
# city_positions = np.array([[60, 200], [180, 200], [80, 180], [140, 180], [20, 160],
#                            [100, 160], [200, 160], [140, 140], [40, 120], [100, 120],
#                            [180, 100], [60, 80], [120, 80], [180, 60], [20, 40],
#                            [100, 40], [200, 40], [20, 20], [60, 20], [160, 20]])
# city_positions = np.array([[25, 25], [90, 100], [25, 175], [175, 175], [175, 25], [90, 50], [50, 150], [50, 50], [50, 90]])
# city_positions = np.array([[100, 100], [150, 50], [50, 50], [50, 150], [75, 125], [125, 75], [125, 125], [150, 150]])

city_positions = np.array([
    [156, 89],
    [32, 174],
    [105, 40],
    [68, 116],
    [187, 61],
    [83, 173],
    [21, 97],
    [145, 32],
    [198, 112]
])

import random
# city_positions = np.array([[random.randint(0, 200), random.randint(0, 200)] for i in range(20)])
num_cities = len(city_positions)
data = {
    "city_positions": city_positions,
    "num_cities": num_cities,
}

class TspProblem(Problem):
    def __init__(self, bounds=None, minmax="min", data=None, **kwargs):
        self.data = data
        super().__init__(bounds, minmax, **kwargs)

    @staticmethod
    def calculate_distance(city_a, city_b):
        # Calculate Euclidean distance between two cities
        return np.linalg.norm(city_a - city_b)

    @staticmethod
    def calculate_total_distance(route, city_positions):
        # Calculate total distance of a route
        total_distance = 0
        num_cities = len(route)
        for idx in range(num_cities):
            current_city = route[idx]
            next_city = route[(idx + 1) % num_cities]  # Wrap around to the first city
            total_distance += TspProblem.calculate_distance(city_positions[current_city], city_positions[next_city])
        return total_distance

    def obj_func(self, x):
        x_decoded = self.decode_solution(x)
        route = x_decoded["per_var"]
        fitness = self.calculate_total_distance(route, self.data["city_positions"])
        return fitness


bounds = PermutationVar(valid_set=list(range(0, num_cities)), name="per_var")
problem = TspProblem(bounds=bounds, minmax="min", data=data)

model = WCA.OriginalWCA(epoch=500, pop_size=200, nsr = 10, wc = 2.0, dmax = 1e-6)
model.solve(problem)

print(f"Best agent: {model.g_best}")                    # Encoded solution
print(f"Best solution: {model.g_best.solution}")        # Encoded solution
print(f"Best fitness: {model.g_best.target.fitness}")
print(f"Best real scheduling: {model.problem.decode_solution(model.g_best.solution)}")      # Decoded (Real) solution

import matplotlib.pyplot as plt

to_plot = [int(i) for i in list(model.g_best.solution) + [model.g_best.solution[0]]]
plt.plot([city_positions[i][0] for i in to_plot], [city_positions[i][1] for i in to_plot], marker='o')
plt.show()

