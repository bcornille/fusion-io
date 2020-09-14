#######################################################
# if we're not in the build directory, build it
#######################################################
ifeq (,$(filter _%,$(notdir $(CURDIR))))

include $(FIO_ROOT)/install/common_header.mk

#######################################################
# if we are in the build directory, do normal build
#######################################################
else

# set source directory
VPATH=$(SRCDIR)

# include platform-specific options
include $(FIO_ROOT)/install/make.inc.$(FIO_ARCH)

LIBS := -L$(FIO_ROOT)/fusion_io/_$(FIO_ARCH) -lfusionio \
	-L$(FIO_ROOT)/m3dc1_lib/_$(FIO_ARCH) -lm3dc1 \
	-Wl,--start-group -L$(NIMROD_ROOT)/nimfio -lnimfio \
	-L$(NIMROD_ROOT)/nimcore -lnimblock -lnimbltype -lnimlocate -lnimmatrix -lnimiter -lnimpar \
	-L$(NIMROD_ROOT)/nimlib -lnimmpi -lnimlib \
	-L$(NIMROD_ROOT)/externals -llapack_dummy -lsslu_dummy -lslud_dummy -Wl,--end-group \
	-Wl,-rpath,$(FIO_ROOT)/fusion_io/_$(FIO_ARCH) \
	-Wl,-rpath,$(FIO_ROOT)/m3dc1_lib/_$(FIO_ARCH) \
	-Wl,-rpath,$(NIMROD_ROOT)/nimfio \
	$(HDF5_LIBS) $(LIBS)

		# -Wl,-rpath,$(NIMROD_ROOT)/nimlib \
		# -Wl,-rpath,$(NIMROD_ROOT)/nimcore \

NIMROD_INCLUDE := -I$(NIMROD_ROOT)/nimfio -I$(NIMROD_ROOT)/nimcore  \
	-I$(NIMROD_ROOT)/nimlib -I$(NIMROD_ROOT)/nimrod -I$(NIMROD_ROOT)/nimplot

INCLUDE := -I$(FIO_ROOT)/fusion_io -I$(FIO_ROOT)/fusion_io/_$(FIO_ARCH) \
	-I$(FIO_ROOT)/m3dc1_lib \
	$(NIMROD_INCLUDE) \
	$(HDF5_INCLUDE) $(INCLUDE)

F90FLAGS := $(F90FLAGS) -DFORTRAN

all :

examples : example example_c example_fortran example_push

push : $(EXAMPLE_PUSH_BIN)

example : example.o
	$(CXX) $(LDFLAGS) $< $(NIMROD_INCLUDE) -I/usr/lib/openmpi/lib $(LIBS) -lmpi_usempif08 -lmpi_usempi_ignore_tkr -lmpi_mpifh  -o $@

example_c : example_c.o
	$(CXX) $(LDFLAGS) $< $(LIBS) -o $@

example_fortran : example_fortran.o
	$(F90) $(LDFLAGS) $< $(LIBS) -o $@

example_push : example_push.o
	$(F90) $(LDFLAGS) $< -lfio_push $(LIBS) -o $@

korc_example : main.cpp #korc_example.cpp
	mpicxx $< -std=c++11 $(INCLUDE) $(LIBS) -o $@

exmk :
	echo FIO_DIR=$(FIO_INSTALL_DIR) > $@
	cat $(FIO_ROOT)/install/make.inc.$(FIO_ARCH) >> $@
	cat $(FIO_ROOT)/examples/example.mk >> $@
	cat $(FIO_ROOT)/install/common_footer.mk >> $@

.PHONE: setup_data
setup_data :
	tar xvfz $(FIO_ROOT)/examples/data/mars/mars_data.tar.gz -C $(FIO_ROOT)/examples/data/mars
	gunzip -c $(FIO_ROOT)/examples/data/gato/diagnostics.dat.gz > $(FIO_ROOT)/examples/data/gato/diagnostics.dat

.PHONY: install
install : exmk setup_data
	mkdir -m 755 -p $(FIO_INSTALL_DIR)/examples
	cp $(SRCDIR)/example.cpp $(FIO_INSTALL_DIR)/examples
	cp $(SRCDIR)/example_fortran.f90 $(FIO_INSTALL_DIR)/examples
	cp $(SRCDIR)/example_c.c $(FIO_INSTALL_DIR)/examples
	cp $(SRCDIR)/example_python.py $(FIO_INSTALL_DIR)/examples
	cp $(SRCDIR)/python_fpy_example.py $(FIO_INSTALL_DIR)/examples
	cp $(SRCDIR)/example_push.f90 $(FIO_INSTALL_DIR)/examples
	cp -r $(SRCDIR)/data $(FIO_INSTALL_DIR)/examples
	cp exmk $(FIO_INSTALL_DIR)/examples/makefile
	rm exmk

include $(FIO_ROOT)/install/common_footer.mk

endif
