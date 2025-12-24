# 🚀 ZRAM GUI - Complete Installation with Menu Integration

**Professional ZRAM compression utility with Qt6 GUI for Linux**

---

## ⚡ ULTRA-QUICK INSTALL (Copy & Paste)

**Just copy this single line into your terminal:**

```bash
bash <(wget -qO- https://raw.githubusercontent.com/devakhilus/zram-gui/main/zram-install.sh)
```

**That's it! Everything is automatic:**
- ✅ Downloads binary
- ✅ Installs to system
- ✅ Creates menu entry (Applications → ZRAM Configuration Tool)
- ✅ Sets up bash alias (`zram` command)
- ✅ Configures passwordless sudo
- ✅ Verifies installation
- ✅ Optional: Launches GUI immediately

---

## 🎯 What Happens During Installation

```
╔════════════════════════════════════════════════════════╗
║                                                        ║
║   🚀 ZRAM GUI - Complete Installation & Setup        ║
║      One-Command Setup with Desktop Integration      ║
║                                                        ║
╚════════════════════════════════════════════════════════╝

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
→ Downloading ZRAM GUI Binary
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
✔ Binary downloaded successfully

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
→ Installing Binary to System
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
✔ Binary installed and made executable

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
→ Creating Desktop Menu Entry
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
✔ Desktop entry created

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
→ Setting Up Bash Alias
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
✔ Alias 'zram' added to ~/.bashrc

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
→ Configuring Passwordless Sudo
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
✔ Passwordless sudo enabled

╔════════════════════════════════════════════════════════╗
║            ✨ Setup Successful!                        ║
╚════════════════════════════════════════════════════════╝

📍 Launch ZRAM GUI:
   Option 1: Type in terminal: zram
   Option 2: Applications Menu → ZRAM Configuration Tool
   Option 3: sudo /usr/local/bin/zram-gui

Happy ZRAM compression! 🚀
```

---

## 🚀 After Installation

### **Launch from Terminal:**
```bash
zram
```
(No password needed - already configured!)

### **Launch from Applications Menu:**
1. Open your applications menu
2. Search: "ZRAM Configuration Tool"
3. Click to launch

### **Direct Command:**
```bash
sudo /usr/local/bin/zram-gui
```

---

## 📋 What Gets Installed

| Component | Location | Purpose |
|-----------|----------|---------|
| Binary | `/usr/local/bin/zram-gui` | Main application |
| Desktop Entry | `/usr/share/applications/zram-gui.desktop` | Menu integration |
| Sudoers File | `/etc/sudoers.d/zram-gui` | Passwordless sudo |
| Alias | `~/.bashrc` or `~/.zshrc` | `zram` command |

---

## 🐧 Distro Support

**Works on all Linux distributions:**

| Distro | Package Manager | ZRAM Package |
|--------|-----------------|--------------|
| **Fedora 40+** | dnf | zram-generator |
| **Ubuntu 20.04+** | apt | zram-tools |
| **Debian 11+** | apt | zram-tools |
| **Arch Linux** | pacman | zram-generator |
| **openSUSE** | zypper | zram-generator |

---

## 📊 Features

- ✅ **One-Command Installation** - No complex steps
- ✅ **Desktop Menu Integration** - Click to launch from Applications
- ✅ **Bash Alias Support** - Just type `zram`
- ✅ **Passwordless Sudo** - No password prompt after setup
- ✅ **Auto-detect Package Manager** - Works on any distro
- ✅ **Live ZRAM Status** - Real-time compression statistics
- ✅ **Custom Compression** - zstd, lz4, lzo, lzo-rle, deflate
- ✅ **Dark/Light Theme** - Visual preference support
- ✅ **Memory Slider** - Configure 10-100% ZRAM usage
- ✅ **Advanced Settings** - Streams, priority, max size configuration

---

## ⚙️ Manual Setup (If Needed)

### Just the Binary
```bash
wget https://github.com/devakhilus/zram-gui/releases/download/v1.0.0/zram-gui
sudo cp zram-gui /usr/local/bin/
sudo chmod +x /usr/local/bin/zram-gui
sudo /usr/local/bin/zram-gui
```

### Add to Applications Menu Later
```bash
cat > ~/.local/share/applications/zram-gui.desktop << 'EOF'
[Desktop Entry]
Type=Application
Name=ZRAM Configuration Tool
Comment=Configure and manage ZRAM swap compression
Exec=bash -c "sudo /usr/local/bin/zram-gui"
Icon=preferences-system
Categories=System;Settings;
Terminal=false
EOF
```

### Setup Alias Later
```bash
echo "alias zram='sudo /usr/local/bin/zram-gui'" >> ~/.bashrc
source ~/.bashrc
```

### Setup Passwordless Sudo Later
```bash
echo "$USER ALL=(ALL) NOPASSWD: /usr/local/bin/zram-gui" | sudo tee /etc/sudoers.d/zram-gui > /dev/null
sudo chmod 440 /etc/sudoers.d/zram-gui
```

---

## 🔐 Security

- ✅ **Passwordless sudo limited** to zram-gui binary only
- ✅ **Desktop entry** prompts for password if needed
- ✅ **Sudoers file** has restricted permissions (440)
- ✅ **No external calls** - local operations only
- ✅ **Open source** - Fully auditable code

---

## 🛠️ Troubleshooting

### Alias Not Working
```bash
source ~/.bashrc  # or ~/.zshrc
which zram        # Verify it exists
```

### Still Asking for Password
```bash
sudo /etc/sudoers.d/zram-gui cat  # Check sudoers file
```

### Desktop Entry Not Appearing
```bash
# Update database
sudo update-desktop-database /usr/share/applications/

# Or restart desktop environment (log out & back in)
```

### Binary Not Working
```bash
# Verify permissions
ls -la /usr/local/bin/zram-gui

# Should show: -rwxr-xr-x (755)
```

---

## 🔄 Uninstall

```bash
# Remove all components
sudo rm -f /usr/local/bin/zram-gui
sudo rm -f /usr/share/applications/zram-gui.desktop
sudo rm -f /etc/sudoers.d/zram-gui

# Remove alias (edit these files and remove the line)
nano ~/.bashrc  # Remove: alias zram=...
nano ~/.zshrc   # Remove: alias zram=... (if using zsh)

# Clean cache
rm -rf ~/.cache/zram-gui
```

---

## 📞 Support & Links

- **🐛 Issues**: https://github.com/devakhilus/zram-gui/issues
- **💬 Telegram**: https://t.me/linuxluminaries
- **📂 GitHub**: https://github.com/devakhilus/zram-gui
- **👨‍💻 Author**: Akhil US (Merwick)

---

## 📄 License

GNU General Public License v3.0 (GPLv3)

---

## 🚀 Quick Reference

```bash
# One-line install
bash <(wget -qO- https://raw.githubusercontent.com/devakhilus/zram-gui/main/zram-install.sh)

# Launch after install
zram                      # Terminal
# OR
# Click: Applications → ZRAM Configuration Tool

# Manual uninstall
sudo rm -f /usr/local/bin/zram-gui /usr/share/applications/zram-gui.desktop /etc/sudoers.d/zram-gui
```

---

**That's it! Happy ZRAM compression! 🚀**

*Copy the install command above → Paste in terminal → Enjoy!*
