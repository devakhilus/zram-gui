FROM fedora:43

RUN dnf update -y && \
    dnf install -y \
    gcc-c++ \
    qt6-qtbase-devel \
    qt6-qtbase-gui \
    pkgconfig \
    zram-generator \
    zram-generator-defaults \
    zramctl \
    procps-ng \
    bash \
    dbus \
    && dnf clean all

WORKDIR /app
COPY zram_gui.cpp .
RUN g++ -std=c++20 -O2 zram_gui.cpp \
    $(pkg-config --cflags --libs Qt6Widgets Qt6Core Qt6Gui) \
    -o zram-gui && \
    chmod +x zram-gui

ENV QT_QPA_PLATFORM=xcb
CMD ["./zram-gui"]
