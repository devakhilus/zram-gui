# 🚀 ZRAM GUI v1.0.0

**Professional ZRAM Compression Utility for Linux** • **Qt6** • **C++20** • **Multi-Distro**

![Status](https://img.shields.io/badge/Status-Production%20Ready-green)
![License](https://img.shields.io/badge/License-GPLv3-blue)
![Platform](https://img.shields.io/badge/Platform-Linux-orange)

---

## ⚡ INSTALL IN ONE LINE

```bash
bash <(wget -qO- https://raw.githubusercontent.com/devakhilus/zram-gui/main/zram-install.sh)
```

**Automatic setup includes:**
- Binary installation
- Applications menu entry
- Bash alias (`zram`)
- Passwordless sudo

---

## 🎯 After Installation

### **Launch from Terminal:**
```bash
zram
```

### **Launch from Applications Menu:**
Search for "ZRAM Configuration Tool"

### **Direct Command:**
```bash
sudo /usr/local/bin/zram-gui
```

---

## ✨ Features

| Feature | Description |
|---------|-------------|
| 🎨 **Dark/Light Theme** | Beautiful UI with theme switcher |
| 📊 **Live Monitoring** | Real-time ZRAM statistics & status |
| ⚙️ **Easy Configuration** | Sliders & spinners for all settings |
| 🔧 **Compression Algorithms** | zstd, lz4, lzo, lzo-rle, deflate |
| 🐧 **Multi-Distro** | Fedora, Ubuntu, Debian, Arch |
| 🔐 **Secure** | Limited passwordless sudo for binary only |
| 📦 **Auto-Setup** | One-command installation with menu integration |
| 🪟 **Desktop Integration** | Applications menu entry created automatically |
| ⌨️ **Alias Support** | Just type `zram` to launch |
| 🎯 **One-Click Install** | Detects & installs ZRAM packages automatically |

---

## 📋 What's Included

### **Main Application**
- Qt6-based GUI
- Real-time ZRAM status
- Configuration management
- Compression statistics

### **Installation Tools**
- `zram-install.sh` - Complete one-liner installation
- Desktop menu integration
- Bash alias configuration
- Passwordless sudo setup

### **Documentation**
- Installation guide
- Troubleshooting tips
- Configuration examples

---

## 🐧 Supported Systems

**Distributions:**
- Fedora 40+
- Ubuntu 20.04+
- Debian 11+
- Arch Linux
- openSUSE
- Any systemd-based Linux

**Requirements:**
- Qt6 libraries
- systemd
- sudo access

---

## 🚀 Installation Methods

### Method 1: One-Line (Recommended)
```bash
bash <(wget -qO- https://raw.githubusercontent.com/devakhilus/zram-gui/main/zram-install.sh)
```

### Method 2: Using curl
```bash
bash <(curl -sL https://raw.githubusercontent.com/devakhilus/zram-gui/main/zram-install.sh)
```

### Method 3: Manual Download
```bash
wget https://raw.githubusercontent.com/devakhilus/zram-gui/main/zram-install.sh
chmod +x zram-install.sh
./zram-install.sh
```

---

## 🔧 Usage Guide

### **Basic Usage**
1. Launch: `zram` (or use Applications menu)
2. Click "Install ZRAM" button
3. Configure settings
4. Click "Apply"

### **Configuration Options**
- **Compression Algorithm** - Choose compression method
- **Memory Usage** - Set ZRAM size (10-100%)
- **Compression Streams** - Number of threads
- **Swap Priority** - System priority level
- **Max Size** - Maximum ZRAM size in MB

### **Quick Actions**
- **Apply** - Save and apply configuration
- **Restart** - Restart ZRAM with current settings
- **Stop** - Disable ZRAM temporarily
- **Reset** - Return to default settings

---

## 📸 Screenshots

### Main Interface
- Dark theme by default
- Live ZRAM status display
- Configuration controls
- Real-time log output

### Menu Integration
- Applications → ZRAM Configuration Tool
- Quick launcher with description
- Desktop entry with icon

---

## 💬 Support

- **GitHub Issues**: https://github.com/devakhilus/zram-gui/issues
- **Telegram Community**: https://t.me/linuxluminaries
- **Author**: Akhil US (Merwick)

---

## 📄 License

**GNU General Public License v3.0 (GPLv3)**

You are free to use, modify, and distribute this software under the terms of the GPL v3 license.

---

## 🙏 Contributing

Contributions welcome!

1. Fork the repository
2. Create feature branch (`git checkout -b feature/YourFeature`)
3. Commit changes (`git commit -m 'Add YourFeature'`)
4. Push branch (`git push origin feature/YourFeature`)
5. Open Pull Request

---

## 📦 Version Information

- **Version**: 1.0.0
- **Release Date**: December 2025
- **Build**: Qt6 + C++20
- **Status**: Production Ready ✅

---

## 🔄 Quick Commands

```bash
# Install
bash <(wget -qO- https://raw.githubusercontent.com/devakhilus/zram-gui/main/zram-install.sh)

# Launch
zram

# Manual launch
sudo /usr/local/bin/zram-gui

# Uninstall
sudo rm -f /usr/local/bin/zram-gui /usr/share/applications/zram-gui.desktop /etc/sudoers.d/zram-gui
```

---

## ⚠️ Important Notes

1. **ZRAM requires root access** - Some operations need sudo
2. **System impact** - ZRAM affects swap behavior globally
3. **Automatic package detection** - Works on any distro
4. **Safe defaults** - Conservative initial settings

---

## 🎓 About ZRAM

ZRAM is a Linux kernel module that creates a compressed block device in RAM. It's useful for:
- Extending effective RAM capacity
- Reducing swap I/O
- Improving system responsiveness
- Better memory management on low-end hardware

---

**Ready to compress? Just copy that one-liner! 🚀**

```bash
bash <(wget -qO- https://raw.githubusercontent.com/devakhilus/zram-gui/main/zram-install.sh)
```

*Made with ❤️ by Akhil US*
