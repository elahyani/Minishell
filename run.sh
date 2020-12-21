#!/bin/bash
make $1 && ./minishell
# make $1 && valgrind --leak-check=full --show-leak-kinds=all ./minishell
