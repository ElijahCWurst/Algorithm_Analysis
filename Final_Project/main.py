import numpy as np

def main():
    tspGraph = np.array([[0, 29, 20, 21, 16], 
                         [29, 0, 15, 29, 28], 
                         [20, 15, 0, 18, 27], 
                         [21, 29, 18, 0, 26], 
                         [16, 28, 27, 26, 0]])

    print(tspGraph)




def init_generator(pop_size, num_variables, min_val, max_val):
    return np.random.uniform(min_val, max_val, (pop_size, num_variables))

def sorting_pop(pop, obj_func, minimizing):
    results = np.apply_along_axis(obj_func, 1, pop)
    indeces = np.argsort(results)
    if not minimizing:
        indeces = indeces[::-1]
    return pop[indeces]

def involved_ranindrop_counter(pop, obj_func, R, S):
    costs = np.apply_along_axis(obj_func, 1, pop[:R+1])
    sum_costs = np.sum
    involved_raindrops = np.round(S*np.abs(costs/sum_costs)).astype(int)
    involved_raindrops = np.insert(involved_raindrops, 0, 0)
    return np.comsum(involved_raindrops)

def update_positions(pop, obj_func, R, S, C):
    involved_raindrops = involved_ranindrop_counter(pop, obj_func, R, S)
    for i in range (R+1):
        pop_reverse = pop[::-1]
        low = involved_raindrops[i]
        up = involved_raindrops[i+1]
        rand = np.random.uniform(0, 1, (up-low)).reshape(-1, 1)
        x = rand * C * (pop[i]-pop_reverse[low:up])
        pop_reverse[low:up] = (pop_reverse[low:up] + x)
    return pop_reverse[::-1]

def evaporation(pop, sea_threshold, min_val, max_val, search_coef, constrained):
    dist_values = np.sqrt(np.sum((pop[0]-pop)**2, 1))
    where = (dist_values < sea_threshold).flat
    replacing_index = np.array(where)[1:]
    if constrained:
        replacing_values = pop[0] + np.random.normal(0, np.sqrt(search_coef), size=pop.shape)
    else:
        replacing_values = np.random.uniform(min_val, max_val, pop.shape)
    pop[replacing_index] = replacing_values[replacing_index]
    return pop

# R is the total number of rivers
# S is the total number of streams
def water_cycle_algorithm(min_val, max_val, num_variables, pop_size, R, C, sea_threshold, obj_func, iteration, minimizing, search_coef=0.1, constrained=False, full_results=False):
    NFE = np.zeros(iteration)
    results = np.zeros(iteration)
    NFE_values = 0
    pop = init_generator(pop_size, num_variables, min_val, max_val)
    pop = sorting_pop(pop, obj_func, minimizing)
    NFE_values += pop_size
    S = pop_size-R-1
    for i in range (iteration):
        pop = update_positions(pop, obj_func, R, S, C)
        pop = sorting_pop(pop, obj_func, minimizing)
        pop = evaporation(pop, sea_threshold, min_val, max_val, search_coef, constrained)
        pop = sorting_pop(pop, obj_func, minimizing)
        sea_threshold *= (1-1/iteration)
        NFE_values += pop_size
        NFE[i] = NFE_values
        results[i] = obj_func(pop[0])
    if not full_results:
        return pop[0], obj_func(pop[0])
    else:
        return pop[0], obj_func(pop[0]), results, NFE
    

if __name__ == "__main__":
    main()