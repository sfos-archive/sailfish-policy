TEMPLATE = aux

CONFIG += sailfish-qdoc-template
SAILFISH_QDOC.project = sailfish-policy
SAILFISH_QDOC.config = sailfish-policy.qdocconf
SAILFISH_QDOC.style = offline
SAILFISH_QDOC.path = /usr/share/doc/sailfish-policy/

OTHER_FILES += \
    $$PWD/sailfish-policy.qdocconf \
    $$PWD/index.qdoc \
    $$PWD/sailfish-policy.cpp
