import scipy
import matplotlib.pyplot as plot
from scipy import stats
import numpy as np

DEFECT = 5

def read():
    file = open("manufacturing_defects.txt", "r")
    data = []

    for line in file:
        row = []
        for i in line.split():
            if i.isdigit():
                row.append(int(i))
        data.append(row)
    
    return data

# counts defect for given defect_id
def count_defects(data, defect_id):
    total = 0

    for i in data:
        total += i[1:].count(defect_id)
        
    return total

#a
def print_table1(data):
    table = []

    for i in range(0, DEFECT):
        table.append(count_defects(data, i))
    
    print(table)
    return table

#b
def find_lambda(data, num_of_company, num_of_year):
    total = 0
    
    for r in data:
        for i in range(len(r) - 2):
            total += r[i+2]

    return total / (num_of_company * num_of_year)

#c
def estimate(table, mean, num_of_company, num_of_year):
    predicated_cases_poisson = []
    total = 0

    for i in table:
        total += i

    for i in range(len(table)):
        predicated_cases_poisson.append(total * scipy.stats.poisson.pmf(i, mean))

    return predicated_cases_poisson

def barplot(table, estimated_table):
    w = 0.1
    
    real_plt = plot.bar(np.arange(DEFECT), table, w, label = "Actual Cases")
    est_plt = plot.bar(np.arange(DEFECT) + w, estimated_table, w, label = "Predicated Cases")

    for i in range(0, DEFECT):
        real_plt[i].set_color('g')
        est_plt[i].set_color('r')

    plot.title("Actual vs Predicated Cases")
    plot.xlabel("# of defects")
    plot.ylabel("# of cases")
    plot.xticks(np.arange(DEFECT) + w/2, [i for i in range(0, DEFECT)])
    plot.legend(loc = "best")
    plot.show()

data = read()
num_of_company = len(data[0]) - 2 # -2 for first(row number) and second(year) column
num_of_year = len(data)

# print table
table = print_table1(data)

# find lambda
mean = find_lambda(data, num_of_company, num_of_year)
print(mean)

# find estimations
estimated_table = estimate(table, mean, num_of_company, num_of_year)
print(estimated_table)

# draw barplot
barplot(table, estimated_table)
