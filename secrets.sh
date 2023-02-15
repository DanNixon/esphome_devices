#!/bin/bash

usage() {
  echo "$0 [new|load] [device.yaml]"
}

here="$(readlink -f "$0")"
here="$(dirname "$here")"
secrets_file="$here/common/secrets.yaml"

device_file="$(basename "$2")"
device="${device_file%.*}"
if [ -z "$device" ]; then
  usage
  exit 1
fi

pass_entry="home/esphome_secrets/$device"

print_details() {
  echo "Secrets file         : $secrets_file"
  echo "Device               : $device"
  echo "Password Store entry : $pass_entry"
}

generate_empty_secrets() {
  echo "---
# Secrets for $device_file
ota_password: \"$(hsxkpasswd)\"
api_key: \"$(tr -dc A-Za-z0-9 </dev/urandom | head -c 32 | base64)\"
wifi_ssid: \"\"
wifi_password: \"\""
}

case "$1" in
  "new")
    print_details
    generate_empty_secrets | pass insert -m "$pass_entry"
    ;;
  "load")
    print_details
    pass "$pass_entry" > "$secrets_file"
    ;;
  *)
    usage
    exit 1
    ;;
esac
