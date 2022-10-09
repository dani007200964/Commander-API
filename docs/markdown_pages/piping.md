@page piping Piping

@section what_is_piping What Is Piping?

By default, if you run a command and that command has some output, it will be printed
on the terminal screen. With a pipe, you can redirect the output of one command, to
the input of another one. It is called piping.

@section how_to_use_piping How To Use Piping?

To redirect the output from one command to another you have to use the '|' operator.
For example, you have to generate a sine value from an ADC sample. In this case, you
can use `analogRead 0 | sin`.

__Let's see how it works:__
1. Firstly the analogRead 0 command will be executed. It generates an ADC measurement
from channel 0.
2. Then the result is pushed into the pipe. Let's say the sample value was 171.
3. When the sin command gets parsed, the parser detects that there is some data
in the pipe, so it redirects it to the sin command as an argument.
4. The sin function gets executed with 171 value.
5. The result of the sin command will be printed on the output.

You can use as many pipes in one command as you want.

@section piped_command_with_arguments Piped Command With Arguments

What happens when you execute this: `analogRead 0 | cos 0`?

1. Firstly the analogRead 0 command will be executed. It generates an ADC measurement
from channel 0.
2. Then the result is pushed into the pipe. Lets say the sample value was 171.
3. When the cos command gets parsed, the parser detects that, there is some data
in the pipe, so it redirects it to the cos command as an argument. The specified 0
argument will be ignored.
4. The cos function gets executed with 171 value, __not with 0__.
5. The result of the sin command will be printed on the output.

@section error_during_pipin Error During Piping

What happens when a command generates an error in the middle of the pipe?

In this case, the command execution stops at the error. It is important to understand,
that the commands before the error will be executed. It is not a compiler, which means
it does not detect errors before execution.

There are two kinds of errors:
* Command parser error. It happens when you type a command name wrong, and the parser
can't locate it. In this scenario, the command execution stops immediately.
* Internal command error. It happens when you specify the arguments wrongly for a command.
In this way, the command usually prints an error message. It is important to understand,
that this message will be pushed into the pipe and it will be carried to the next command
in the pipe as the argument.
@warning Because of this, every command, that has arguments needs to be protected against wrong input!
