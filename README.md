# 🦊 What is Minishell?

Minishell is a small **Unix Shell** implementation designed to replicate basic shell functionalities. </br></br>
It **reads** user input, **tokenizes** and **parses** commands with proper handling of ***quotes***, ***pipes***, ***redirections***, and ***environment variable expansions***. </br></br>
Finally it executes those commands similarly to how a standard shell would.

### Overview:
- **Lexer:** Tokenizes the input string and stores the tokens in the lexer structure
  > [`tokenizer`](https://github.com/flmarsou/minishell/blob/main/src/parser/tokenizer.c) Processes the given input string character by character, identifying different types of enum tokens and stores them in the provided lexer structure for further processing.
  - > **SEPARATOR** `Whitespace`
  - > **WORD** `Others`
  - > **SINGLE_QUOTE** `'`
  - > **DOUBLE_QUOTE** `"`
  - > **PIPE** `|`
  - > **INPUT_REDIRECT** `<`
  - > **OUTPUT_REDIRECT** `>`
  - > **HEREDOC** `<<`
  - > **APPEND_REDIRECT** `>>`
  - > **DOLLAR** `$`
  - > **NA_VALUE** `Nullified token`
  - > **END** `Terminator`

  > [`count_token`](https://githubcom/flmarsou/minishell/blob/main/src/parser/count_tokens.c) Counts the number of tokens in a given string for allocation.

- **Parser:** Parses the tokens from the lexer and builds the parser structure in the order below
  > [`handle_quotes_error`](https://github.com/flmarsou/minishell/blob/main/src/parser/handle_quotes_error.c) Checks if every opening quote has a matching closing quote.

  > [`handle_quotes`](https://github.com/flmarsou/minishell/blob/main/src/parser/handle_quotes.c) Processes tokens within quotes, converting them into WORD tokens, except for DOLLAR tokens inside SINGLE_QUOTE quotes which are handled later.

  > [`handle_pipes_error`](https://github.com/flmarsou/minishell/blob/main/src/parser/handle_pipes_error.c) Checks if every PIPE tokens have a WORD token before and after themselves.

  > [`handle_dollars`](https://github.com/flmarsou/minishell/blob/main/src/parser/handle_dollars.c) Expands dollar-prefixed variables with the following rules:
  - > **Dollar after a HEREDOC:** *No expansion is performed*
  - > **Dollar followed by a WORD beginning with a digit:** *No expansion occurs, and the digit is removed*
  - > **Dollar followed by a SEPARATOR:** *The DOLLAR token is turned into a WORD token*
  - > **Dollar followed by a WORD beginning with '?':** *The question mark is expanded to the exit status*
  - > **Dollar followed by a WORD:** *Attempts to expand the variable*

  > [`handle_redir_error`](https://github.com/flmarsou/minishell/blob/main/src/parser/handle_quotes_error.c) Checks if every opening quote has a matching closing quote.

  > [`handle_words`](https://github.com/flmarsou/minishell/blob/main/src/parser/handle_words.c) Merges WORD tokens within quotes and across token boundaries.
  - > Merges multiple consecutive WORD tokens inside quotes into one token.
  - > Merges adjacent WORD tokens that are not separated by SEPARATOR or redirections.

  > [`handle_redir`](https://github.com/flmarsou/minishell/blob/main/src/parser/handle_redir.c) Processes redirection tokens and organizes them within the parser. Redirection tokens (e.g., >, <) are stored in the parser structure, grouping them according to their respective pipe group, nullifying the tokens once processed.

  > [`handle_command`](https://github.com/flmarsou/minishell/blob/main/src/parser/handle_command.c) Processes command tokens and organizes them within the parser. WORD tokens are stored in the parser structure, grouping them according to their respective pipe group.

- **Execution:** ???
  > [`exec`](https://github.com/flmarsou/minishell/blob/main/src/execution/exec.c) Executes commands, managing process creation.

  > [`heredoc`](https://github.com/flmarsou/minishell/blob/main/src/execution/heredoc.c), [`handle_heredoc`](https://github.com/flmarsou/minishell/blob/main/src/execution/handle_heredoc.c), [`heredoc_signal`](https://github.com/flmarsou/minishell/blob/main/src/execution/heredoc_signal.c), [`handle_child_signals`](https://github.com/flmarsou/minishell/blob/main/src/execution/handle_child_signals.c) Processes heredoc inputs, allowing multi-line input until a delimiter.

  > [`handle_pipes`](https://github.com/flmarsou/minishell/blob/main/src/execution/handle_pipes.c) Sets up and manages inter-process communication through pipes.

  > [`handle_redirs`](https://github.com/flmarsou/minishell/blob/main/src/execution/handle_redirs.c) Handles input and output redirections for commands.

- **Builtins:** Internal commands implemented directly within Minishell
  > [`cd`](https://github.com/flmarsou/minishell/blob/main/src/builtins/ft_cd.c) Changes the current working directory.

  > [`echo`](https://github.com/flmarsou/minishell/blob/main/src/builtins/ft_cd.c) Prints arguments to the standard output.

  > [`env`](https://github.com/flmarsou/minishell/blob/main/src/builtins/ft_cd.c) Displays the current environment variables.

  > [`exit`](https://github.com/flmarsou/minishell/blob/main/src/builtins/ft_cd.c) Exits the shell.

  > [`export`](https://github.com/flmarsou/minishell/blob/main/src/builtins/ft_cd.c) Sets or modifies environment variables.

  > [`pwd`](https://github.com/flmarsou/minishell/blob/main/src/builtins/ft_cd.c) Prints the current working directory.

  > [`unset`](https://github.com/flmarsou/minishell/blob/main/src/builtins/ft_cd.c) Removes environment variables.

  > [`execve`](https://github.com/flmarsou/minishell/blob/main/src/builtins/ft_cd.c) Executes a binary *(command!)*.

# ⚒️ Compilation

1. Run `make` to compile the program.
2. Run `make re` to recompile everything.
3. Run `./minishell` to execute the program.

# 🧼 Cleaning

1. Run `make clean` to remove every object files.
2. Run `make fclean` to remove every object files, including the executable.
