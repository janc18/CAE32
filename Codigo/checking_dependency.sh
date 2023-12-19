#!/bin/bash

echo -e "\e[1mDependency\t Status\e[0m"
echo -e "\t\t|---------"
for cmd in cmake gcc make; do 
  if ! command -v $cmd &> /dev/null; then
    echo -e "$cmd \t\t \e[31mNot installed\e[0m"
  else
    echo -e "$cmd \t\t \e[32mInstalled\e[0m"
  fi 
done
