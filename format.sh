#!/usr/bin/env bash

echo "=== Форматирование всех файлов в src с помощью clang-format ==="

find src -type f \( -name "*.cpp" -o -name "*.hpp" -o -name "*.h" \) | while read -r file; do
    echo "Форматирую: $file"
    clang-format -i "$file"
done

echo "=== Готово! ==="