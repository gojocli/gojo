#!/bin/bash

MAGENTA="\033[1;35m"
CYAN="\033[1;36m"
GREEN="\033[1;32m"
YELLOW="\033[1;33m"
CLEAR="\033[0m"

# Create directories in the user's home directory
mkdir -p ~/.gojocli
mkdir -p ~/.gojocli/profiles
mkdir -p ~/.gojocli/bin

# Detect operating systerm
echo ""
OS=$(uname -s)
if [ "$OS" = "Linux" ]; then
    echo -e "Installing ${MAGENTA}gojo${CLEAR} for ${CYAN}Linux${CLEAR}..."
elif [ "$OS" = "Darwin" ]; then
    echo -e "Installing ${MAGENTA}gojo${CLEAR} for ${CYAN}MacOS${CLEAR}..."
else
    echo "$OS is not supported by gojo"
    exit 1
fi
echo ""

# Download latest release from github into ~/.gojocli/bin

# Download gojo-update from github into ~/.gojocli/bin

# Set gojo binaries to be executable
# Not sure if the first one is needed.
chmod +x ~/.gojocli/bin/gojo
chmod +x ~/.gojocli/bin/gojo-update

# Add ~/.gojocli/bin to PATH
if [ "$OS" = "Linux" ]; then
    echo "export PATH=\"\$PATH:\$HOME/.gojocli/bin/\"" >> ~/.bashrc
elif [ "$OS" = "Darwin" ]; then
    echo "export PATH=\"\$PATH:\$HOME/.gojocli/bin/\"" >> ~/.zshrc
fi


echo -e "${MAGENTA}gojo${CLEAR} ${GREEN}has successfully been installed!${CLEAR}"
echo ""
if [ "$OS" = "Linux" ]; then
    echo -e "run '${YELLOW}source ~/.bashrc${CLEAR}' in your terminal to use it,"
elif [ "$OS" = "Darwin" ]; then
    echo -e "run '${YELLOW}source ~/.zshrc${CLEAR}' in your terminal to use it,"
fi
echo "or start a new terminal session."
echo ""
