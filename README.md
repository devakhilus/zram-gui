# 🚀 ZRAM GUI v1.0.0

**Professional ZRAM Compression Utility for Linux** • **Qt6** • **C++20** • **Multi-Distro**

![Status](https://img.shields.io/badge/Status-Production%20Ready-green)
![License](https://img.shields.io/badge/License-GPLv3-blue)
![Platform](https://img.shields.io/badge/Platform-Linux-orange)

---

## 📸 Screenshots

### **Main Interface - Configuration Tab**
![ZRAM GUI Main Interface](https://raw.githubusercontent.com/devakhilus/zram-gui/main/pictures/1.png)
- Professional dark theme
- Real-time ZRAM status monitoring
- Easy-to-use configuration sliders
- Live compression statistics

### **System Resources Display**
![System Resources Monitoring](https://raw.githubusercontent.com/devakhilus/zram-gui/main/pictures/2.png)
- Memory usage display (like System Resources)
- Swap allocation overview
- Compression ratio information
- Live memory statistics

### **Advanced Configuration**
![Configuration Panel](https://raw.githubusercontent.com/devakhilus/zram-gui/main/pictures/3.png)
- Compression algorithm selection (zstd, lz4, lzo, etc.)
- Memory usage percentage slider (10-100%)
- Compression streams configuration
- Swap priority settings
- Custom ZRAM size allocation

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
| 📊 **Live Monitoring** | Real-time ZRAM statistics & status (like System Resources) |
| ⚙️ **Easy Configuration** | Sliders & spinners for all settings |
| 🔧 **Compression Algorithms** | zstd, lz4, lzo, lzo-rle, deflate |
| 🐧 **Multi-Distro** | Fedora, Ubuntu, Debian, Arch, openSUSE |
| 🔐 **Secure** | Limited passwordless sudo for binary only |
| 📦 **Auto-Setup** | One-command installation with menu integration |
| 🪟 **Desktop Integration** | Applications menu entry created automatically |
| ⌨️ **Alias Support** | Just type `zram` to launch |
| 🎯 **One-Click Install** | Detects & installs ZRAM packages automatically |

---

## 📋 What's Included

### **Main Application**
- Qt6-based GUI
- Real-time ZRAM status (System Resources style display)
- Configuration management
- Compression statistics
- Live memory monitoring

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
2. Click "Install ZRAM" button (first time only)
3. Configure settings with sliders
4. Click "Apply" to save configuration

### **Configuration Options**
- **Compression Algorithm** - Choose from zstd, lz4, lzo, lzo-rle, deflate
- **Memory Usage** - Set ZRAM size as percentage of RAM (10-100%)
- **Compression Streams** - Number of parallel compression threads (1-8)
- **Swap Priority** - System priority level for ZRAM swap
- **Max Size** - Maximum ZRAM size in MB (0 = auto)

### **Quick Actions**
- **Apply** - Save and apply configuration
- **Restart** - Restart ZRAM with current settings
- **Stop** - Disable ZRAM temporarily
- **Reset** - Return to default settings

### **Real-time Monitoring**
- View current ZRAM compression status
- Monitor system memory usage
- Track swap allocation
- Display compression ratio

---

## 📊 Understanding Size Differences

Your ZRAM configuration displays sizes in different units depending on the tool:

```
Configuration:      8384 MB
lsblk output:       8.2 GiB (binary: 1024-based)
System Resources:   8.8 GB (decimal: 1000-based)
```

**Why the difference?**
- **MB to GiB**: 8384 MiB ÷ 1024 = 8.18 GiB ≈ 8.2 GiB
- **MiB to GB**: 8384 × 1.048576 = 8.79 GB ≈ 8.8 GB

This is completely normal - just different unit conventions!

---

## 💻 Building from Source

### **Requirements**
```bash
# Fedora
sudo dnf install qt6-qtbase-devel gcc g++ cmake

# Ubuntu/Debian
sudo apt install qt6-base-dev build-essential cmake

# Arch
sudo pacman -S qt6-base gcc cmake
```

### **Compile**
```bash
git clone https://github.com/devakhilus/zram-gui.git
cd zram-gui
g++ -std=c++20 zram_gui_complete_v2.cpp $(pkg-config --cflags --libs Qt6Widgets Qt6Core Qt6Gui) -o zram-gui
./zram-gui
```

---

## 🎓 About ZRAM

ZRAM is a Linux kernel module that creates a compressed block device in RAM. Benefits:

- **Extend Effective RAM** - Get more usable memory through compression
- **Reduce Swap I/O** - Compressed data in RAM is faster than disk swap
- **Improve Responsiveness** - Reduced disk thrashing improves system feel
- **Save Power** - Less disk activity = lower power consumption
- **Great for Low-End Hardware** - Especially useful on systems with limited RAM

### **Compression Ratios**
- **zstd**: 2.5-3x (best balance)
- **lz4**: 2x-2.5x (fastest)
- **lzo**: 2-2.5x (medium speed)
- **deflate**: 2.5-3.5x (slowest)

---

## 🔒 Security

- ✅ **Passwordless Sudo** - Only for the ZRAM GUI binary
- ✅ **Configuration Protection** - Config file is protected
- ✅ **No External Dependencies** - Self-contained binary
- ✅ **GPLv3 License** - Open source and transparent

---

## 💬 Support

- **GitHub Issues**: [https://github.com/devakhilus/zram-gui/issues](https://github.com/devakhilus/zram-gui/issues)
- **Telegram Community**: [https://t.me/linuxluminaries](https://t.me/linuxluminaries)
- **Email**: devakhilus@gmail.com
- **Author**: Akhil US (Merwick)

---

## 📄 License

**GNU General Public License v3.0 (GPLv3)**

You are free to use, modify, and distribute this software under the terms of the GPL v3 license.

See [LICENSE](LICENSE) file for details.

---

## 🙏 Contributing

Contributions are welcome! Help improve ZRAM GUI:

1. **Fork** the repository
2. **Create** feature branch (`git checkout -b feature/YourFeature`)
3. **Commit** changes (`git commit -m 'Add YourFeature'`)
4. **Push** branch (`git push origin feature/YourFeature`)
5. **Open** Pull Request

### **Ideas for Contributions:**
- Additional compression algorithms
- Performance monitoring graphs
- Preset configurations
- Localization/translations
- Documentation improvements

---

## 📦 Version Information

- **Version**: 1.0.0
- **Release Date**: December 2025
- **Build**: Qt6 + C++20
- **Status**: Production Ready ✅
- **License**: GPLv3

---

## 🔄 Quick Commands

```bash
# Install
bash <(wget -qO- https://raw.githubusercontent.com/devakhilus/zram-gui/main/zram-install.sh)

# Launch GUI
zram

# Manual launch
sudo /usr/local/bin/zram-gui

# Check ZRAM status
zramctl

# View configuration
cat /etc/systemd/zram-generator.conf

# Uninstall
sudo rm -f /usr/local/bin/zram-gui /usr/share/applications/zram-gui.desktop /etc/sudoers.d/zram-gui
```

---

## ⚠️ Important Notes

1. **Root Access Required** - Some ZRAM operations require sudo
2. **System-Wide Impact** - ZRAM affects swap behavior globally
3. **Automatic Detection** - Tool auto-detects package manager (dnf/apt/pacman)
4. **Safe Defaults** - Conservative initial settings to avoid issues
5. **Persistent Configuration** - Settings survive reboot

---

## 🚀 Performance Tips

1. **Choose Right Algorithm**
   - Use **zstd** for best compression ratio
   - Use **lz4** for maximum speed
   - Use **lzo** for balanced approach

2. **Set Appropriate Size**
   - Start with 50-80% of RAM
   - Adjust based on system needs
   - Monitor usage in System Resources

3. **Monitor Compression**
   - Watch compression ratio in the GUI
   - Ratios below 2x might indicate little benefit
   - Adjust compression-streams for CPU cores

4. **Swap Priority**
   - Default 116 is good for most systems
   - Higher priority = use ZRAM before disk swap
   - Lower priority = use disk swap first

---

## 📞 Troubleshooting

### **ZRAM not starting?**
```bash
# Check if zram module is loaded
lsmod | grep zram

# Check systemd status
systemctl status systemd-zram-setup@zram0.service

# View logs
journalctl -xe
```

### **GUI won't launch?**
```bash
# Check Qt6 installation
pkg-config --cflags --libs Qt6Widgets

# Run from terminal to see errors
sudo /usr/local/bin/zram-gui
```

### **Compression ratio too low?**
- Try different algorithm (zstd usually best)
- Check if ZRAM is actually being used
- View zramctl statistics

---

## 🎯 Roadmap

- [ ] Performance graphs and history
- [ ] Preset configurations (gaming, server, workstation)
- [ ] Real-time compression monitoring
- [ ] Multi-language support
- [ ] AppImage distribution
- [ ] Flatpak package
- [ ] System tray integration

---

**Ready to compress? Just copy that one-liner! 🚀**

```bash
bash <(wget -qO- https://raw.githubusercontent.com/devakhilus/zram-gui/main/zram-install.sh)
```

*Made with ❤️ by Akhil US*

---

## 📊 Project Stats

- **Language**: C++20
- **Framework**: Qt6
- **Lines of Code**: 600+
- **Build Time**: < 5 seconds
- **Binary Size**: ~2-3 MB
- **Memory Usage**: < 50 MB

---

**Enjoy faster system performance with ZRAM GUI! 🚀💨**
