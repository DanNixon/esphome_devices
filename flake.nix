{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
  }:
    flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = import nixpkgs {inherit system;};
      in rec {
        devShell = pkgs.mkShell {
          packages = with pkgs; [
            esphome

            # Code formatting tools
            alejandra
            shellcheck
            treefmt
          ];
        };
      }
    );
}
