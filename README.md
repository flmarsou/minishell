# 🦊 What is Minishell?

**Minishell** is ... <br><br>
...

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
  - > **DOLLAR** `-`
  - > **NA_VALUE** `Nullified token`

  > [`count_token`](https://githubcom/flmarsou/minishell/blob/main/src/parser/count_tokens.c) Counts the number of tokens in a given string for allocation.

- **Parser:** Parses the tokens from the lexer and builds the parser structure in the order below
  > [`handle_quotes_error`](https://github.com/flmarsou/minishell/blob/main/src/parser/handle_quotes_error.c) Checks if every opening quote has a matching closing quote.

  > [`handle_quotes`](https://github.com/flmarsou/minishell/blob/main/src/parser/handle_quotes.c) Processes tokens within quotes, converting them into WORD tokens, except for DOLLAR tokens inside SINGLE_QUOTE quotes which are handled later.

  > [`handle_pipes_error`](https://github.com/flmarsou/minishell/blob/main/src/parser/handle_pipes_error.c) Checks if every PIPE tokens have a WORD token before and after themselves.

  > [`handle_dollars`](https://github.com/flmarsou/minishell/blob/main/src/parser/handle_dollars.c) Expands dollar-prefixed variables with the following rules:
  - > **Dollar after a HEREDOC:** *No expansion is performed*
  - > **Dollar followed by a WORD beginning with a digit:** *No expansion occurs, and the digit is removed*
  - > **Dollar followed by a WORD beginning with a digit:** *The DOLLAR token is turned into a WORD token*
  - > **Dollar followed by a WORD beginning with '?':** *The question mark is expanded to the exit status*
  - > **Dollar followed by a WORD:** *Attempts to expand the variable*

  > [`handle_redir_error`](https://github.com/flmarsou/minishell/blob/main/src/parser/handle_quotes_error.c) Checks if every opening quote has a matching closing quote.

  > [`handle_words`](https://github.com/flmarsou/minishell/blob/main/src/parser/handle_words.c) Merges WORD tokens within quotes and across token boundaries.
  - > Merges multiple consecutive WORD tokens inside quotes into one token.
  - > Merges adjacent WORD tokens that are not separated by SEPARATOR or redirections.

  > [`handle_redir`](https://github.com/flmarsou/minishell/blob/main/src/parser/handle_redir.c) Processes redirection tokens and organizes them within the parser. Redirection tokens (e.g., >, <) are stored in the parser structure, grouping them according to their respective pipe group, nullifying the tokens once processed.

  > [`handle_command`](https://github.com/flmarsou/minishell/blob/main/src/parser/handle_command.c) Processes command tokens and organizes them within the parser. WORD tokens are stored in the parser structure, grouping them according to their respective pipe group.

# ⚒️ Compilation

1. Run `make` to compile the program.
2. Run `make re` to recompile everything.
3. Run `./minishell` to execute the program.

# 🧼 Cleaning

1. Run `make clean` to remove every object files.
2. Run `make fclean` to remove every object files, including the executable.

# ✨ Summary

|                                                       |                              |
| ----------------------------------------------------- | ---------------------------- |
| Program name                                          | minishell                    |
| Turn in files                                         | Makefile, *.h, *.c           |
| Makefile                                              | NAME, all, clean, fclean, re |
| Arguments                                             |                              |
| External functs.                                      | readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs |
| [Libft](https://github.com/flmarsou/libft) authorized | Yes |
| Description                                           | Write a shell.               |
