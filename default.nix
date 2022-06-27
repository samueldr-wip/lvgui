{ withSimulator ? false }:
(import <nixpkgs> {}).callPackage ./build.nix { inherit withSimulator; }
