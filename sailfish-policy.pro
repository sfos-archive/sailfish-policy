TEMPLATE = subdirs
SUBDIRS = libsailfishpolicy \
    qml \
    policy-updater \
    tests \
    examples \
    doc

qml.depends = libsailfishpolicy
policy-updater.depends = libsailfishpolicy
tests.depends = libsailfishpolicy
examples.depends = libsailfishpolicy

OTHER_FILES += rpm/sailfish-policy.spec
