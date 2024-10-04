#!/bin/bash

delay=${1:-0.1}

tput clear

indices=()
inp_art=$(cat)
for ((i = 0; i < ${#inp_art}; i++)); do
  next_char="${inp_art:$i:1}"
  if [[ "$next_char" != " " && "$next_char" != $'\n' ]]; then
    indices+=($i)
  fi
done
indices=($(printf "%s\n" "${indices[@]}" | shuf))

for index in "${indices[@]}"; do
  row=0; col=0
  for ((i = 0; i < index; i++)); do
    if [ "${inp_art:$i:1}" == $'\n' ]; then
      row=$((row + 1))
      col=0
    else
      col=$((col + 1))
    fi
  done

  tput cup $row $col
  echo -n "${inp_art:$index:1}"
  sleep "$delay"
done

tput cup $(tput lines) 0
