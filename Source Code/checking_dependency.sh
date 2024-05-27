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

# Checking if some library are installed with pkg-config 
for pkg_cmd in gtk3+-3.0 libevdev-dev; do
  if pkg-config --exist $pkg_cmd; then
    echo -e "$pkg_cmd\t\e[31m Not installed\e[0m"
  else
    echo -e "$pkg_cmd\t\e[32m Installed\e[0m"
  fi
  done
