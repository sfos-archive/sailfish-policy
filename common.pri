unix|macx {
    QMAKE_CXXFLAGS += -Werror

    # enable full stack traces at the expense of optimisation
    QMAKE_CXXFLAGS += -pg -O0 -g
}
