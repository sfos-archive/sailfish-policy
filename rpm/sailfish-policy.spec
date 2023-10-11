Name:       sailfish-policy
Summary:    Sailfish MDM Policy library
Version:    0.3.23
Release:    1
License:    BSD
URL:        https://github.com/sailfishos/sailfish-policy
Source0:    %{name}-%{version}.tar.bz2
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5DBus)
BuildRequires:  pkgconfig(Qt5Gui)
BuildRequires:  pkgconfig(nemodbus)
BuildRequires:  pkgconfig(libshadowutils)
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(ohm-ext-mdm)
BuildRequires:  pkgconfig(usb_moded)
BuildRequires:  pkgconfig(systemd)
Requires(pre): shadow-utils
Requires(pre): sailfish-setup
Requires:  ohm-plugin-mdm

%define policydir %{_sharedstatedir}/policy

%description
Sailfish Policy library

%package doc
Summary:    Documentation for Sailfish OS MDM Policy Framework
BuildRequires:  sailfish-qdoc-template
BuildRequires:  qt5-qttools-qthelp-devel
BuildRequires:  qt5-tools

%description doc
%{summary}.

%package examples
Summary:    Sailfish MDM example policy plugin
Requires:   %{name} = %{version}-%{release}

%description examples
Sailfish MDM example policy plugin.

%package tests
Summary:    Sailfish Policy unit tests
Requires:   %{name} = %{version}-%{release}
BuildRequires:  pkgconfig(Qt5Test)

%description tests
%{summary}.

%package devel
Summary:    Development files for Sailfish Policy
Requires:   %{name} = %{version}-%{release}

%description devel
Development package for Sailfish Policy

%prep
%setup -q -n %{name}-%{version}

%build

%qmake5 "VERSION=%{version}"

%make_build

%install
rm -rf %{buildroot}
%qmake5_install

mkdir -p %{buildroot}/%{policydir}
mkdir -p %{buildroot}%{_unitdir}/multi-user.target.wants/
ln -sf ../policies-setup.service %{buildroot}%{_unitdir}/multi-user.target.wants/

mkdir -p %{buildroot}/%{_docdir}/%{name}
cp -R doc/html/* %{buildroot}/%{_docdir}/%{name}/

%files
%defattr(-,root,root,-)
%license LICENSE.BSD
%attr(4754, root, sailfish-mdm) %{_libexecdir}/policy-updater
%{_unitdir}/policies-setup.service
%{_unitdir}/multi-user.target.wants/policies-setup.service
%{_libdir}/libsailfishpolicy.so.*
%{_libdir}/qt5/qml/Sailfish/Policy
%attr(775, root, sailfish-mdm) %dir %{policydir}

%files doc
%defattr(-,root,root,-)
%dir %{_datadir}/doc/sailfish-policy
%{_datadir}/doc/sailfish-policy

%files examples
%defattr(-,root,root,-)
%{_libdir}/libsailfishpolicy/plugin/libsailfishpolicyplugin.so

%files tests
%defattr(-,root,root,-)
/opt/tests/Sailfish/MDM/tst_accesspolicy

%files devel
%defattr(-,root,root,-)
%{_libdir}/libsailfishpolicy.so
%{_libdir}/pkgconfig/sailfishpolicy.pc
%{_includedir}/libsailfishpolicy

%post
/sbin/ldconfig || :

%postun
/sbin/ldconfig || :
