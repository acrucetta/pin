
# Pin

Pin allows you to save the most frequently used commands in your command line. 

Assume you use an EXPORT command to set env variables often in your shell. Pin allows you to call "pin list" to show a list of your pinned commands and selecting it to execute it from the list.

## Usage

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
