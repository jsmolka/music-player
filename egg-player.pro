TARGET = egg-player
TEMPLATE = app

RC_ICONS += \
    resource/images/egg/egg.ico

QT += \
    core \
    widgets \
    multimedia \
    sql

INCLUDEPATH += \
    ext/taglib/include \
    src/constants \
    src/core \
    src/ui/components \
    src/ui/layouts \
    src/ui \
    src/utils

LIBS += \
    -L"$$PWD/ext/taglib/lib" -ltag.dll

HEADERS += \
    src/core/audio.hpp \
    src/core/audiolist.hpp \
    src/core/library.hpp \
    src/core/player.hpp \
    src/ui/components/iconbutton.hpp \
    src/ui/components/songinfo.hpp \
    src/ui/layouts/borderlayout.hpp \
    src/utils/fileutil.hpp \
    src/ui/eggplayer.hpp \
    src/ui/musicbar.hpp \
    src/ui/musiclibrary.hpp \
    src/core/cache.hpp \
    src/utils/colorutil.hpp \
    src/ui/components/lengthslider.hpp \
    src/constants/constants.hpp \
    src/core/config.hpp \
    src/core/timer.hpp

SOURCES += \
    src/main.cpp \
    src/core/audio.cpp \
    src/core/audiolist.cpp \
    src/core/library.cpp \
    src/core/player.cpp \
    src/ui/components/iconbutton.cpp \
    src/ui/components/songinfo.cpp \
    src/ui/layouts/borderlayout.cpp \
    src/utils/fileutil.cpp \
    src/ui/eggplayer.cpp \
    src/ui/musicbar.cpp \
    src/ui/musiclibrary.cpp \
    src/core/cache.cpp \
    src/utils/colorutil.cpp \
    src/ui/components/lengthslider.cpp \
    src/constants/constants.cpp \
    src/core/config.cpp \
    src/core/timer.cpp
