#!/bin/bash

echo -e "\e[1mDependency\t Status\e[0m"
echo -e "\t\t|---------"
for cmd in cmake gcc make pkgconf; do 
  if ! command -v $cmd &> /dev/null; then
    echo -e "$cmd \t\t \e[31mNot installed\e[0m"
    Packages_not_installed+=($cmd)
    exit 1
  else
    echo -e "$cmd \t\t \e[32mInstalled\e[0m"
    Packages_installed+=($cmd)
  fi 
done

# Checking if the gtk3 library is installed 
if pkg-config --exist gtk+-3.0; then
  echo -e "gtk3 \t\t \e[32mInstalled\e[0m"
else
  echo -e "gtk3 \t\t \e[31mNot installed\e[0m"
fi
