// ZRAM GUI for Linux (Enhanced, multi-distro)
// Qt6 + C++20
// Compile:
// g++ -std=c++20 zram_gui.cpp $(pkg-config --cflags --libs Qt6Widgets Qt6Core Qt6Gui) -o zram-gui

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

class ZramGui : public QWidget {
public:
    ZramGui() {
        setWindowTitle("ZRAM Configuration Tool ");
        resize(980, 720);

        QVBoxLayout *root = new QVBoxLayout(this);

        // ===== Header =====
        QLabel *title = new QLabel("<h2>ZRAM Configuration Tool </h2>");
        title->setAlignment(Qt::AlignCenter);
        root->addWidget(title);

        // ===== Tabs =====
        QTabWidget *tabs = new QTabWidget(this);
        QWidget *mainPage = new QWidget(this);
        QWidget *aboutPage = new QWidget(this);
        tabs->addTab(mainPage, "Main");
        tabs->addTab(aboutPage, "About");
        root->addWidget(tabs);

        // ===== Main tab layout =====
        QVBoxLayout *main = new QVBoxLayout(mainPage);

        // Top row: theme + setup
        QHBoxLayout *topRow = new QHBoxLayout();
        QLabel *themeLabel = new QLabel("Theme:");
        themeSwitch = new QCheckBox("Stop - Restart | Stop - Apply ");
        topRow->addWidget(themeLabel);
        topRow->addWidget(themeSwitch);
        topRow->addStretch();

        setupBtn = new QPushButton("Install ZRAM if not (one-time)");
        topRow->addWidget(setupBtn);
        main->addLayout(topRow);

        connect(themeSwitch, &QCheckBox::toggled,
                this, &ZramGui::setThemeChecked);
        connect(setupBtn, &QPushButton::clicked,
                this, &ZramGui::runInitialSetup);

        // ===== Status =====
        QGroupBox *statusBox = new QGroupBox("Current Status");
        QVBoxLayout *statusLayout = new QVBoxLayout(statusBox);
        statusLabel = new QLabel("Checking ZRAM status...");
        statusLayout->addWidget(statusLabel);
        statsView = new QTextEdit();
        statsView->setReadOnly(true);
        statsView->setFontFamily("monospace");
        statsView->setFixedHeight(130);
        statusLayout->addWidget(statsView);
        main->addWidget(statusBox);

        // ===== Configuration =====
        QGroupBox *cfgBox = new QGroupBox("Configuration");
        QGridLayout *cfg = new QGridLayout(cfgBox);

        cfg->addWidget(new QLabel("Compression Algorithm:"), 0, 0);
        algoCombo = new QComboBox();
        algoCombo->addItems({"lz4", "lzo", "lzo-rle", "zstd", "deflate"});
        cfg->addWidget(algoCombo, 0, 1);

        cfg->addWidget(new QLabel("Memory Limit (% RAM):"), 1, 0);
        memSlider = new QSlider(Qt::Horizontal);
        memSlider->setRange(10, 100);
        memSlider->setValue(93);
        cfg->addWidget(memSlider, 1, 1);
        memLabel = new QLabel("93%");
        cfg->addWidget(memLabel, 1, 2);
        connect(memSlider, &QSlider::valueChanged, this, [&](int v) {
            memLabel->setText(QString::number(v) + "%");
        });

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

        cfg->addWidget(new QLabel("Max ZRAM size (MB, 0=default):"), 4, 0);
        maxSizeSpin = new QSpinBox();
        maxSizeSpin->setRange(0, 65536);
        maxSizeSpin->setValue(16384);
        cfg->addWidget(maxSizeSpin, 4, 1);

        main->addWidget(cfgBox);

        // ===== Buttons =====
        QHBoxLayout *btns = new QHBoxLayout();
        applyBtn   = new QPushButton("Apply");
        restartBtn = new QPushButton("Restart");
        stopBtn    = new QPushButton("Stop");
        resetBtn   = new QPushButton("Reset");
        btns->addWidget(applyBtn);
        btns->addWidget(restartBtn);
        btns->addWidget(stopBtn);
        btns->addWidget(resetBtn);
        main->addLayout(btns);

        // ===== Log =====
        QGroupBox *logBox = new QGroupBox("Log Output");
        QVBoxLayout *logLayout = new QVBoxLayout(logBox);
        logView = new QTextEdit();
        logView->setReadOnly(true);
        logView->setFontFamily("monospace");
        logLayout->addWidget(logView);
        main->addWidget(logBox, 1);

        connect(applyBtn,   &QPushButton::clicked, this, &ZramGui::applyConfig);
        connect(restartBtn, &QPushButton::clicked, this, &ZramGui::restartZram);
        connect(stopBtn,    &QPushButton::clicked, this, &ZramGui::stopZram);
        connect(resetBtn,   &QPushButton::clicked, this, &ZramGui::resetDefaults);

        // ===== About tab =====
        QVBoxLayout *aboutLayout = new QVBoxLayout(aboutPage);

        QLabel *author = new QLabel(
            "<b>Author:</b> Akhil US (Merwick)\n"
            "<b>Telegram:</b> <a href=\"https://t.me/linuxluminaries\">@linuxluminaries</a>\n"
            "<b>Repository:</b> <a href=\"https://github.com/devakhilus/zram-gui\">GitHub: zram-gui</a>");
        author->setTextFormat(Qt::RichText);
        author->setTextInteractionFlags(Qt::TextBrowserInteraction);
        author->setOpenExternalLinks(true);
        aboutLayout->addWidget(author);

        QLabel *license = new QLabel(
            "<b>License:</b> GNU General Public License v3.0 (GPLv3)<br>"
            "This program is free software: you can redistribute it and/or modify it "
            "under the terms of the GNU General Public License as published by the "
            "Free Software Foundation, either version 3 of the License, or (at your "
            "option) any later version.<br><br>"
            "You should have received a copy of the GNU General Public License along "
            "with this program; if not, see "
            "<a href=\"https://www.gnu.org/licenses/gpl-3.0.html\">https://www.gnu.org/licenses/gpl-3.0.html</a>.");
        license->setWordWrap(true);
        license->setTextFormat(Qt::RichText);
        license->setTextInteractionFlags(Qt::TextBrowserInteraction);
        license->setOpenExternalLinks(true);
        aboutLayout->addWidget(license);

        aboutLayout->addStretch(1);

        // ===== Init config/theme/status =====
        loadExistingConfig();
        themeSwitch->setChecked(true);
        applyDarkTheme();

        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &ZramGui::updateStatus);
        timer->start(3000);
        updateStatus();
    }

protected:
    void closeEvent(QCloseEvent *event) override {
        auto reply = QMessageBox::question(
            this,
            "Exit",
            "Are you sure you want to close the ZRAM tool?",
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No
        );
        if (reply == QMessageBox::Yes) {
            event->accept();
        } else {
            event->ignore();
        }
    }

private:
    QLabel *statusLabel;
    QTextEdit *statsView;
    QTextEdit *logView;
    QComboBox *algoCombo;
    QSlider *memSlider;
    QLabel *memLabel;
    QSpinBox *streamsSpin;
    QSpinBox *prioSpin;
    QSpinBox *maxSizeSpin;
    QPushButton *applyBtn;
    QPushButton *restartBtn;
    QPushButton *stopBtn;
    QPushButton *resetBtn;
    QPushButton *setupBtn;
    QCheckBox *themeSwitch;

    void log(const QString &msg) {
        logView->append(msg);
        logView->setStyleSheet("QTextEdit { background-color: #333333; }");
        QTimer::singleShot(120, this, [this]() {
            logView->setStyleSheet("");
        });
    }

    void logAction(const QString &label, const QString &detail = QString()) {
        QString line = "▶ " + label;
        if (!detail.isEmpty())
            line += " — " + detail;
        log(line);
    }
    void logSuccess(const QString &label) {
        log("✔ " + label);
    }
    void logError(const QString &label) {
        log("✖ " + label);
    }

    QString run(const QString &cmd, bool silent = false) {
        if (!silent)
            logAction(cmd);
        QProcess p;
        p.start("bash", {"-c", cmd});
        p.waitForFinished(-1);
        QString out = QString::fromLocal8Bit(p.readAllStandardOutput()).trimmed();
        QString err = QString::fromLocal8Bit(p.readAllStandardError()).trimmed();
        if (!silent && !out.isEmpty())
            log(out);
        if (!silent && !err.isEmpty())
            logError(err);
        return out;
    }

    QString detectPackageManager() {
        if (!run("command -v dnf >/dev/null 2>&1; echo $?", true).toInt())
            return "dnf";
        if (!run("command -v apt >/dev/null 2>&1; echo $?", true).toInt())
            return "apt";
        if (!run("command -v pacman >/dev/null 2>&1; echo $?", true).toInt())
            return "pacman";
        return QString();
    }

    void runInitialSetup() {
        logAction("One-time ZRAM setup");

        QString pm = detectPackageManager();
        if (pm.isEmpty()) {
            logError("Could not detect package manager (dnf/apt/pacman).");
            QMessageBox::warning(this, "Setup", "Could not detect package manager.");
            return;
        }

        logAction("Detected package manager", pm);

        QString installCmd;
        if (pm == "dnf") {
            installCmd = "dnf install -y zram-generator zram-generator-defaults";
        } else if (pm == "apt") {
            installCmd = "apt update && apt install -y systemd-zram-generator";
        } else if (pm == "pacman") {
            installCmd = "pacman -S --noconfirm zram-generator";
        }

        if (!installCmd.isEmpty()) {
            run(installCmd);
        }

        if (!QFile::exists("/etc/systemd/zram-generator.conf")) {
            logAction("Creating default config", "/etc/systemd/zram-generator.conf");
            double fraction = static_cast<double>(memSlider->value()) / 100.0;
            QString cfg;
            cfg += "[zram0]\n";
            cfg += "compression-algorithm = " + algoCombo->currentText() + "\n";
            cfg += "zram-fraction = " + QString::number(fraction, 'f', 2) + "\n";
            if (maxSizeSpin->value() > 0)
                cfg += "max-zram-size = " + QString::number(maxSizeSpin->value()) + "\n";
            cfg += "swap-priority = " + QString::number(prioSpin->value()) + "\n";
            cfg += "compression-streams = " + QString::number(streamsSpin->value()) + "\n";

            QFile f("/etc/systemd/zram-generator.conf");
            if (f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
                QTextStream s(&f);
                s << cfg;
                f.close();
            }
        }

        run("systemctl daemon-reload");
        run("swapoff /dev/zram0 2>/dev/null || true");
        run("systemctl restart systemd-zram-setup@zram\\* 2>/dev/null || "
            "systemctl restart dev-zram0.swap 2>/dev/null || true");

        logSuccess("Setup completed (you may need to reboot on some distros)");
        updateStatus();
    }

    void setThemeChecked(bool checked) {
        if (checked) {
            applyDarkTheme();
        } else {
            applyLightTheme();
        }
    }

    void applyDarkTheme() {
        QString style = R"(
            QWidget { background-color: #121212; color: #f0f0f0; }
            QGroupBox { border: 1px solid #444444; margin-top: 6px; }
            QGroupBox::title { subcontrol-origin: margin; left: 8px; padding: 0 4px; }

            QPushButton {
                background-color: #1e1e1e;
                border: 1px solid #555555;
                padding: 4px 10px;
            }
            QPushButton:hover { background-color: #2a2a2a; }
            QPushButton:pressed { background-color: #333333; }

            QSlider::groove:horizontal {
                border: 1px solid #444444;
                height: 6px;
                background: #1e1e1e;
            }
            QSlider::handle:horizontal {
                background: #dddddd;
                border: 1px solid #777777;
                width: 14px;
                margin: -4px 0;
                border-radius: 7px;
            }

            QTextEdit, QSpinBox, QComboBox {
                background-color: #1a1a1a;
                border: 1px solid #555555;
                selection-background-color: #3d3d3d;
            }

            QCheckBox::indicator {
                width: 36px;
                height: 18px;
            }
            QCheckBox::indicator:unchecked {
                border-radius: 9px;
                background-color: #555555;
                border: 1px solid #777777;
            }
            QCheckBox::indicator:checked {
                border-radius: 9px;
                background-color: #4caf50;
                border: 1px solid #81c784;
            }
        )";
        qApp->setStyleSheet(style);
    }

    void applyLightTheme() {
        QString style = R"(
            QWidget { background-color: #ffffff; color: #202020; }
            QGroupBox { border: 1px solid #cccccc; margin-top: 6px; }
            QGroupBox::title { subcontrol-origin: margin; left: 8px; padding: 0 4px; }

            QPushButton {
                background-color: #f3f3f3;
                border: 1px solid #b0b0b0;
                padding: 4px 10px;
            }
            QPushButton:hover { background-color: #e5e5e5; }
            QPushButton:pressed { background-color: #dddddd; }

            QTextEdit, QSpinBox, QComboBox {
                background-color: #ffffff;
                border: 1px solid #b0b0b0;
                selection-background-color: #c5cae9;
            }

            QSlider::groove:horizontal {
                border: 1px solid #cccccc;
                height: 6px;
                background: #f3f3f3;
            }
            QSlider::handle:horizontal {
                background: #666666;
                border: 1px solid #888888;
                width: 14px;
                margin: -4px 0;
                border-radius: 7px;
            }

            QCheckBox::indicator {
                width: 36px;
                height: 18px;
            }
            QCheckBox::indicator:unchecked {
                border-radius: 9px;
                background-color: #d0d0d0;
                border: 1px solid #b0b0b0;
            }
            QCheckBox::indicator:checked {
                border-radius: 9px;
                background-color: #4caf50;
                border: 1px solid #388e3c;
            }
        )";
        qApp->setStyleSheet(style);
    }

    void updateStatus() {
        QString out = run("zramctl --output NAME,ALGORITHM,DISKSIZE,DATA,COMPR,TOTAL --noheadings 2>/dev/null", true);
        if (out.isEmpty()) {
            statusLabel->setText("ZRAM is not active");
            statsView->clear();
        } else {
            statusLabel->setText("ZRAM is active");
            statsView->setText(out);
        }
    }

    void loadExistingConfig() {
        QFile f("/etc/systemd/zram-generator.conf");
        if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        QString content = QString::fromUtf8(f.readAll());
        f.close();

        auto getValue = [&](const QString &key, const QString &def) {
            QRegularExpression re(
                "^\\s*" + QRegularExpression::escape(key) +
                "\\s*=\\s*(\\S+)\\s*$",
                QRegularExpression::MultilineOption
            );
            auto m = re.match(content);
            return m.hasMatch() ? m.captured(1) : def;
        };

        QString algo    = getValue("compression-algorithm", algoCombo->currentText());
        QString frac    = getValue("zram-fraction",
                                   QString::number(memSlider->value() / 100.0, 'f', 2));
        QString maxsz   = getValue("max-zram-size", QString::number(maxSizeSpin->value()));
        QString prio    = getValue("swap-priority", QString::number(prioSpin->value()));
        QString streams = getValue("compression-streams", QString::number(streamsSpin->value()));

        int algoIndex = algoCombo->findText(algo);
        if (algoIndex >= 0)
            algoCombo->setCurrentIndex(algoIndex);

        bool ok = false;
        double fFraction = frac.toDouble(&ok);
        if (ok)
            memSlider->setValue(static_cast<int>(fFraction * 100.0));

        maxSizeSpin->setValue(maxsz.toInt());
        prioSpin->setValue(prio.toInt());
        streamsSpin->setValue(streams.toInt());
    }

    void writeConfigAndRestart(const QString &reason) {
        logAction(reason);

        double fraction = static_cast<double>(memSlider->value()) / 100.0;

        QString cfg;
        cfg += "[zram0]\n";
        cfg += "compression-algorithm = " + algoCombo->currentText() + "\n";
        cfg += "zram-fraction = " + QString::number(fraction, 'f', 2) + "\n";

        if (maxSizeSpin->value() > 0) {
            cfg += "max-zram-size = " + QString::number(maxSizeSpin->value()) + "\n";
        }

        cfg += "swap-priority = " + QString::number(prioSpin->value()) + "\n";
        cfg += "compression-streams = " + QString::number(streamsSpin->value()) + "\n";

        QFile f("/etc/systemd/zram-generator.conf");
        if (!f.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
            logError("Failed to write config file");
            return;
        }
        QTextStream s(&f);
        s << cfg;
        f.close();

        logAction("Configuration saved", "/etc/systemd/zram-generator.conf");
        log(cfg);

        run("systemctl daemon-reload");
        run("swapoff /dev/zram0 2>/dev/null || true");
        run("systemctl restart systemd-zram-setup@zram\\* 2>/dev/null || "
            "systemctl restart dev-zram0.swap 2>/dev/null || true");
        logSuccess("ZRAM configuration applied");

        updateStatus();
    }

    void applyConfig() {
        writeConfigAndRestart("Applying ZRAM Configuration");
    }

    void restartZram() {
        writeConfigAndRestart("Restarting ZRAM (re-applying current GUI values)");
    }

    void stopZram() {
        logAction("Stopping ZRAM");
        run("swapoff /dev/zram0 2>/dev/null || true");
        run("rmmod zram 2>/dev/null || true");
        logSuccess("ZRAM stopped");
        updateStatus();
    }

    void resetDefaults() {
        algoCombo->setCurrentText("zstd");
        memSlider->setValue(93);
        streamsSpin->setValue(3);
        prioSpin->setValue(116);
        maxSizeSpin->setValue(16384);
        logAction("Defaults restored");
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ZramGui w;
    w.show();
    return app.exec();
}

