#!/usr/local/bin/perl

foreach $run (200733, 200734, 200746, 200750, 200797, 200798, 200801,
	      200802, 200805, 200806, 200826, 200829, 200832, 200833,
	      200834, 200835, 200847, 200851, 200853, 200854, 200976,
	      200978, 200979, 200981, 200983, 200984, 201001, 201002,
	      201003, 201004, 201013, 201014, 201016, 201017, 201018,
	      201019, 201021, 201023, 201024, 201026, 201027, 201028,
	      201029, 201030, 201031, 201035, 201037, 201039, 201040,
	      201041, 201042, 201043, 201095, 201097, 201102, 201103,
	      201104, 201105, 201106, 201107, 201108, 201135, 201142,
	      201144, 201145, 201146, 201147, 201148, 201150, 201151,
	      201152, 201153, 201154, 201155, 201156, 201157, 201158,
	      201160, 201164, 201165, 201166, 201167, 201170, 201171,
	      201172, 201173, 201174, 201175, 201176, 201179, 201180,
	      201181, 201184, 201186, 201188, 201189, 201190, 201192,
	      201193, 201194, 201195, 201196, 201197, 201198, 201199,
	      201201, 201202, 201203, 201204, 201205, 201206, 201213,
	      201277, 201285, 201301, 201302, 201303, 201318, 201319,
	      201352, 201365, 201366, 201385, 201387, 201390) {

    print "Submitting $run\n";
    system("qsub -N b_$run batch_$run.run");
    
    do {
	print "Waiting ten seconds...\n";
	sleep 10;
	
	$qstat = `qstat -u mccann | wc -l`;
	chop($qstat);
	$qstat -= 2;
	
    } while ($qstat >= 50);
}
