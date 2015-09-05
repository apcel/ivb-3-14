
use strict;
use warnings;

my $in ="as 123.1 . 2 _ \\\'adsf.1";

    while ( $in =~ /(?:([0-9]+(?:\.[0-9]+)?)|([a-zA-Z_]+)|([^a-zA-Z_0-9]))/g ) {
        print("NUM: $1 \n") if defined $1;
        print("LIT: $2 \n") if defined $2;
        print("OTHER: $3 \n") if defined $3;
    }
#$_="\n"
