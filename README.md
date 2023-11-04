# Monkey Chess Engine

Monkey Chess Engine is a simple chess engine programmed in C that allows you to play chess and test your skills against a computer opponent. It's a fun and educational project for chess enthusiasts, programmers, and anyone interested in the game of chess.

## Features

- Full chess rules compliance, including castling, en passant, and pawn promotion.
- Alpha-beta pruning with basic evaluation functions for game tree searching.
- Command-line interface for playing chess and testing the engine.
- Easy-to-compile with a simple `make` command.

## Getting Started

To get started with Monkey Chess Engine, follow these simple steps:

1. Clone the repository to your local machine:

   ```bash
   git clone https://github.com/your-username/monkey-chess-engine.git
   ```

2. Navigate to the project directory:

   ```bash
   cd monkey-chess-engine
   ```

3. Compile the chess engine:

   ```bash
   make
   ```

4. Start a new game:

   ```bash
   ./build/monkey-chess-engine
   ```

5. Follow the on-screen instructions to play against the computer opponent.

## Usage

Monkey Chess Engine provides a basic command-line interface for playing chess. Here are some of the commands you can use during a game:

- `help`: Display the list of available commands.
- `board`: Display the current state of the chessboard.
- `move <from> <to>`: Make a move using algebraic notation (e.g., `e2 e4`).
- `new`: Start a new game.
- `quit`: Quit the game.

## Contributing

Contributions to Monkey Chess Engine are welcome! Whether you want to improve the engine's playing strength, enhance its features, or fix bugs, feel free to submit a pull request. Please make sure to follow the coding style and provide clear documentation for your changes.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

Monkey Chess Engine is based on the open-source [Stockfish](https://stockfishchess.org/) chess engine. We are grateful to the Stockfish team and the broader chess programming community for their contributions to the field of computer chess.

Have fun playing chess with Monkey Chess Engine, and feel free to share your experiences and improvements with the community!
