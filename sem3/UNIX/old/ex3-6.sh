#!/bin/bash
if cmp -s $1 $2; then
    printf 'The file "%s" is the same as "%s"\n' "$1" "$2"
else
    printf 'The file "%s" is different from "%s"\n' "$1" "$2"
fi
