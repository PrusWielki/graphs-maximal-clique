gcc -m64 -Wall -Wextra -o main main.c

echo "Running ./input/product_example.txt"

main.exe ./input/product_example.txt

ren output.txt output-main-product_example.txt

echo "Running ./input/product_example.txt ./input/product_example.txt"

main.exe ./input/product_example.txt ./input/product_example.txt

ren output.txt output-main-product_example_example.txt

echo "Running ./input/product_example.txt ./input/product_example.txt ./input/product_example.txt"

main.exe ./input/product_example.txt ./input/product_example.txt ./input/product_example.txt

ren output.txt output-main-product_example_example_example.txt

echo "Running ./input/product_example.txt ./input/example.txt ./input/example.txt"

main.exe ./input/product_example.txt ./input/example.txt ./input/example.txt

ren output.txt output-main-product_example_example2_example2.txt

echo "Running ./input/directedGraph.txt"

main.exe ./input/directedGraph.txt

ren output.txt output-main-directed.txt

echo "Running ./input/product_example.txt ./input/product_example.txt ./input/product_example.txt ./input/product_example.txt"

main.exe ./input/product_example.txt ./input/product_example.txt ./input/product_example.txt ./input/product_example.txt

ren output.txt output-main-product_example_example_example_example.txt



