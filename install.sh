#!/bin/sh
set -eu

cd "build"

clang -march=native main.c -O3 -o main
./main -rbld

case ":$PATH:" in
	*":$HOME/.local/bin:"*) ;;
	*)
		printf '\nexport PATH="$HOME/.local/bin:$PATH"\n' >> "$HOME/.profile"
		export PATH="$HOME/.local/bin:$PATH"
		echo 'Added ~/.local/bin to ~/.profile'
		;;
esac

echo "stormc installed at $HOME/.local/bin/stormc"
echo "Current shell can use it now if this script was sourced; otherwise open a new shell or run:"
echo "  export PATH=\"\$HOME/.local/bin:\$PATH\""
