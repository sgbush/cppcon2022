# Using an arena allocator
## PC example
Run the `build_run.sh` script.  It will compile and run the PC example.  The example will print some allocation statistics.  Now, change the value of the boolean `use_arena` to see how the statistics change.
## MCU example
This assumes an STM32L476 Nucleo board is attached to the PC, and is programmed via a Segger JLink (instead of the on board ST-Link, which I find hard to control via command line).  This is kind of a chore to set up, so you may just want to stick with the PC example above, which will pretty do the same thing.