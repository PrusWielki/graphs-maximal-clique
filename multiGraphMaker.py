import sys
import random


def generate_symmetric_random_matrix(size,maxWeight):
    matrix = [[0 for _ in range(size)] for _ in range(size)]
    for i in range(size):
        for j in range(i + 1, size):
            createEdge =random.randint(0,1)
            value=0
            if createEdge == 1:
                value = random.randint(1, maxWeight)
            matrix[i][j] = value
            matrix[j][i] = value
    return matrix


def print_usage():
    print(
        "Usage: python script_name.py <number_of_graphs> <maxWeight> <default_size> [<size_of_graph_1> <size_of_graph_2> ...]"
    )


args = sys.argv[1:]


if len(args) < 3:
    print_usage()
    sys.exit(1)

num_graphs = int(args[0])
maxWeight  = int(args[1])
default_size = int(args[2])
sizes = [int(arg) for arg in args[3:]] + [default_size] * (num_graphs - len(args) + 3)

output_string = f"{num_graphs}\n"
for size in sizes[:num_graphs]:
    matrix = generate_symmetric_random_matrix(size, maxWeight)
    output_string += (
        f"{size}\n"
        + "\n".join(" ".join(str(cell) for cell in row) for row in matrix)
        + "\ninfo\n\n"
    )

filename = f"MultiGraph{num_graphs}_{maxWeight}_{default_size}.txt"
with open(filename, "w") as file:
    file.write(output_string)

print(f"Output written to {filename}")
