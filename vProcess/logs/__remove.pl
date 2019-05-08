#!/usr/bin/perl

use strict;
use warnings;

print "removing old files...\n";
system("del /Q 2014*.txt \_exec*.txt exec*.txt proc*.txt mem*.txt DADOS.txt *.eps *.plot");


