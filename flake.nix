{
  description = "Collection of C macros to generate code";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/23.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        stdenv = nixpkgs.legacyPackages.${system}.stdenv;
      in
      {
        packages =
          let
            package = stdenv.mkDerivation
              {
                name = "blackmagic";
                src = self;
                installPhase =
                  "mkdir --parents $out/include && cp -r include $out";
              };
          in
          {
            blackmagic = package;
            default = package;
          };
      }
    );
}
