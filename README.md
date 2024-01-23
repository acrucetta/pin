
# pin - tag your most used commands

Have you ever tried to run a command but forgot where it was in your history? Too tired to search? 

Pin allows you to save the most frequently used commands in your command line. 

By calling `pin add '<your command>'` you can store your most frequently used commands into a simple text file saved in your machine. 

To run them simply call `pin run <command id>` and call the command whenever you need it. 

Don't remember the ID? call `pin ls` to show the list of saved commands.

## Usage

### Building from Source

Clone the repository or download the source code.

```
git clone acrucetta/pin
```

Navigate to the source directory.

Compile the code:
```gcc -o pin main.c```

(Optional) Move the compiled executable to a directory in your PATH for global access:
bash
```
mv pin /usr/local/bin/
```

### Getting Started

Run the tool using the command:
```
pin
```
This initializes the configuration files in your `~/.config/pin` directory.

### Listing Commands
- To list all stored commands:
  ```
  pin ls
  ```
  **Example:**
  ```
  $ pin ls
  0: ls -la
  1: echo Hello World
  ```

### Adding a Command
- To add a new command:
  ```
  pin add "<command>"
  ```
  Replace `<command>` with the actual command you want to store.

  **Example:**
  ```
  $ pin add "git status"
  Successfully added command git status
  ```

### Removing a Command
- To remove a command by its ID:
  ```
  pin rm <id>
  ```
  Replace `<id>` with the numerical ID of the command.

  **Example:**
  ```
  $ pin rm 1
  Successfully removed command 1
  ```

### Running a Command
- To run a stored command by its ID:
  ```
  pin run <id>
  ```
  Replace `<id>` with the numerical ID of the command.

  **Example:**
  ```
  $ pin run 0
  (output from 'ls -la' command)
  ```
