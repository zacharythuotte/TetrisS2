TEMPLATE     = vcapp
TARGET       = T-Tricks
CONFIG      += warn_on qt debug_and_release windows console
HEADERS     += forme.h game.h level.h test.h mainwindow.h optionwindow.h gamewindow.h gameoverwindow.h leaderboardwindow.h leaderboard.h
SOURCES     += main.cpp forme.cpp game.cpp level.cpp test.cpp mainwindow.cpp optionwindow.cpp gamewindow.cpp gameoverwindow.cpp leaderboardwindow.cpp leaderboard.cpp
INCLUDEPATH += ../Tetris
QT += widgets multimedia
RC_ICONS = icon.ico