#!/bin/bash

# set -e

cd build
if [ -f install_manifest.txt ]; then
    xargs rm < install_manifest.txt
    echo "Uninstallation complete."
else
    echo "ERROR: install_manifest.txt not found."
    exit 1
fi
