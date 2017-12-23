# zmessage
Multi-line messages with whole words shifts.

# Usage
Just include it.

# Functions
This library provides only one function with can be useful in [some cases](#5). Some examples of usage can be found [here](#6).

##### ZMsg_GetMessages(message[], array[][], const lines = sizeof(array), const line_size = sizeof(array[]))
> * **Parameters:**
>   * `message[]`: The original message which should be splitted.
>   * `array[][]`: The array which stores splitted strings.
>   * `lines`: The number of the strings which can be stored in `array`.
>   * `line_size`: The number of the symbols which can be stored in one `array` string.
> * **Return values:**
>   * The number of the lines

# Directives

Directive | Default value | Can be redefined | Note
----------|---------------|------------------|------
ZMSG_MAX_CHAT_LENGTH | MAX_CHATBUBBLE_LENGTH | yes |
ZMSG_MAX_PLAYER_CHAT_LENGTH | (MAX_CHATBUBBLE_LENGTH / 2) | yes |
ZMSG_SEPARATORS_LIST | ' ' | yes | Used in `case` statement
ZMSG_HYPHEN_END | " ¬" | yes |
ZMSG_HYPHEN_START | "» " | yes |

# Screenshot

![example](https://user-images.githubusercontent.com/1020099/31858686-a297fb1e-b706-11e7-9987-64f996a1b1c6.png)
