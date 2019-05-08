#!/usr/bin/perl

use strict;
use warnings;

if (@ARGV != 1) { 
   print "missing FILE parameter. \nusage: perl extract.pl FILE\n";
   exit;
}

print "processing...\n";

my $file = "./".$ARGV[0];
#print "extracting file=$file\n";

open(INFILE, "<$file") or die("cannot open $file");
my(@lines) = <INFILE>;
close(INFILE);

my %stats;
my $tot_stats; # total number of statistics
my @TOTAL_TIME = ();
my @AVERAGE_MEM = ();
my @AVERAGE_PROCS = ();
my @EVT_PA_PVM = ();
my @EVT_PA_NATIVE = ();
my @EVT_PA_VM = ();
my @EVT_PE = ();
my @EVT_PD = ();
my @EVT_PI = ();
my $tot_evts = 0;
foreach my $line (@lines) {
   $line =~ s/\n//g;
   (my $iter,my $stat,my $number) = split(";",$line);
   if ($stat =~ /^#/) {
      $tot_stats++;
      next;
   }
   $number =~ s/\,/\./g;
   $stats{$stat} .= $number.";";
   
   if ($stat eq "STAT_TOTAL_TIME") {
      push @TOTAL_TIME, $number;
   } elsif ($stat eq "STAT_AVERAGE_MEM") {
      push @AVERAGE_MEM, $number;
   } elsif ($stat eq "STAT_AVERAGE_PROCS") {
      push @AVERAGE_PROCS, $number;
   } elsif ($stat eq "STAT_EVT_PA_PVM") {
      push @EVT_PA_PVM, $number;
   } elsif ($stat eq "STAT_EVT_PA_NATIVE") {
      push @EVT_PA_NATIVE, $number;
   } elsif ($stat eq "STAT_EVT_PA_VM") {
      push @EVT_PA_VM, $number;
   } elsif ($stat eq "STAT_EVT_PE") {
      push @EVT_PE, $number;
   } elsif ($stat eq "STAT_EVT_PD") {
      push @EVT_PD, $number;
   } elsif ($stat eq "STAT_EVT_PI") {
      push @EVT_PI, $number;
   } elsif ($stat eq "STAT_TOTAL_EVENTS") {
      $tot_evts = $number;
   }
   
   #print $line."\n";
}

#foreach my $key (sort keys %stats) {
#   my $number = $stats{$key};
#   $number =~ s/\./\,/g;
#   print "$key;$number\n";
#}


#create the data file for gnuplot

open(OUTFILE, ">DADOS.txt") or die("cannot open DADOS.txt\n");
for (my $i = 0; $i < @TOTAL_TIME; $i++) {
   #$TOTAL_TIME[$i] =~ s/\./\,/g;
   #$AVERAGE_MEM[$i] =~ s/\./\,/g;
   #$AVERAGE_PROCS[$i] =~ s/\./\,/g;
   my $str = "$TOTAL_TIME[$i] $AVERAGE_MEM[$i] $AVERAGE_PROCS[$i] ".
             "$EVT_PA_PVM[$i] $EVT_PA_NATIVE[$i] $EVT_PA_VM[$i] ".
             "$EVT_PE[$i] $EVT_PD[$i] $EVT_PI[$i]\n";
   print OUTFILE $str;
}
close(OUTFILE);

####################################################################################################

#create a gnuplot
my $name = "_analysis.plot";
print "creating new gnuplot file named '$name'\n";
open(OUTFILE, ">$name") or die("cannot open $name\n");
print OUTFILE "set terminal postscript enhanced color\n";
print OUTFILE "set output \"_analysis.eps\"\n";

#print OUTFILE "set logscale y\n";
print OUTFILE "set key right top\n";
print OUTFILE "set ylabel \"Average Memory (in Gb)\"\n";
#print OUTFILE "set y2label \"Simulation Time (in s)\"\n";
print OUTFILE "set xlabel \"#Simulation Execution\"\n";
#print OUTFILE "set y2tics\n";
#print OUTFILE "set logscale y\n";
print OUTFILE "set grid\n";
#print OUTFILE "set yrange[7.5:8.2]\n";
#print OUTFILE "set y2range[18000:19000]\n";

print OUTFILE "set style line 1 lt 5 lc rgb \"#0000FF\" lw 1\n";
print OUTFILE "set style line 2 lt 1 lc rgb \"#FF0000\" lw 1\n";
print OUTFILE "plot \\\n";
#print OUTFILE " \"DADOS\.txt\" using (\$2/1024/1024) ls 1 with lines title \"Memory 1\" axes x1y1, \\\n";
print OUTFILE " \"DADOS\.txt\" using (\$2/1024/1024/1024) ls 2 with lines title \"Memory \" axes x1y1\n";
close(OUTFILE);

system("gnuplot $name");

####################################################################################################

#create a gnuplot
$name = "_time.plot";
print "creating new gnuplot file named '$name'\n";
open(OUTFILE, ">$name") or die("cannot open $name\n");
print OUTFILE "set terminal postscript enhanced color\n";
print OUTFILE "set output \"_time.eps\"\n";

#print OUTFILE "set logscale x\n";
#print OUTFILE "set logscale y\n";
print OUTFILE "set key right top\n";
print OUTFILE "set ylabel \"Simulation Time (in s)\"\n";
print OUTFILE "set xlabel \"Simulation Execution Iteration\"\n";
print OUTFILE "set yrange[25000:]\n";
print OUTFILE "set grid\n";

print OUTFILE "set style line 1 lt 5 lc rgb \"#0000FF\" lw 1\n";
print OUTFILE "plot \\\n";
print OUTFILE " \"DADOS\.txt\" using 1 ls 1 with lines title \"Time\" \n";
close(OUTFILE);

system("gnuplot $name");

####################################################################################################

#create a gnuplot for the rates
$name = "_rates.plot";
print "creating new gnuplot file named '$name'\n";
open(OUTFILE, ">$name") or die("cannot open $name\n");
print OUTFILE "set terminal postscript enhanced color\n";
print OUTFILE "set output \"_rates.eps\"\n";

print OUTFILE "set key right top\n";
print OUTFILE "set ylabel \"# of events\"\n";
print OUTFILE "set xlabel \"Simulation Execution Iteration\"\n";
print OUTFILE "set grid\n";

print OUTFILE "set style line 1 lt 5 lc rgb \"#0000FF\" lw 1\n";
print OUTFILE "set style line 2 lt 1 lc rgb \"#FF0000\" lw 1\n";
print OUTFILE "set style line 3 lt 2 lc rgb \"#00FF00\" lw 1\n";
print OUTFILE "set style line 4 lt 3 lc rgb \"#AA00BB\" lw 1\n";
print OUTFILE "set style line 5 lt 4 lc rgb \"#A94455\" lw 1\n";
print OUTFILE "set style line 6 lt 5 lc rgb \"#FED433\" lw 1\n";
print OUTFILE "plot \\\n";
print OUTFILE " \"DADOS\.txt\" using (\$4/$tot_evts) ls 1 with lines title \"PA-PVM\", \\\n";
print OUTFILE " \"DADOS\.txt\" using (\$5/$tot_evts) ls 2 with lines title \"PA-NATIVE\", \\\n";
print OUTFILE " \"DADOS\.txt\" using (\$6/$tot_evts) ls 3 with lines title \"PA-VM\", \\\n";
print OUTFILE " \"DADOS\.txt\" using (\$7/$tot_evts) ls 4 with lines title \"PE\", \\\n";
print OUTFILE " \"DADOS\.txt\" using (\$8/$tot_evts) ls 5 with lines title \"PD\", \\\n";
print OUTFILE " \"DADOS\.txt\" using (\$9/$tot_evts) ls 6 with lines title \"PI\"\n";
close(OUTFILE);

system("gnuplot $name");


####################################################################################################

#create a gnuplot for the average number of processes (lots of lines)
$name = "_procnum.plot";
print "creating new gnuplot file named '$name'\n";
open(OUTFILE, ">$name") or die("cannot open $name\n");
print OUTFILE "set terminal postscript enhanced color\n";
print OUTFILE "set output \"_procnum.eps\"\n";

print OUTFILE "unset key\n";
print OUTFILE "set ylabel \"Arrival\"\n";
print OUTFILE "set y2label \"Departure\"\n";
print OUTFILE "set xlabel \"Simulation Execution Iteration\"\n";
print OUTFILE "set ytics\n";
print OUTFILE "set y2tics\n";
print OUTFILE "set grid\n";

print OUTFILE "set style line 1 lt 5 lc rgb \"#0000FF\" lw 1\n";
print OUTFILE "set style line 2 lt 1 lc rgb \"#FF0000\" lw 1\n";
print OUTFILE "set style line 3 lt 2 lc rgb \"#00FF00\" lw 1\n";
print OUTFILE "set style line 4 lt 3 lc rgb \"#AA00BB\" lw 1\n";
print OUTFILE "set style line 5 lt 4 lc rgb \"#A94455\" lw 1\n";
print OUTFILE "set style line 6 lt 5 lc rgb \"#FED433\" lw 1\n";
print OUTFILE "plot \\\n";
for (my $i=0;$i<$tot_stats;$i++) {
   my $num;
   if ($i < 10) { $num = "00".$i; }
   elsif ($i < 100) { $num = "0".$i; }
   else { $num = "".$i; }
   if ($i==$tot_stats-1) {
      print OUTFILE " \"exec\_$num\.txt\" using 1 ls 1 with lines title \"$num\" axes x1y1, \\\n";
      print OUTFILE " \"exec\_$num\.txt\" using 2 ls 2 with points title \"$num\" axes x1y2\n";
   } else {
      print OUTFILE " \"exec\_$num\.txt\" using 1 ls 1 with lines title \"$num\" axes x1y1, \\\n";
      print OUTFILE " \"exec\_$num\.txt\" using 2 ls 2 with points title \"$num\" axes x1y2, \\\n";
   }
}
close(OUTFILE);

system("gnuplot $name");

####################################################################################################

#create a gnuplot for the USED MEMORY
$name = "_memory.plot";
print "creating new gnuplot file named '$name'\n";
open(OUTFILE, ">$name") or die("cannot open $name\n");
print OUTFILE "set terminal postscript enhanced color\n";
print OUTFILE "set output \"_memory.eps\"\n";

print OUTFILE "unset key\n";
print OUTFILE "set ylabel \"Used Memory (Gb)\"\n";
print OUTFILE "set xlabel \"Simulation Execution Iteration\"\n";
print OUTFILE "set ytics\n";
print OUTFILE "set grid\n";

print OUTFILE "set style line 1 lt 5 lc rgb \"#0000FF\" lw 1\n";
print OUTFILE "set style line 2 lt 1 lc rgb \"#FF0000\" lw 1\n";
print OUTFILE "set style line 3 lt 2 lc rgb \"#00FF00\" lw 1\n";
print OUTFILE "set style line 4 lt 3 lc rgb \"#AA00BB\" lw 1\n";
print OUTFILE "set style line 5 lt 4 lc rgb \"#A94455\" lw 1\n";
print OUTFILE "set style line 6 lt 5 lc rgb \"#FED433\" lw 1\n";
print OUTFILE "plot \\\n";
for (my $i=0;$i<$tot_stats;$i++) {
   my $num;
   if ($i < 10) { $num = "00".$i; }
   elsif ($i < 100) { $num = "0".$i; }
   else { $num = "".$i; }
   if ($i==$tot_stats-1) {
      print OUTFILE " \"mem\_$num\.txt\" using (\$1/1024/1024/1024) ls 1 with lines title \"$num\"\n";
   } else {
      print OUTFILE " \"mem\_$num\.txt\" using (\$1/1024/1024/1024) ls 1 with lines title \"$num\", \\\n";
   }
}
close(OUTFILE);

system("gnuplot $name");


####################################################################################################

#create a gnuplot for the process types
$name = "_proctypes.plot";
print "creating new gnuplot file named '$name'\n";
open(OUTFILE, ">$name") or die("cannot open $name\n");
print OUTFILE "set terminal postscript enhanced color\n";
print OUTFILE "set output \"_proctypes.eps\"\n";

print OUTFILE "unset key\n";
print OUTFILE "set ylabel \"Process Type\"\n";
print OUTFILE "set xlabel \"Simulation Execution Iteration\"\n";
print OUTFILE "set ytics\n";
print OUTFILE "set grid\n";

print OUTFILE "set style line 1 lt 5 lc rgb \"#0000FF\" lw 1\n";
print OUTFILE "set style line 2 lt 1 lc rgb \"#FF0000\" lw 1\n";
print OUTFILE "set style line 3 lt 2 lc rgb \"#00FF00\" lw 1\n";
print OUTFILE "set style line 4 lt 3 lc rgb \"#AA00BB\" lw 1\n";
print OUTFILE "set style line 5 lt 4 lc rgb \"#A94455\" lw 1\n";
print OUTFILE "set style line 6 lt 5 lc rgb \"#FED433\" lw 1\n";
print OUTFILE "plot \\\n";
my $counter = 0;
for (my $i=0;$i<$tot_stats;$i++) {
   my $num;
   if ($i < 10) { $num = "00".$i; }
   elsif ($i < 100) { $num = "0".$i; }
   else { $num = "".$i; }
   if ($i==$tot_stats-1) {
      print OUTFILE " \"proc\_$num\.txt\" using 1 ls 1 with lines ".($counter==0?"title \"$num\"":"").", \\\n";
      print OUTFILE " \"proc\_$num\.txt\" using 2 ls 2 with lines ".($counter==0?"title \"$num\"":"").", \\\n";
      print OUTFILE " \"proc\_$num\.txt\" using 3 ls 3 with lines ".($counter==0?"title \"$num\"":"")." \n";
      $counter++;
   } else {
      print OUTFILE " \"proc\_$num\.txt\" using 1 ls 1 with lines title \"$num\", \\\n";
      print OUTFILE " \"proc\_$num\.txt\" using 2 ls 2 with lines title \"$num\", \\\n";
      print OUTFILE " \"proc\_$num\.txt\" using 3 ls 3 with lines title \"$num\", \\\n";
   }
}
close(OUTFILE);

system("gnuplot $name");

####################################################################################################



####################################################################################################
####################################################################################################

print "Total statistics: ".$tot_stats."\n";

####################################################################################################
####################################################################################################


#[         0];-- Statistics [0] --
#[         1];STAT_TOTAL_TIME;78842
#[         2];STAT_TOTAL_EVENTS;20000
#[         3];STAT_EVT_PA_PVM;1518
#[         4];STAT_EVT_PA_NATIVE;7896
#[         5];STAT_EVT_PA_VM;422
#[         6];STAT_EVT_PE;7820
#[         7];STAT_EVT_PD;1596
#[         8];STAT_EVT_PI;748
#[         9];STAT_AVERAGE_MEM;1,31514e+006
#[        10];STAT_AVERAGE_PROCS;22
#[        11];STAT_EXECUTION_TIME;6


