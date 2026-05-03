#!/bin/sh
set -eu

  cd build

  if ! command -v clang >/dev/null 2>&1; then
      echo "clang not found" >&2
      exit 1
  fi

  clang -mavx2 main.c -O3 -o main
  ./main -rbld

  path_line='export PATH="$HOME/.local/bin:$PATH"'

  touch "$HOME/.bashrc"
  if ! grep -qxF "$path_line" "$HOME/.bashrc"; then
      printf '\n# stormc\n%s\n' "$path_line" >> "$HOME/.bashrc"
  fi

  touch "$HOME/.profile"
  if ! grep -qxF "$path_line" "$HOME/.profile"; then
      printf '\n# stormc\n%s\n' "$path_line" >> "$HOME/.profile"
  fi

  echo "stormc installed at $HOME/.local/bin/stormc"
  echo "For this terminal, run:"
  echo "  export PATH=\"\$HOME/.local/bin:\$PATH\""
