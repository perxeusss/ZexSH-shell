# ZexSH Shell

A custom Unix shell implementation written in C, designed to provide a lightweight and efficient command-line interface.

## 📋 Overview

ZexSH is a simple yet functional shell that interprets and executes user commands. Built from scratch in C, it demonstrates core shell functionalities including command parsing, execution, and built-in command support.

## ✨ Features

- **Command Execution**: Execute external programs and system commands
- **Built-in Commands**: Support for essential shell built-ins
- **Input Parsing**: Robust command-line input parsing and tokenization
- **Process Management**: Efficient process creation and management
- **Custom Prompt**: Interactive command-line interface

## 🛠️ Technologies Used

- **Language**: C
- **Build System**: Makefile
- **Platform**: Unix/Linux

## 📂 Project Structure

```
ZexSH-shell/
├── main.c           # Entry point and main shell loop
├── input_parser.c   # Command-line input parsing logic
├── executor.c       # Command execution engine
├── builtins.c       # Built-in command implementations
├── helpers.c        # Utility and helper functions
├── zexsh.h          # Header file with declarations
├── Makefile         # Build configuration
└── readme.md        # Project documentation
```

## 🚀 Installation

### Prerequisites

- GCC compiler or compatible C compiler
- Make utility
- Unix-like operating system (Linux, macOS, BSD)

### Build Instructions

1. **Clone the repository**
   ```bash
   git clone https://github.com/perxeusss/ZexSH-shell.git
   cd ZexSH-shell
   ```

2. **Compile the shell**
   ```bash
   make
   ```

3. **Run ZexSH**
   ```bash
   ./zexsh
   ```

## 💡 Usage

### Starting the Shell

Simply run the compiled binary:
```bash
./zexsh
```

### Basic Commands

Once inside ZexSH, you can execute standard Unix commands:
```bash
ls -la
pwd
cd /path/to/directory
echo "Hello, World!"
```

### Built-in Commands

ZexSH includes several built-in commands for enhanced functionality. Check the `builtins.c` file for the complete list.

### Exiting the Shell

To exit ZexSH:
```bash
exit
```

## 🔧 Development

### Rebuilding

To rebuild after making changes:
```bash
make clean
make
```

### Project Components

- **`main.c`**: Contains the main loop that reads, parses, and executes commands
- **`input_parser.c`**: Handles tokenization and parsing of user input
- **`executor.c`**: Manages command execution and process creation
- **`builtins.c`**: Implements shell built-in commands
- **`helpers.c`**: Provides utility functions used across the project
- **`zexsh.h`**: Central header file with function prototypes and structure definitions

## 📝 Contributing

Contributions are welcome! Here's how you can help:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

### Development Guidelines

- Follow the existing code style
- Add comments for complex logic
- Test your changes thoroughly
- Update documentation as needed

## 🐛 Known Issues

- Check the [Issues](https://github.com/perxeusss/ZexSH-shell/issues) page for current bugs and feature requests

## 📄 License

This project is open source. Please check the repository for license information.

## 👤 Author

**perxeusss**
- GitHub: [@perxeusss](https://github.com/perxeusss)

## 🙏 Acknowledgments

- Inspired by classic Unix shells (bash, sh, zsh)
- Built as a learning project to understand shell internals

## 📚 Resources

For those interested in learning more about shell implementation:
- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/)
- [Advanced Programming in the UNIX Environment](https://www.apuebook.com/)
- [Writing Your Own Shell](https://brennan.io/2015/01/16/write-a-shell-in-c/)

---

**Note**: ZexSH is an educational project and may not include all features of production shells. Use it for learning purposes and experimentation.