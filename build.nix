{ stdenv
, lib
, nix-gitignore

, pkg-config
, libevdev
, libxkbcommon
, freetype
, SDL2
, libdrm
, libinput

, withSimulator ? false
}:

let
  inherit (lib) optional optionals optionalString;
  simulatorDeps = [
    SDL2
  ];
in
  stdenv.mkDerivation {
    pname = "mobile-nixos-early-boot-gui";
    version = "2020-02-05";

    src = nix-gitignore.gitignoreSource [] ./.;

    # Document `LVGL_ENV_SIMULATOR` in the built headers.
    # This allows the mrbgem to know about it.
    # (In reality this should be part of a ./configure step or something similar.)
    postPatch = ''
      sed -i"" '/^#define LV_CONF_H/a #define LVGL_ENV_SIMULATOR ${if withSimulator then "1" else "0"}' lv_conf.h
    '';

    nativeBuildInputs = [
      pkg-config
    ];

    buildInputs = [
      freetype
      libevdev
      libdrm
      libinput
      libxkbcommon
    ]
    ++ optionals withSimulator simulatorDeps
    ;

    NIX_CFLAGS_COMPILE = [
      "-DX_DISPLAY_MISSING"
    ];

    makeFlags = [
      "PREFIX=${placeholder "out"}"
    ]
    ++ optional withSimulator "LVGL_ENV_SIMULATOR=1"
    ++ optional (!withSimulator) "LVGL_ENV_SIMULATOR=0"
    ;

    enableParallelBuilding = true;
  }
