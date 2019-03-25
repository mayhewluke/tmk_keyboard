{
  # Unless given an override, automatically grab the last known working revision
  # of nixpkgs (17.03), as newer channels make changes to cross-compilation that
  # break this derivation.
  nixpkgs ? import ((import <nixpkgs> {}).fetchgit {
    url = "https://github.com/NixOS/nixpkgs-channels.git";
    rev = "78e9665b48ff45d3e29f45b3ebeb6fc6c6e19922";
    sha256 = "09f50jaijvry9lrnx891qmcf92yb8qs64n1cvy0db2yjrmxsxyw8";
  }) {},
  keyboard ? "ergodox"
}:

with nixpkgs;
with pkgs;

let
  loader = "${teensy-loader-cli}/bin/teensy-loader-cli";
  subdir = "keyboard/${keyboard}";
  make   = "make $makeFlags -f $makefile --no-print-directory";
  script = "make-teensy";
in
  stdenv.mkDerivation rec {
    name = "tmk-keyboard-${keyboard}";
    src = ./.;
    buildInputs = [ avrgcclibc ];
    makefile = "Makefile.lufa";
    makeFlags = "-C ${subdir}";
    doDist = false;
    installPhase = ''
      mkdir -p $out

      pushd ${subdir} && make -f ${makefile} clean && popd
      # Copy build results
      ${make} program PROGRAM_CMD="cp -p \$^ $out/"

      # Put teensy target commands into a script
      cat >$out/${script} <<EOF
      #!/bin/sh
      # Abort if not root, as normal users don't have permission to flash the
      # ErgoDox and will end up locking up the keyboard.
      if [ "\$EUID" -ne 0 ]; then
        echo "Must be run as root. Aborting."
        exit
      fi
      cd $out
      exec $(${make} -n teensy | sed 's@teensy_loader_cli@${loader}@g')
      EOF
      chmod a+x $out/${script}
    '';
  }
