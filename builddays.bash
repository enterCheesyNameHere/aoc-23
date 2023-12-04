#!/bin/bash
DAY=1
while [ $DAY -le 25 ]; do
  DAYDIR="$PWD/$DAY"
  if [ -d "$DAYDIR" ]; then
    g++ -o "$DAYDIR/bin/day$DAY" "$DAYDIR/day$DAY.cpp"
  fi
  DAY=$((DAY+1))
done
