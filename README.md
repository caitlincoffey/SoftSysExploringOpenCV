# SoftSysGarbageEaters: A Simple Virtual Machine Implementation

*Zoe M., Gati A., Navi B., Caitlin C.*

**SoftSysGarbageEaters** is a LC-3 virtual machine that can run .obj files on Linux/Unix systems. Note that the virtual machine ***is not*** compatible with Windows due to operating system constraints.

## What is LC-3?

Little Computer 3 (LC-3) is a reduced instruction set computer (RISC), meaning its architecture uses a small number of optimized instructions to complete tasks rather than a larger set of specialized instructions as is the standard for modern personal computers.

LC-3 uses a simplified instruction set in order to introduce computer architecture concepts to students. The LC-3 instruction set consists of only 15 instructions and uses a simplified memory system of 10 registers. It is not practical for industrial use, but it is a great way to learn introductory computer architecture concepts.

## How to Set Up the Virtual Machine

To set up the virtual machine, you should do the following:

- Clone the repository by running `git clone[https://github.com/caitlincoffey/SoftSysGarbageEaters.git](https://github.com/caitlincoffey/SoftSysGarbageEaters.git)` in the terminal
- Cd into `SoftSysGarbageEaters`
- Run `make all` to get the executable file to start the virtual machine
- Last but not least, run `./GarbageEater <filename.obj`> to use the virtual machine.

Our LC-3 virtual machine runs `.obj` files on Linux/Unix platforms. We have some example files, `2048.obj` and `rogue.obj` if you would like to run these.

### Dependencies

To run the LC-3 virtual machine, you will need the following:

- `gcc`, the GNU Compiler
- `git`, a free and open source distributed version control system

