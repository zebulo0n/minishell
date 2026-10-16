*This project has been created as part of the 42 curriculum by zoeschne.*

# minishell

A minimal Bash-like shell written in C.

## Features

- Prompt with history
- Pipes, redirections (`<`, `>`, `>>`, `<<`)
- Environment variable expansion and `$?`
- Quotes handling
- Builtins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- `ctrl-C`, `ctrl-D`, `ctrl-\` behave like Bash

## Usage

```sh
make
./minishell
```

Requires the `readline` library.

