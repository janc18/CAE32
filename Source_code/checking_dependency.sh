#!/bin/bash
printf "\e[1m%-20s %-15s\e[0m\n" "Dependency" "Status"
printf "%-20s %-15s\n" "--------------------" "---------------"

for cmd in cmake gcc make pkgconf gtester; do 
  if ! command -v $cmd &> /dev/null; then
    printf "%-20s \e[31m%-15s\e[0m\n" "$cmd" "Not installed"
    Packages_not_installed+=($cmd)
  else
    printf "%-20s \e[32m%-15s\e[0m\n" "$cmd" "Installed"
    Packages_installed+=($cmd)
  fi 
done

for pkg_cmd in gtk3+-3.0 libevdev-dev; do
  if ! pkg-config --exists $pkg_cmd; then
    printf "%-20s \e[32m%-15s\e[0m\n" "$pkg_cmd" "Installed"
  else
    printf "%-20s \e[31m%-15s\e[0m\n" "$pkg_cmd" "Not installed"
  fi
done
