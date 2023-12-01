gcc -m64 -Wall -Wextra -o main adjlist.c

echo "Running ./input/product_example.txt"

main.exe ./input/product_example.txt

ren output.txt output-adjlist-product_example.txt

echo "Running ./input/product_example.txt ./input/product_example.txt"

main.exe ./input/product_example.txt ./input/product_example.txt

ren output.txt output-adjlist-product_example_example.txt

echo "Running ./input/product_example.txt ./input/product_example.txt ./input/product_example.txt"

main.exe ./input/product_example.txt ./input/product_example.txt ./input/product_example.txt

ren output.txt output-adjlist-product_example_example_example.txt

echo "Running ./input/product_example.txt ./input/product_example.txt ./input/product_example.txt ./input/product_example.txt"

main.exe ./input/product_example.txt ./input/product_example.txt ./input/product_example.txt ./input/product_example.txt

ren output.txt output-adjlist-product_example_example_example_example.txt

echo "Running ./input/directedGraph.txt"

main.exe ./input/directedGraph.txt

ren output.txt output-adjlist-directed.txt

