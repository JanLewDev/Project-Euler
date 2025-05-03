#!/usr/bin/env bash

# Declare answers for the problems
# Associative read-only array, requires Bash >= 4.0
declare -A -r answers=(
    ["p0001"]="233168"
    ["p0002"]="4613732"
    ["p0003"]="6857"
    ["p0004"]="906609"
    ["p0005"]="232792560"
    ["p0006"]="25164150"
    ["p0007"]="104743"
    ["p0008"]="23514624000"
    ["p0009"]="31875000"
    ["p0010"]="142913828922"
    ["p0016"]="1366"
    ["p0025"]="4782"
    ["p0036"]="872187"
    ["p0049"]="296962999629"
    ["p0050"]="997651"
    ["p0064"]="1322"
    ["p0080"]="40886"
    ["p0081"]="427337"
    ["p0090"]="1217"
    ["p0297"]="44043947822"
    ["p0872"]="2903144925319290239"
)

SCRIPT_DIR="$(dirname "$(realpath "$0")")"
cd $SCRIPT_DIR/..

# Compile and check the answer to each program
for file in p[0-9][0-9][0-9][0-9].cpp; do
    if [ -f "$file" ]; then
        binary=$(basename "$file" .cpp)
        make "$binary" >/dev/null 2>error

        if [ -s error ] && grep -q "error:|fatal error:" error; then
            echo -e "Error during compilation:\n$(cat error)"
            rm -f error
            exit 1
        fi

        start_time=$(date +%s.%N)
        output=$(./"$binary" 2>&1)
        exit_code=$?

        end_time=$(date +%s.%N)
        runtime=$(echo "$end_time - $start_time" | bc)

        if [ $exit_code -ne 0 ]; then
            echo -e "❌ \e[91mRE\e[39m $binary"
            echo -e "Output:\n$output"
            rm -f error
            exit 1
        fi

        # Check the answer
        expected="${answers[$binary]}"
        if [ -n "$expected" ]; then
            if [ "$output" == "$expected" ]; then
                echo -e "✅ \e[92mAC\e[39m $binary in $runtime seconds"
            else
                echo -e "❌ \e[91mWA\e[39m $binary in $runtime seconds"
                echo "Expected: $expected"
                echo "Output: $output"
                rm -f error
                exit 1
            fi
        fi
    fi
done

# Clean up
echo "Cleaning up..."
rm -f error
make clean
