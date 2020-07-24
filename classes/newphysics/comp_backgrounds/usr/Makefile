####################################################
# Copyright (C) 2001-2003, CompHEP Collaboration
#------------------------------------------------------
# Author: Sherstnev                                #
####################################################
#
# $Id: Makefile,v 1.13 2003/11/17 08:23:47 kryukov Exp $
#
# $Log: Makefile,v $
# Revision 1.13  2003/11/17 08:23:47  kryukov
# Small bug in binary distributive
#
# Revision 1.12  2003/09/22 09:58:28  sherstnv
# Izmenena sistema nazvaniya bibliotek CompHEP
#
# Revision 1.11  2003/06/29 12:09:58  sherstnv
# Small bug in Makefiels: n_comphep is not linked, because of
# all lib's have been moved to lib dir.
#
# Revision 1.10  2003/06/25 18:46:42  kryukov
# *** empty log message ***
#
# Revision 1.9  2003/06/18 09:06:59  kryukov
# Improvet the mk_tab building
#
# Revision 1.8  2003/06/17 16:43:15  sherstnv
# mk_tab is linked by user in the $WDIR/usr directory.
#
# Revision 1.7  2003/06/15 16:44:23  kryukov
# n_comphep allways usr userFunction from $WDIR/usr/usrFun.c now.
#
####################################################

.PHONY: clean
CHEP=/A/lns183/cdat/daf9/mccann/software/src/comphep-4.4.0

CC=    $(shell more $(CHEP)/CC)
CFLAGS=$(shell more $(CHEP)/CFLAGS)
CLIBS:=$(shell more $(CHEP)/CLIBS)
INS:=-I$(CHEP)/src

mk_tab.exe: userFun.o
	$(CC) $(CFLAGS) -o mk_tab.exe userFun.o $(CLIBS) -ltab -lnum -lserv

userFun.o: userFun.c

clean:
	@rm *.o
	
%.o: %.c
	$(CC) $(CFLAGS) $(INS) -c $<
