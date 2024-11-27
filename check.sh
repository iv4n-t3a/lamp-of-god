# !/bin/sh

find src -name "*.cpp" -o -name "*.hpp" -o -name "*.h" -type f | xargs clang-tidy -extra-arg=-std=c++20 --quiet

if [[ ! $? -eq 0 ]]
then
  echo "Проверка clang-tidy не пройдена"
    exit 1
  fi
echo "Clang-tidy done"

echo "Begin clang-format"
find src -name "*.cpp" -o -name "*.hpp" -o -name "*.h" -type f | xargs clang-format -i
find src -name "*.cpp" -o -name "*.hpp" -o -name "*.h" -type f | xargs git diff --ignore-submodules > diff

if [[ -s diff ]]
then
  echo "Проверка clang-format не пройдена"
  find src -name "*.cpp" -o -name "*.hpp" -o -name "*.h" -type f | xargs git diff --ignore-submodules --color
  exit 1
fi
echo "Clang-format done"
