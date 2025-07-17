# attrsim

This program simulates character attribute initialization for a chosen
role and race, and calculates the means and standard deviations.  It
was written for the purpose of filling in the data in the role table
at https://nethackwiki.com/wiki/Role.

## Compiling

`make` should build `attrsim36` (for NetHack 3.6 and prior versions)
and `attrsim37` (for NetHack 3.7).  3.7 fixes an off-by-one error,
which was discovered through the use of this program:
https://github.com/NetHack/NetHack/issues/752

## Running

`./attrsim36 <role> <race> <iterations>`

Role is one of `arc`, `bar`, `cav`, `hea`, `kni`, `mon`, `pri`, `rog`,
`ran`, `sam`, `tou`, `val`, `wiz`.  Race is one of `h`, `d`, `e`, `g`,
`o` (respectively: human, dwarf, elf, gnome, orc).

For example:

`./attrsim36 hea h 10000000` simulates 10 million human Healers and
outputs the attribute statistics.
