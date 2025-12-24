#!/bin/bash
# ZRAM GUI - Ultimate One-Line Installer
# Copy-paste into terminal = Complete setup with menu integration

set -e

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m'

# Configuration
REPO="devakhilus/zram-gui"
DOWNLOAD_URL="https://github.com/devakhilus/zram-gui/releases/download/v1.0.0/zram-gui"
INSTALL_PATH="/usr/local/bin/zram-gui"
DESKTOP_FILE="/usr/share/applications/zram-gui.desktop"
SUDOERS_FILE="/etc/sudoers.d/zram-gui"

print_header() {
    clear
    echo -e "${CYAN}"
    echo "╔════════════════════════════════════════════════════════╗"
    echo "║                                                        ║"
    echo "║   🚀 ZRAM GUI - Complete Installation & Setup        ║"
    echo "║      One-Command Setup with Desktop Integration      ║"
    echo "║                                                        ║"
    echo "╚════════════════════════════════════════════════════════╝"
    echo -e "${NC}"
}

print_step() {
    echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${CYAN}→ $1${NC}"
    echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
}

print_success() {
    echo -e "${GREEN}✔${NC} $1"
}

print_error() {
    echo -e "${RED}✖${NC} $1"
}

print_info() {
    echo -e "${BLUE}ℹ${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}⚠${NC} $1"
}

# Step 1: Download
download_binary() {
    print_step "Downloading ZRAM GUI Binary"
    
    TMP_DIR="/tmp/zram-gui-install"
    mkdir -p "$TMP_DIR"
    cd "$TMP_DIR"
    
    print_info "Downloading from: $DOWNLOAD_URL"
    
    if command -v wget &> /dev/null; then
        wget -q --show-progress "$DOWNLOAD_URL" -O zram-gui-binary 2>&1 || {
            print_error "Failed to download"
            return 1
        }
    elif command -v curl &> /dev/null; then
        curl -L -o zram-gui-binary "$DOWNLOAD_URL" 2>/dev/null || {
            print_error "Failed to download"
            return 1
        }
    else
        print_error "wget or curl required"
        return 1
    fi
    
    if [ ! -s "$TMP_DIR/zram-gui-binary" ]; then
        print_error "Downloaded file is empty"
        return 1
    fi
    
    print_success "Binary downloaded successfully"
    echo ""
}

# Step 2: Install Binary
install_binary() {
    print_step "Installing Binary to System"
    
    print_info "Installing to: $INSTALL_PATH"
    sudo cp /tmp/zram-gui-install/zram-gui-binary "$INSTALL_PATH"
    sudo chmod +x "$INSTALL_PATH"
    
    print_success "Binary installed and made executable"
    echo ""
}

# Step 3: Create Desktop Entry
create_desktop_entry() {
    print_step "Creating Desktop Menu Entry"
    
    cat > /tmp/zram-gui.desktop << 'EOF'
[Desktop Entry]
Version=1.0
Type=Application
Name=ZRAM Configuration Tool
Comment=Configure and manage ZRAM swap compression
Keywords=zram;swap;compression;system;
Icon=preferences-system
Categories=System;Settings;Utility;
Exec=bash -c "sudo /usr/local/bin/zram-gui"
Terminal=false
StartupNotify=true
X-GNOME-Gettext-Domain=zram-gui

[Desktop Action Open]
Name=Open ZRAM GUI
Exec=bash -c "sudo /usr/local/bin/zram-gui"
EOF
    
    sudo cp /tmp/zram-gui.desktop "$DESKTOP_FILE"
    sudo chmod 644 "$DESKTOP_FILE"
    
    # Update desktop database
    if command -v update-desktop-database &> /dev/null; then
        sudo update-desktop-database /usr/share/applications/ 2>/dev/null || true
    fi
    
    print_success "Desktop entry created"
    print_info "Location: $DESKTOP_FILE"
    echo ""
}

# Step 4: Setup Bash Alias
setup_alias() {
    print_step "Setting Up Bash Alias"
    
    # Detect shell
    SHELL_RC="$HOME/.bashrc"
    SHELL_NAME="bash"
    
    if [ -f "$HOME/.zshrc" ] && echo "$SHELL" | grep -q zsh; then
        SHELL_RC="$HOME/.zshrc"
        SHELL_NAME="zsh"
    fi
    
    if grep -q "alias zram=" "$SHELL_RC" 2>/dev/null; then
        print_warning "Alias already exists in $SHELL_RC"
    else
        cat >> "$SHELL_RC" << 'EOF'

# ===== ZRAM GUI Alias =====
alias zram='sudo /usr/local/bin/zram-gui'
EOF
        print_success "Alias 'zram' added to $SHELL_RC"
    fi
    
    print_info "Usage: Just type 'zram' in terminal"
    echo ""
}

# Step 5: Setup Passwordless Sudo
setup_passwordless_sudo() {
    print_step "Configuring Passwordless Sudo"
    
    if [ -f "$SUDOERS_FILE" ]; then
        print_warning "Passwordless sudo already configured"
    else
        echo "$USER ALL=(ALL) NOPASSWD: /usr/local/bin/zram-gui" | \
            sudo tee "$SUDOERS_FILE" > /dev/null 2>&1
        sudo chmod 440 "$SUDOERS_FILE"
        print_success "Passwordless sudo enabled"
    fi
    
    print_info "No password needed when running: zram"
    echo ""
}

# Step 6: Verify Installation
verify_installation() {
    print_step "Verifying Installation"
    
    CHECKS=(
        ["Binary:$INSTALL_PATH"]="[ -x $INSTALL_PATH ]"
        ["Desktop Entry:$DESKTOP_FILE"]="[ -f $DESKTOP_FILE ]"
        ["Sudo Config:$SUDOERS_FILE"]="[ -f $SUDOERS_FILE ]"
    )
    
    all_good=true
    for check in "${!CHECKS[@]}"; do
        if eval "${CHECKS[$check]}"; then
            print_success "$check"
        else
            print_warning "$check"
            all_good=false
        fi
    done
    
    echo ""
    if [ "$all_good" = true ]; then
        print_success "All components installed successfully!"
    else
        print_warning "Some components missing (non-critical)"
    fi
    echo ""
}

# Step 7: Cleanup
cleanup() {
    print_step "Cleaning Up"
    
    rm -rf /tmp/zram-gui-install
    rm -f /tmp/zram-gui.desktop
    
    print_success "Temporary files cleaned"
    echo ""
}

# Step 8: Final Instructions
show_completion() {
    print_step "Installation Complete!"
    
    echo -e "${GREEN}"
    echo "╔════════════════════════════════════════════════════════╗"
    echo "║            ✨ Setup Successful!                        ║"
    echo "╚════════════════════════════════════════════════════════╝"
    echo -e "${NC}"
    
    echo ""
    echo -e "${CYAN}📍 Launch ZRAM GUI:${NC}"
    echo -e "   ${BLUE}Option 1:${NC} Type in terminal: ${YELLOW}zram${NC}"
    echo -e "   ${BLUE}Option 2:${NC} Applications Menu → ZRAM Configuration Tool"
    echo -e "   ${BLUE}Option 3:${NC} ${YELLOW}sudo /usr/local/bin/zram-gui${NC}"
    
    echo ""
    echo -e "${CYAN}📊 Installation Details:${NC}"
    echo -e "   Binary:     ${YELLOW}$INSTALL_PATH${NC}"
    echo -e "   Desktop:    ${YELLOW}$DESKTOP_FILE${NC}"
    echo -e "   Alias:      ${YELLOW}zram${NC}"
    echo -e "   Sudo:       ${YELLOW}Passwordless (no password needed)${NC}"
    
    echo ""
    echo -e "${CYAN}🔗 Links:${NC}"
    echo -e "   GitHub:     ${YELLOW}https://github.com/devakhilus/zram-gui${NC}"
    echo -e "   Telegram:   ${YELLOW}https://t.me/linuxluminaries${NC}"
    
    echo ""
}

# Step 9: Optional Launch
launch_prompt() {
    echo -e "${CYAN}─────────────────────────────────────────────────────${NC}"
    read -p "$(echo -e "${YELLOW}Launch ZRAM GUI now? (y/n):${NC} ")" -n 1 -r
    echo ""
    
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        print_info "Launching ZRAM GUI..."
        sleep 1
        sudo /usr/local/bin/zram-gui &
        print_success "ZRAM GUI started in background"
    else
        print_info "You can launch later with: ${YELLOW}zram${NC}"
    fi
    
    echo ""
}

# Main execution
main() {
    print_header
    
    # Check sudo access
    if ! sudo -n true 2>/dev/null; then
        print_warning "This script requires sudo. You may be asked for password."
        echo ""
    fi
    
    # Run all steps
    download_binary || exit 1
    install_binary || exit 1
    create_desktop_entry || exit 1
    setup_alias || exit 1
    setup_passwordless_sudo || exit 1
    verify_installation
    cleanup
    show_completion
    launch_prompt
    
    echo -e "${GREEN}Happy ZRAM compression! 🚀${NC}"
    echo ""
}

# Execute
main
