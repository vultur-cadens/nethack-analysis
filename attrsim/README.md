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

`attrsim-dnh` (for dNetHack) is also included.

## Running

`attrsim36 <role> <race> <iterations>`

Role is one of `arc`, `bar`, `cav`, `hea`, `kni`, `mon`, `pri`, `rog`,
`ran`, `sam`, `tou`, `val`, `wiz`.  Race is one of `hum`, `elf`,
`dwa`, `gno`, `orc`.

For example:

`attrsim36 hea hum 10000000` simulates 10 million human Healers and
outputs the attribute statistics.

`attrsim-dnh` supports additional roles and races, and also the
"descendant" option with `-d`.  For a list of the roles and races, run
`attrsim-dnh` without any parameters.

`attrsim-dnh -d hea hum 10000000` simulates 10 million human Healers
that are descendants.

## Limitations

When the starting inventory is heavy enough and STR+CON is not enough
to keep the character unburdened, then NetHack will increase STR,
followed by CON, until the character is unburdened.  This program does
not simulate the effects of starting inventory, so the average STR
calculated by this program for some roles might be lower than the
actual average.
