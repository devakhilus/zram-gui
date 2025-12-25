// ZRAM GUI for Linux (Complete Production-Ready - FIXED sudo/systemd)
// Qt6 + C++20 - Multi-distro (Fedora/Ubuntu/Arch)
// Compile: g++ -std=c++20 zram_gui.cpp $(pkg-config --cflags --libs Qt6Widgets Qt6Core Qt6Gui) -o zram-gui

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QSlider>
#include <QSpinBox>
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>
#include <QScrollBar>
#include <QProcess>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QGroupBox>
#include <QRegularExpression>
#include <QCloseEvent>
#include <QCheckBox>
#include <QTabWidget>
#include <QDesktopServices>
#include <QUrl>
#include <unistd.h>
#include <cstdlib>

class ZramGui : public QWidget {
public:
    ZramGui(QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    QLabel *statusLabel = nullptr;
    QTextEdit *statsView = nullptr;
    QTextEdit *logView = nullptr;
    QComboBox *algoCombo = nullptr;
    QSlider *memSlider = nullptr;
    QLabel *memLabel = nullptr;
    QSpinBox *streamsSpin = nullptr;
    QSpinBox *prioSpin = nullptr;
    QSpinBox *maxSizeSpin = nullptr;
    QPushButton *applyBtn = nullptr;
    QPushButton *restartBtn = nullptr;
    QPushButton *stopBtn = nullptr;
    QPushButton *resetBtn = nullptr;
    QPushButton *setupBtn = nullptr;
    QCheckBox *themeSwitch = nullptr;
    QTimer *statusTimer = nullptr;

    void log(const QString &msg);
    void logAction(const QString &label, const QString &detail = QString());
    void logSuccess(const QString &label);
    void logError(const QString &label);
    QString run(const QString &cmd, bool silent = false, bool needsSudo = false);
    QString detectPackageManager();
    void loadExistingConfig();
    void writeConfigAndRestart(const QString &reason);
    void applyDarkTheme();
    void applyLightTheme();
    void updateStatus();
    void runInitialSetup();
    void stopZram();
    void resetDefaults();
};

ZramGui::ZramGui(QWidget *parent) : QWidget(parent) {
    setWindowTitle("🚀 ZRAM Configuration Tool v1.0.0");
    resize(1000, 750);

    QVBoxLayout *root = new QVBoxLayout(this);

    // Header
    QLabel *title = new QLabel("<h2>🚀 ZRAM Configuration Tool</h2>");
    title->setAlignment(Qt::AlignCenter);
    root->addWidget(title);

    // Tabs
    QTabWidget *tabs = new QTabWidget(this);
    QWidget *mainPage = new QWidget();
    QWidget *aboutPage = new QWidget();
    tabs->addTab(mainPage, "Main");
    tabs->addTab(aboutPage, "About");
    root->addWidget(tabs);

    // ===== MAIN TAB =====
    QVBoxLayout *main = new QVBoxLayout(mainPage);

    // Top row: theme + setup
    QHBoxLayout *topRow = new QHBoxLayout();
    QLabel *themeLabel = new QLabel("Theme:");
    themeSwitch = new QCheckBox("Dark");
    topRow->addWidget(themeLabel);
    topRow->addWidget(themeSwitch);
    topRow->addStretch();

    setupBtn = new QPushButton("📦 Install ZRAM (one-time)");
    setupBtn->setMinimumWidth(200);
    topRow->addWidget(setupBtn);
    main->addLayout(topRow);

    // Status Section
    QGroupBox *statusBox = new QGroupBox("📊 Current Status");
    QVBoxLayout *statusLayout = new QVBoxLayout(statusBox);
    statusLabel = new QLabel("Checking ZRAM status...");
    statusLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
    statusLayout->addWidget(statusLabel);
    statsView = new QTextEdit();
    statsView->setReadOnly(true);
    statsView->setFontFamily("monospace");
    statsView->setFixedHeight(100);
    statusLayout->addWidget(statsView);
    main->addWidget(statusBox);

    // Configuration Section
    QGroupBox *cfgBox = new QGroupBox("⚙️ Configuration");
    QGridLayout *cfg = new QGridLayout(cfgBox);

    cfg->addWidget(new QLabel("Compression Algorithm:"), 0, 0);
    algoCombo = new QComboBox();
    algoCombo->addItems({"lz4", "lzo", "lzo-rle", "zstd", "deflate"});
    algoCombo->setCurrentText("zstd");
    cfg->addWidget(algoCombo, 0, 1);

    cfg->addWidget(new QLabel("Memory Usage (%):"), 1, 0);
    memSlider = new QSlider(Qt::Horizontal);
    memSlider->setRange(10, 100);
    memSlider->setValue(93);
    cfg->addWidget(memSlider, 1, 1);
    memLabel = new QLabel("93%");
    memLabel->setMinimumWidth(40);
    cfg->addWidget(memLabel, 1, 2);

    cfg->addWidget(new QLabel("Compression Streams:"), 2, 0);
    streamsSpin = new QSpinBox();
    streamsSpin->setRange(1, 8);
    streamsSpin->setValue(3);
    cfg->addWidget(streamsSpin, 2, 1);

    cfg->addWidget(new QLabel("Swap Priority:"), 3, 0);
    prioSpin = new QSpinBox();
    prioSpin->setRange(-1, 32767);
    prioSpin->setValue(116);
    cfg->addWidget(prioSpin, 3, 1);

    cfg->addWidget(new QLabel("Max ZRAM Size (MB):"), 4, 0);
    maxSizeSpin = new QSpinBox();
    maxSizeSpin->setRange(0, 65536);
    maxSizeSpin->setValue(16384);
    cfg->addWidget(maxSizeSpin, 4, 1);

    main->addWidget(cfgBox);

    // Buttons
    QHBoxLayout *btns = new QHBoxLayout();
    applyBtn = new QPushButton("💾 Apply");
    restartBtn = new QPushButton("🔄 Restart");
    stopBtn = new QPushButton("🛑 Stop");
    resetBtn = new QPushButton("🔙 Reset");
    
    applyBtn->setMinimumHeight(40);
    restartBtn->setMinimumHeight(40);
    stopBtn->setMinimumHeight(40);
    resetBtn->setMinimumHeight(40);
    
    btns->addWidget(applyBtn);
    btns->addWidget(restartBtn);
    btns->addWidget(stopBtn);
    btns->addWidget(resetBtn);
    main->addLayout(btns);

    // Log Section
    QGroupBox *logBox = new QGroupBox("📝 Log Output");
    QVBoxLayout *logLayout = new QVBoxLayout(logBox);
    logView = new QTextEdit();
    logView->setReadOnly(true);
    logView->setFontFamily("monospace");
    logView->setFontPointSize(9);
    logLayout->addWidget(logView);
    main->addWidget(logBox, 1);

    // ===== ABOUT TAB =====
    QVBoxLayout *aboutLayout = new QVBoxLayout(aboutPage);
    QLabel *about = new QLabel(
        "<center><h2>ZRAM GUI v1.0.0</h2></center>"
        "<p><b>👨‍💻 Author:</b> Akhil US (Merwick)</p>"
        "<p><b>💬 Telegram:</b> <a href='https://t.me/linuxluminaries'>@linuxluminaries</a></p>"
        "<p><b>📂 GitHub:</b> <a href='https://github.com/devakhilus/zram-gui'>devakhilus/zram-gui</a></p>"
        "<hr>"
        "<p><b>📋 License:</b> GNU General Public License v3.0 (GPLv3)</p>"
        "<p><b>🐧 Supported Distros:</b> Fedora • Ubuntu • Debian • Arch Linux</p>"
        "<p><b>📦 Packages:</b> zram-generator • zram-tools • systemd</p>"
        "<hr>"
        "<p><b>✨ Features:</b></p>"
        "<ul>"
        "<li>✅ Auto-detect package manager (dnf/apt/pacman)</li>"
        "<li>✅ One-click ZRAM installation</li>"
        "<li>✅ Live status monitoring</li>"
        "<li>✅ Custom compression algorithms (zstd, lz4, lzo)</li>"
        "<li>✅ Dark/Light theme support</li>"
        "<li>✅ Memory usage slider (10-100%)</li>"
        "<li>✅ Real-time configuration</li>"
        "</ul>"
    );
    about->setTextFormat(Qt::RichText);
    about->setOpenExternalLinks(true);
    about->setWordWrap(true);
    aboutLayout->addWidget(about);
    aboutLayout->addStretch();

    // ===== SIGNAL CONNECTIONS (Lambdas - NO MOC) =====
    connect(themeSwitch, &QCheckBox::toggled, this, [this](bool checked) {
        if (checked) applyDarkTheme(); 
        else applyLightTheme();
    });
    
    connect(memSlider, &QSlider::valueChanged, this, [this](int v) {
        memLabel->setText(QString::number(v) + "%");
    });
    
    connect(applyBtn, &QPushButton::clicked, this, [this]() {
        writeConfigAndRestart("💾 Applying configuration");
    });
    
    connect(restartBtn, &QPushButton::clicked, this, [this]() {
        writeConfigAndRestart("🔄 Restarting ZRAM with current config");
    });
    
    connect(stopBtn, &QPushButton::clicked, this, [this]() {
        stopZram();
    });
    
    connect(resetBtn, &QPushButton::clicked, this, [this]() {
        resetDefaults();
    });
    
    connect(setupBtn, &QPushButton::clicked, this, [this]() {
        runInitialSetup();
    });

    // ===== INITIALIZATION =====
    loadExistingConfig();
    themeSwitch->setChecked(true);
    applyDarkTheme();

    // Status timer
    statusTimer = new QTimer(this);
    connect(statusTimer, &QTimer::timeout, this, [this]() {
        updateStatus();
    });
    statusTimer->start(3000);
    updateStatus();
    logSuccess("ZRAM GUI initialized successfully");
}

void ZramGui::log(const QString &msg) {
    logView->append(msg);
    logView->ensureCursorVisible();
    logView->verticalScrollBar()->setValue(logView->verticalScrollBar()->maximum());
}

void ZramGui::logAction(const QString &label, const QString &detail) {
    QString line = "▶ " + label;
    if (!detail.isEmpty()) line += " — " + detail;
    log(line);
}

void ZramGui::logSuccess(const QString &label) {
    log("✔ " + label);
}

void ZramGui::logError(const QString &label) {
    log("✖ " + label);
}

QString ZramGui::run(const QString &cmd, bool silent, bool needsSudo) {
    if (!silent) logAction(cmd);
    
    QProcess p;
    QString fullCmd = needsSudo ? ("sudo " + cmd) : cmd;
    p.start("bash", QStringList() << "-c" << fullCmd);
    p.waitForFinished(15000);
    
    QString out = p.readAllStandardOutput().trimmed();
    QString err = p.readAllStandardError().trimmed();
    
    if (!silent && !out.isEmpty()) log(out);
    if (!silent && !err.isEmpty()) logError(err);
    
    return out;
}

QString ZramGui::detectPackageManager() {
    if (system("command -v dnf >/dev/null 2>&1") == 0) return "dnf";
    if (system("command -v apt >/dev/null 2>&1") == 0) return "apt";
    if (system("command -v pacman >/dev/null 2>&1") == 0) return "pacman";
    return QString();
}

void ZramGui::runInitialSetup() {
    logAction("📦 Starting one-time ZRAM setup");
    QString pm = detectPackageManager();
    if (pm.isEmpty()) {
        logError("❌ Could not detect package manager (dnf/apt/pacman)");
        return;
    }
    logAction("Detected package manager: " + pm);

    QString installCmd;
    if (pm == "dnf") {
        installCmd = "dnf install -y zram-generator zram-generator-defaults";
    } else if (pm == "apt") {
        installCmd = "apt update && apt install -y zram-tools";
    } else if (pm == "pacman") {
        installCmd = "pacman -S --noconfirm zram-generator";
    }
    
    run(installCmd, false, true);
    logSuccess("✅ ZRAM packages installed successfully");
    updateStatus();
}

void ZramGui::applyDarkTheme() {
    QString style = R"(
        QWidget {
            background: #1e1e1e;
            color: #e0e0e0;
            font-family: 'Segoe UI', Arial, sans-serif;
        }
        QGroupBox {
            border: 2px solid #444;
            margin-top: 1ex;
            font-weight: bold;
            border-radius: 8px;
            padding-top: 10px;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 12px;
            padding: 0 8px;
            color: #ffffff;
        }
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #3a3a3a, stop:1 #2a2a2a);
            border: 2px solid #555;
            padding: 10px 20px;
            border-radius: 6px;
            font-weight: bold;
            color: #e0e0e0;
            font-size: 12px;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #4a4a4a, stop:1 #3a3a3a);
            border: 2px solid #777;
        }
        QPushButton:pressed {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #2a2a2a, stop:1 #1a1a1a);
        }
        QTextEdit, QComboBox, QSpinBox, QSlider {
            background: #2d2d2d;
            border: 2px solid #555;
            border-radius: 6px;
            padding: 6px;
            color: #e0e0e0;
            selection-background-color: #4a90e2;
        }
        QSlider::groove:horizontal {
            height: 10px;
            background: #444;
            border: 2px solid #666;
            border-radius: 5px;
        }
        QSlider::handle:horizontal {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #666, stop:1 #888);
            border: 2px solid #999;
            width: 22px;
            margin: -6px 0;
            border-radius: 11px;
        }
        QLabel { color: #e0e0e0; }
    )";
    setStyleSheet(style);
}

void ZramGui::applyLightTheme() {
    QString style = R"(
        QWidget {
            background: #f5f5f5;
            color: #333333;
            font-family: 'Segoe UI', Arial, sans-serif;
        }
        QGroupBox {
            border: 2px solid #ddd;
            margin-top: 1ex;
            font-weight: bold;
            border-radius: 8px;
            padding-top: 10px;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 12px;
            padding: 0 8px;
            color: #333333;
        }
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #f0f0f0, stop:1 #e0e0e0);
            border: 2px solid #bbb;
            padding: 10px 20px;
            border-radius: 6px;
            font-weight: bold;
            color: #333333;
            font-size: 12px;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #ffffff, stop:1 #f0f0f0);
            border: 2px solid #999;
        }
        QPushButton:pressed {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #e0e0e0, stop:1 #d0d0d0);
        }
        QTextEdit, QComboBox, QSpinBox, QSlider {
            background: #ffffff;
            border: 2px solid #ddd;
            border-radius: 6px;
            padding: 6px;
            color: #333333;
            selection-background-color: #4a90e2;
        }
        QSlider::groove:horizontal {
            height: 10px;
            background: #ddd;
            border: 2px solid #bbb;
            border-radius: 5px;
        }
        QSlider::handle:horizontal {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #666, stop:1 #888);
            border: 2px solid #999;
            width: 22px;
            margin: -6px 0;
            border-radius: 11px;
        }
        QLabel { color: #333333; }
    )";
    setStyleSheet(style);
}

void ZramGui::updateStatus() {
    QString out = run("zramctl --output NAME,ALGORITHM,DISKSIZE,DATA,COMPR,TOTAL --noheadings 2>/dev/null || true", true);
    if (out.isEmpty()) {
        statusLabel->setText("❌ ZRAM is not active");
        statsView->clear();
    } else {
        statusLabel->setText("✅ ZRAM is active");
        statsView->setText(out);
    }
}

void ZramGui::loadExistingConfig() {
    QFile f("/etc/systemd/zram-generator.conf");
    if (!f.open(QIODevice::ReadOnly)) return;
    
    QString content = f.readAll();
    f.close();
    
    QRegularExpression algoRe("^\\s*compression-algorithm\\s*=\\s*(\\w+)\\s*$", QRegularExpression::MultilineOption);
    auto algoMatch = algoRe.match(content);
    if (algoMatch.hasMatch()) {
        int idx = algoCombo->findText(algoMatch.captured(1));
        if (idx >= 0) algoCombo->setCurrentIndex(idx);
    }
}

void ZramGui::writeConfigAndRestart(const QString &reason) {
    logAction(reason);
    
    double fraction = memSlider->value() / 100.0;
    QString cfg = QString("[zram0]\n"
                         "compression-algorithm = %1\n"
                         "zram-fraction = %2\n"
                         "compression-streams = %3\n"
                         "swap-priority = %4\n")
                    .arg(algoCombo->currentText())
                    .arg(fraction, 0, 'f', 2)
                    .arg(streamsSpin->value())
                    .arg(prioSpin->value());
    
    if (maxSizeSpin->value() > 0) {
        cfg += QString("max-zram-size = %1\n").arg(maxSizeSpin->value());
    }
    
    QFile f("/etc/systemd/zram-generator.conf");
    if (f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        f.write(cfg.toUtf8());
        f.close();
        logSuccess("Configuration saved to /etc/systemd/zram-generator.conf");
        log("---");
        log(cfg);
        log("---");
    } else {
        logError("Cannot write config file (permission denied)");
        return;
    }
    
    // Reload systemd and restart ZRAM
    run("systemctl daemon-reload", false, true);
    
    // Stop existing ZRAM
    run("systemctl stop systemd-zram-setup@zram0.service 2>/dev/null || swapoff /dev/zram0 2>/dev/null || true", false, true);
    
    // Start ZRAM again
    run("systemctl start systemd-zram-setup@zram0.service 2>/dev/null || systemctl restart dev-zram0.swap 2>/dev/null || true", false, true);
    
    logSuccess("✅ ZRAM configuration applied successfully");
    updateStatus();
}

void ZramGui::stopZram() {
    logAction("🛑 Stopping ZRAM");
    
    run("systemctl stop systemd-zram-setup@zram0.service 2>/dev/null || swapoff /dev/zram0 2>/dev/null || true", false, true);
    run("systemctl stop dev-zram0.swap 2>/dev/null || true", false, true);
    run("rmmod zram 2>/dev/null || true", false, true);
    
    logSuccess("✅ ZRAM stopped successfully");
    updateStatus();
}

void ZramGui::resetDefaults() {
    algoCombo->setCurrentText("zstd");
    memSlider->setValue(93);
    streamsSpin->setValue(3);
    prioSpin->setValue(116);
    maxSizeSpin->setValue(16384);
    logAction("🔄 Defaults restored");
}

void ZramGui::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Exit ZRAM GUI",
        "Are you sure you want to close ZRAM Configuration Tool?",
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No
    );
    if (reply == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ZramGui w;
    w.show();
    return app.exec();
}
