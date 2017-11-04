#!/bin/bash


while [[ $# -ne 0 ]]; do
  sed 's/^@.*$/&\n\\noindent\\makebox[\\linewidth]{\\rule{\\textwidth}{0.4pt}}/' $1
  sed 's/^<<.*>>=.*$/\\noindent\\makebox[\\linewidth]{\\rule{\\textwidth}{0.4pt}}\n&/' $1
  shift
done
