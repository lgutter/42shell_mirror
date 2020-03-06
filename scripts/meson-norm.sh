#!/bin/sh
cd "$(dirname "$0")/.." || exit 1
! norminette "$@" $(find inc -name "*.h") | tee /dev/stderr | grep -q Error
