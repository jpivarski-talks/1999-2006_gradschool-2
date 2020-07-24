#!/usr/bin/perl

@files = ();
foreach $argv ( @ARGV )
{ push( @files, $argv )
      if ( $argv !~ /\.\./  &&  $argv !~ /\.$/ ); }

if ( $#ARGV != -1 )
{
    system( "ls", "-s", @files );

    print "Do you want to delete all of these? (y/n): ";

    $answer = <STDIN>;

    if ( $answer =~ /^y/i )
    {
	foreach $file ( @files )
	{
	    unlink( $file );
	}
	print ( ($#files + 1 ) . " files deleted.\n" );
    }
    else
    {
	print "Nothing has been deleted.\n";
    }
}
