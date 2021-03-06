#
#  -- LAPACK95 interface driver routine (version 2.0) --
#     UNI-C, Denmark; Univ. of Tennessee, USA; NAG Ltd., UK
#     August 5, 2000
# 
# -dcfuns  Enable recognition of non-standard double
#          precision  complex intrinsic functions
# -dusty   Allows the compilation and execution of "legacy"
#          software by downgrading the category  of  common
#          errors  found  in  such software from "Error" to
# -ieee=full enables all IEEE arithmetic facilities
#          including non-stop arithmetic.

OPTS0    = -O3 -fno-trapping-math -std=legacy 
#-u -V -dcfuns -dusty -ieee=full
MODLIB   = -I./../lapack95_modules
OPTS1    = -c $(OPTS0)
OPTS3    = $(OPTS1) $(MODLIB)
OPTL     = -o 
OPTLIB   =

LAPACK_PATH = ./LAPACK95

LAPACK95 = ../lapack95.a
LAPACK77 = $(LAPACK_PATH)/lapack.a
TMG77    = $(LAPACK_PATH)/tmglib.a
BLAS     = $(LAPACK_PATH)/blas.a

LIBS     = $(LAPACK95) $(TMG77) $(LAPACK77) $(BLAS)
SUF      = f90

XX = $(RM) $@; \
        $(RM) $@.res; \
	$(FC) $(OPTS0) -o $@ $(MODLIB) $@.$(SUF) $(OPTLIB) $(LIBS); \
        $@ < $@.dat > $@.res; \
        $(RM) $@

YY = $(FC) $(OPTS0) -o $@ $(MODLIB) $@.$(SUF) $(OPTLIB) $(LIBS)

.SUFFIXES: .f90 .f .o

.$(SUF).o: 
	$(FC) $(OPTS3) $<

.f.o:
	$(FC) $(OPTS3) $<
