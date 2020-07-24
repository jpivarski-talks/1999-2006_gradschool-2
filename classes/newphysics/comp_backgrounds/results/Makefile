####################################################
# Copyright (C) 2001-2003, CompHEP Collaboration
#------------------------------------------------------
# Author: Sherstnev                                #
#---------------------------------------------------
# $Id: Makefile.results,v 1.21 2003/09/22 09:58:28 sherstnv Exp $
#
# $Log: Makefile.results,v $
# Revision 1.21  2003/09/22 09:58:28  sherstnv
# Izmenena sistema nazvaniya bibliotek CompHEP
#
# Revision 1.20  2003/06/29 12:09:58  sherstnv
# Small bug in Makefiels: n_comphep is not linked, because of
# all lib's have been moved to lib dir.
#
# Revision 1.19  2003/06/26 15:55:35  sherstnv
# small bug in Makefile for results is fixed
#
# Revision 1.18  2003/06/26 15:51:43  sherstnv
# symp_batch.pl script is customized to new CompHEP options/new
# n_comphep creation schime.
#
# Revision 1.17  2003/06/25 18:46:42  kryukov
# *** empty log message ***
#
# Revision 1.16  2003/06/18 09:06:59  kryukov
# Improvet the mk_tab building
#
# Revision 1.15  2003/06/15 16:44:23  kryukov
# n_comphep allways usr userFunction from $WDIR/usr/usrFun.c now.
#
# Revision 1.14  2003/06/15 15:48:37  kryukov
# Impove n_comphep compilation
#
# Revision 1.13  2003/04/21 16:10:40  kryukov
# New compilation scheme for n_comphep
#
# Revision 1.12  2003/04/21 11:19:10  kryukov
# Input target: d_compile
#
# Revision 1.11  2003/04/21 11:11:53  kryukov
# Optimize n_comphep compilation
#
# Revision 1.10  2003/04/13 20:47:23  kryukov
# Change the order of libs for s_comphep link.
#
# Revision 1.9  2003/04/08 10:22:46  kryukov
# Put option force in gzip if diagr.tar
#
# Revision 1.8  2003/04/02 20:02:09  sherstnv
# Melkaya oshibka v systeme make
#
# Revision 1.7  2003/03/01 09:18:51  sherstnv
# Small ug in results Makefile: now sqme.c and service.c are added to
# diag.tar archive
#
# Revision 1.6  2003/01/25 19:12:49  kryukov
# Change sequence of linking libraries.
#
####################################################

.PHONY: ffiles all blind link blindlink clean usrObj
CHEP=/A/lns183/cdat/daf9/mccann/software/src/comphep-4.4.0

INS:=-I$(CHEP)/include
CC=    $(shell more $(CHEP)/CC)
CFLAGS=$(shell more $(CHEP)/CFLAGS)
CLIBS= $(shell more $(CHEP)/CLIBS) 

F_TARGET=$(shell cat ffile_0)
F_OBJ=$(subst .c,.o,$(F_TARGET))

D_TARGET=$(shell ls d*.c)
D_OBJ=$(subst .c,.o,$(D_TARGET))

echo F_TARGET=${F_TARGET}

all: ffiles d_compile sqme.o service.o
	make link

blind: ffiles d_compile sqme.o service.o
	make blindlink

blindlink: usrObj
	$(CC) $(CFLAGS) -o n_comphep.exe sqme.o service.o \
	../usr/userFun.o -lnum -lserv f_*.a -lmssm $(CLIBS) -lg2c -lserv

link: blindlink
	@echo "Press [Enter] to continue ..."; \
	 read

ffiles:
	@make f_compile
	@rm -f ffile_0
	@for x in `ls ffile_*`; do \
		mv -f $$x ffile_0; \
		make f_compile; \
	done
	@if [ -x diags.tar ]; then gzip diags.tar; fi
	rm -f ffile_*

f_compile: $(F_OBJ)
	@echo $(F_OBJ)
	@tar r --remove-files -f diags.tar $(F_TARGET)
	@ar -r f_0.a $(F_OBJ)
	@rm -f $(F_OBJ)
	@ranlib f_0.a

d_compile: $(D_OBJ)
	@tar r --remove-files -f diags.tar $(D_TARGET)
	@ar -r f_0.a $(D_OBJ)
	@rm -f $(D_OBJ)
	@ranlib f_0.a

usrObj:
	@make -C ../usr

clean:
	@mv  Makefile  .Makefile.results
	@mv  n_comphep .n_comphep
	@rm -f *
	@mv .Makefile.results Makefile
	@mv .n_comphep        n_comphep
	
.c.o:
	$(CC) $(CFLAGS) $(INS) -c $<
