# Pxlrace - a race between pixels on an X Windows screen

The starting line for the pixels is on the left edge of the X Windows
screen.  The pixels race against each other to reach the right edge
of the screen.  The winner and winning time is displayed after each
race.

The race is slowed down by nanosleep, to make it easier to watch the
racers.

The number of pixels to race is an optional parameter.

Example:

pxlrace 100

In this example, 100 pixels race across the screen.

The default number of pixel racers depends on the size of the screen.

See INSTALL for installation instructions.
