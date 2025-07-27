# rsh - A Simple C Shell

A minimal shell implementation in C, supporting basic built-in commands and external program execution.

## Features

- **Prompt**: Displays a `$` prompt for user input.
- **Built-in commands**:
  - `exit [code]`: Exit the shell with an optional exit code.
  - `echo [args...]`: Print arguments to the terminal.
  - `type [command]`: Identify if a command is a shell builtin or an external executable.
- **External commands**: Runs programs found in your system's `PATH`.

## Usage

1. **Clone the repository:**

   ```sh
   git clone https://github.com/ronitrajfr/rsh.git
   cd rsh
   ```

2. **Build:**

   ```sh
   gcc -o rsh src/main.c
   ```

3. **Run:**

   ```sh
   ./rsh
   ```

4. **Example session:**

   ```sh
   $ echo Hello World
   Hello World
   $ type echo
   echo is a shell builtin
   $ type ls
   ls is /bin/ls
   $ exit 0
   ```

## Notes

- Only basic argument parsing is supported (no quotes, pipes, or redirection).
- Maximum 20 arguments per command.
- The shell is for educational purposes and does not implement advanced shell features.

## License

See [LICENSE](LICENSE).
