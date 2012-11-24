INCLUDES = 
METASOURCES = AUTO
SUBDIRS = devices algorithms
lib_LTLIBRARIES = libpense.la
libpense_la_SOURCES = environment.cpp object.cpp
libpense_la_LIBADD = $(top_builddir)/pense/algorithms/fuzzylogic/libfuzzylogic.la\
	$(top_builddir)/pense/algorithms/libalgorithms.la\
	$(top_builddir)/pense/devices/libdevices.la \
	$(top_builddir)/pense/devices/plants/libplants.la \
	$(top_builddir)/pense/devices/controllers/libcontrollers.la

rootincludedir = $(includedir)/pense
rootinclude_HEADERS = environment.h object.h global.h

