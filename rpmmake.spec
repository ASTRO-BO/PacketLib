# rpm spec file template for Qwt.  
#
# Qwt doesn't distribute binary packages as there are too many 
# distributions and Qt options. If you like to have Qwt rpm packages
# this spec file template will help you to build them.
# It was tested on Mandrake-8.1 and SuSE-7.3/8.0.
#
# 1) Set QTDIR to point to the qt release you want to build qwt for.
#
# 2) If qmake is not installed, the spec file will fallback on tmake.
#    In this case you have to set TMAKEPATH.
#
# 3) The spec file tries to autodetect if a threaded qt library
#    is installed. If not it tries to build against the non-threaded
#    qt-library. If you need C++-exceptions remove the '#' from the line 
#    in the prep stage. If you need to change any other option in the pro-files 
#    un-tar the Qwt package, edit the pro files and tar it again.
#
# 4) The spec file builds a qwt and a qwt-devel package. The qwt-devel
#    package includes qwt-examples. If you don't like to install 
#    binaries remove the commands in the build stage.
#
# 6) Each distribution has a RPM-BUILD-TREE. 
#
#        - On Mandrake's it is /usr/src/RPM
#        - On SuSE's it is /usr/src/packages
#        - On Red Hat's it is /usr/src/redhat (95 % sure)
#
#    You need write access to RPM-BUILD-TREE.
#    Copy the spec file to RPM-BUILD-TREE/SPECS, qwt-0.4.1.tar.bz2 to 
#    RPM-BUILD-TREE/SOURCES.
#
#    rpm -ba --clean RPM-BUILD-TREE/SPECS/qwt.spec
#
# 7) You find the following packages:
#		RPM-BUILD-TREE/RPMS/i386/qwt-0.4.1-1.i386.rpm
#       RPM-BUILD-TREE/RPMS/i386/qwt-devel-0.4.1-1.i386.rpm
#       RPM-BUILD-TREE/SRPMS/qwt-0.4.1-1.src.rpm

%define name	qwt
%define version	0.4.1
%define release	1

Summary:	Qt Widgets for Technical applications (Qwt)
Name:		%{name}
Version:	%{version}
Release:	%{release}
Copyright:	LGPL
URL:		http://sourceforge.net/projects/qwt
Group:		System/Libraries
Source:		%{name}-%{version}.tar.bz2
BuildRoot:	%{_tmppath}/%{name}-buildroot

%description
Qwt is an extension to the Qt GUI library from Troll Tech AS.  The Qwt library
contains widgets and components which are primarily useful for technical and
scientifical purposes.  It includes a 2-D plotting widget, different kinds of
sliders, and much more.

%package devel
Summary:	Qt Widgets for Technical applications (Qwt)
Group:		Development/C++

%description devel
Qwt is an extension to the Qt GUI library from Troll Tech AS.  The Qwt library
contains widgets and components which are primarily useful for technical and
scientifical purposes.  It includes a 2-D plotting widget, different kinds of
sliders, and much more.  This package contains the header files, HTML and MAN
documentation and all examples.

%prep
%setup -n %{name}-%{version}
# zap CVS stuff, in case of a snapshot
find . -name CVS -o -name .cvsignore | xargs rm -Rf

# check for a threaded qt library and if not found,
# modify the *.pro files to fall back on a non-threaded 
# Qt library, if found.
if [ ! -e $QTDIR/lib/libqt-mt.so -a -e $QTDIR/lib/libqt.so ]; then
	find . -name "*.pro" | perl -e "s|thread||g" -pi
fi

# uncomment the following line if you need C++-exceptions
# find . -name "*.pro" | perl -e "s|-fno-exceptions||g" -pi


# try to run qmake, or fall back on tmake 
if [ -e $QTDIR/bin/qmake ]; then
	$QTDIR/bin/qmake qwt.pro -o Makefile
	(cd examples; $QTDIR/bin/qmake examples.pro -o Makefile)
else
	tmake qwt.pro -o Makefile
	(cd examples; tmake examples.pro -o Makefile)
fi

%build

# build the library
make

# building the examples is a useful check 
# if you don't like them comment out the following line
(cd examples; make)
 
%install

rm -rf %{buildroot}
mkdir -p %{buildroot}/%{_includedir}/qwt
mkdir -p %{buildroot}/%{_libdir}
mkdir -p %{buildroot}/%{_mandir}/man3

for n in include/*.h ; do
    install -m 644 $n %{buildroot}/%{_includedir}/qwt
done

# install, preserving links
chmod 644 lib/libqwt.so.%{version}
for n in lib/libqwt.so* ; do
    cp -d $n %{buildroot}/%{_libdir}
done

for n in doc/man/man3/*.3 ; do
    install -m 644 $n %{buildroot}/%{_mandir}/man3
done

# the %%post and %%postun directives are superfluous on SuSE, but harmless
%post
/sbin/ldconfig

%postun
/sbin/ldconfig

%clean
rm -rf %{buildroot}

%files
%defattr(-, root, root)
%doc CHANGES COPYING README
%{_libdir}/libqwt.so.%{version}

%files devel
%defattr(-, root, root)
%doc COPYING doc/html/*.html doc/html/*.gif examples
%dir %{_includedir}/qwt
%{_includedir}/qwt/*
%{_libdir}/libqwt.so
%{_mandir}/man3/*

%changelog
* Wed Apr 24 2002 Gerard Vermeulen <gvermeul@polycnrs-gre.fr> 0.4.1-1
- spec file for Qwt-4.1.0 with Qt-2.X, Qt-3.X on Mandrake, Suse, ...

# EOF
