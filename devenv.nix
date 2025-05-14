{pkgs, ...}: {
  packages = with pkgs; [
    esphome

    # Code formatting tools
    alejandra
    shellcheck
    treefmt
  ];
}
